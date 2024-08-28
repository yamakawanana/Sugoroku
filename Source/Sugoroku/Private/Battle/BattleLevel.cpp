#include "Battle/BattleLevel.h"
#include "Battle/BattleController.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "../Public/SugorokuGameInstance.h"
#include "GameFramework/Character.h"
#include "Battle/BattleUiManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include <cmath>
#include "Battle/AI/CharacterAIController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Battle/Dice/Dice.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/HUD.h"
#include "Battle/GoldCoin/GoldCoin.h"
#include "Battle/ReduceGoldCoin/ReduceGoldCoin.h"
#include "Battle/AnimManager/AnimManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ABattleLevel::ABattleLevel()
  : SpawnPoint(nullptr)
  , FilmingPoint(nullptr)
  , Phase(TurnType::WaitingRollDice)
  , DiceNum(0)
  , TypeACharacterClass(nullptr)
  , TypeACharacter(nullptr)
  , TypeACharacterChildClass(nullptr)
  , TypeACharacterChild(nullptr)
  , TypeBCharacterClass(nullptr)
  , TypeBCharacter(nullptr)
  , TypeCCharacterClass(nullptr)
  , TypeCCharacter(nullptr)
  , TypeDCharacterClass(nullptr)
  , TypeDCharacter(nullptr)
  , CharacterKind(CharacterType::TypeA)
  , bBranchRoad(false)
  , PreExistSquareClass(nullptr)
  , PreExistSquare(nullptr)
  , AccumulatedTime(0.0f)
  , DecideNunAccumulatedTime(0.0f)
  , BlendAlpha(0.0f)
  , WaitTime(BattleNameSpace::SecondSmoothBlendTime)
{
  // Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;
}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::BeginPlay() {
  Super::BeginPlay();

  ABattleController* PlayerController = Cast<ABattleController>(GetWorld()->GetFirstPlayerController());
  if (IsValid(PlayerController))
  {
    //Battle画面を開く
  }

  // 各キャラクターとキャラクタークラスを配列に格納する
  CharacterClasses = {
      {TypeACharacterChildClass, TypeACharacterChild},
      {TypeBCharacterClass, TypeBCharacter},
      {TypeCCharacterClass, TypeCCharacter},
      {TypeDCharacterClass, TypeDCharacter}
  };

  // レベルに配置済みのキャラクターを取得する
  for (TObjectIterator<APlayerCharacter> Itr; Itr; ++Itr) {
    if (IsValid(*Itr)) {
      // キャラクターのクラスを取得
      UClass* CharacterClass = Itr->GetClass();

      // 対応するキャラクターを設定する
      for (auto& Pair : CharacterClasses) {
        if (CharacterClass == Pair.first) {
          Pair.second = *Itr;
          break;
        }
      }
    }
  }

  //ベースとなるマスをスポーンする
  PreExistSquare = GetWorld()->SpawnActor<ASquare>(PreExistSquareClass, FVector(0.0f, 0.0f, BattleNameSpace::SpawnStartXPos), FRotator::ZeroRotator);
  //経路探索のクラスをスポーンする
  RouteSearch = GetWorld()->SpawnActor<ARouteSearch>(RouteSearchClass, FVector(0.0f, 0.0f, BattleNameSpace::SpawnStartXPos), FRotator::ZeroRotator);
  RouteSearch->SetSquareClass(PreExistSquare);
  //CSVFileManagerのクラスをスポーンする
  CSVFileManager = GetWorld()->SpawnActor<ACSVFileManager>(CSVFileManagerClass, FVector(0.0f, 0.0f, BattleNameSpace::SpawnStartXPos), FRotator::ZeroRotator);
  CSVFileManager->SetSquareClass(PreExistSquare);
  //ファイルからボードデータを読み込む
  CSVFileManager->SetDataFromFile();
  // サイコロのクラスをスポーンする
  Dice = GetWorld()->SpawnActor<ADice>(DiceClass, FVector(0.0f, 0.0f, BattleNameSpace::SpawnStartXPos), FRotator::ZeroRotator);
  //所持金表示のクラスをスポーンする
  CoinNum = CreateWidget<UCoinNum>(GetWorld(), CoinNumClass);

  // ボードにマスをスポーンする
  SpawnSquares();

  // 全てのマスの数を取得する
  int32 NumElements = PreExistSquare->GetTargetLocationsNum();

  //スタート位置を取得する
  FVector StartLocation = PreExistSquare->GetTargetLocations(NumElements - 1);
  //既に通ったマスを格納する配列にスタート位置を格納する
  for (int32 j = 0; j < StaticCast<int32>(CharacterType::TypeMax); ++j) {
    PreExistSquare->AddPassedLocations(StartLocation, j);
  }
  //曲がり角のマスを配列に格納する
  PreExistSquare->CheckCornerLocations();

  //所持金表示のUIを開き、所持金の情報を初期化する
  CoinNum->InitCoinNumWidget();
  CoinNum->OpenCoinNum();
  CoinNum->InitCoinNum(DiceNameSpace::Four);
  //コインの増減時にアニメーションするコインの数を配列GoldCoinsに設定する
  GoldCoins.SetNum(CoinNumNameSpace::CoinChangeAmount);
  ReduceGoldCoins.SetNum(CoinNumNameSpace::CoinChangeAmount);

  //最初のキャラクターのカメラをセットする
  PlayerController->SetViewTargetWithBlend(TypeACharacterChild, 0.0f);
}

/// <summary>
/// EndPlay関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>終了する理由</returns>
void ABattleLevel::EndPlay(const EEndPlayReason::Type EndPlayReason) {
  Super::EndPlay(EndPlayReason);

}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ABattleLevel::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  for (int32 j = 0; j < StaticCast<int32>(CharacterType::TypeMax); ++j) {
    if (CharacterKind == StaticCast<CharacterType>(j)) {

      //キャラクターの現在位置を取得する
      FVector NowPos = CharacterClasses[j].second->GetActorLocation();

      //現在のボードデータ上のX位置とY位置を取得する
      int32 NowX = StaticCast<int32>(StaticCast<int32>(NowPos.X - BattleNameSpace::SpawnStartYPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));
      int32 NowY = StaticCast<int32>(StaticCast<int32>(NowPos.Y - BattleNameSpace::SpawnStartXPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));
      //現在のマスの種類を取得する
      RoadType NowRoadType = PreExistSquare->GetBoardData(NowY, NowX);
      //サイコロの出目をランダムに格納する配列
      int32 DiceNums[DiceNameSpace::Six] = { DiceNameSpace::Four,DiceNameSpace::Two,DiceNameSpace::Six,DiceNameSpace::One,DiceNameSpace::Five,DiceNameSpace::Three };
      //PlayerControllerを取得
      ABattleController* PlayerController = Cast<ABattleController>(GetWorld()->GetFirstPlayerController());
      // 現在のカメラの位置と角度を取得
      APlayerCameraManager* NowPlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
      FVector NowCameraLocation = NowPlayerCameraManager->GetCameraLocation();
      FRotator NowCameraRotation = NowPlayerCameraManager->GetCameraRotation();
      FString DebugMessage20 = FString::Printf(TEXT("NowPos.X: %f"), NowPos.X);
      FString DebugMessage21 = FString::Printf(TEXT("NowPos.Z: %f"), NowPos.Z);
      GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage20);
      GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage21);
      FString DebugMessage22 = FString::Printf(TEXT("NowCameraLocation.X: %f"), NowCameraLocation.X);
      FString DebugMessage23 = FString::Printf(TEXT("NowCameraLocation.Z: %f"), NowCameraLocation.Z);
      GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage22);
      GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage23);

      // コイン増加時のコインのスポーン位置を設定する
      FVector CoinSpawnLocation(NowPos.X - GoldCoinNameSpace::CoinSpawnX, NowPos.Y + ReduceGoldCoinNameSpace::CoinSpawnY, NowPos.Z + GoldCoinNameSpace::CoinSpawnZ);
      // コイン減少時のコインのスポーン位置を設定する
      FVector ReduceCoinSpawnLocation(NowPos.X - ReduceGoldCoinNameSpace::CoinSpawnX, NowPos.Y + ReduceGoldCoinNameSpace::CoinSpawnY, NowPos.Z + ReduceGoldCoinNameSpace::CoinSpawnZ);
      //コインのスポーン角度を設定する
      FRotator CoinSpawnRotation(NowCameraRotation.Pitch + BattleNameSpace::RightAngle, NowCameraRotation.Yaw, NowCameraRotation.Roll);
      // 最短経路を選択するCPUキャラクターであるかを確認する
      bool IsFrontOnly = IsFrontOnlyCharacter(CharacterKind);

      // カメラコンポーネントの取得
      UCameraComponent* CameraComp = CharacterClasses[j].second->GetCharacterCameraComponent();
      UCameraComponent* SecondCameraComp = CharacterClasses[j].second->GetCharacterSecondCameraComponent();

      //サイコロを振る入力待ちの場合
      if (Phase == TurnType::WaitingRollDice) {
        AccumulatedTime = AccumulatedTime + DeltaTime;
        bForceMove = false;

        if (AccumulatedTime >= DiceNameSpace::ResetTime) {
          AccumulatedTime = 0.0f;
          if (CharacterKind != CharacterType::TypeA) {
            //ランダムな整数を生成する
            int32 RandomNum = 0;
            //キャラクターBの場合、出目を4～6しか出さない
            if (CharacterKind == CharacterType::TypeB) {
              RandomNum = GetRandomNum(DiceNameSpace::Four, DiceNameSpace::Six);
            }
            //キャラクターCかDの場合、1～6をランダムに出す
            else {
              RandomNum = GetRandomNum(DiceNameSpace::One, DiceNameSpace::Six);
            }
            
            //プレイヤー以外のキャラクターの場合、自動でランダムな整数をサイコロの出目にする
            Dice->OpenDice(RandomNum);
            DiceNum = RandomNum;
            Phase = TurnType::DecideNumAnim;
          }
        }

        // そのキャラクターの最初のターンであるか確認する
        bool IsFirstTurn = CharacterClasses[j].second->GetFirstTurn();

        //最初のターンである場合
        if (IsFirstTurn) {
          // 全てのマスの数を取得する
          int32 NumElements = PreExistSquare->GetTargetLocationsNum();
          //スタート位置を取得する
          FVector StartLocation = PreExistSquare->GetTargetLocations(NumElements - 1);
          CharacterClasses[j].second->SetActorLocation(FVector(StartLocation.X, StartLocation.Y, StartLocation.Z + BattleNameSpace::ChangeLocY));
          CharacterClasses[j].second->SetFirstTurn(false);
        }

        if (!IsFirstTurn) {
          //前のターンのキャラクターを他のキャラクターとぶつからない位置に調整する
          ChangeCharacterPos(j);
        }

        //累積時間に伴い、DiceNumsの中から表示するサイコロの出目を変える
        for (int i = 0; i < DiceNameSpace::Six; ++i) {
          if (AccumulatedTime > DiceNameSpace::ChangeTime[i] && AccumulatedTime <= DiceNameSpace::ChangeTime[i + 1]) {
            int PreviousIndex = 0;
            if (i == 0) {
              PreviousIndex = DiceNameSpace::Six - 1;
            }
            else {
              PreviousIndex = i - 1;
            }
            Dice->CloseDice(DiceNums[PreviousIndex]);
            Dice->OpenDice(DiceNums[i]);
            DiceNum = DiceNums[i];
            break;
          }
        }

        //動作確認のため、サイコロの目を指定する処理
        TArray<FKey> Keys = { EKeys::A, EKeys::B, EKeys::C, EKeys::D, EKeys::E, EKeys::F };
        for (int i = 0; i < Keys.Num(); ++i)
        {
          if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(Keys[i]))
          {
            Dice->OpenDice(i + 1);
            DiceNum = i + 1;
            Phase = TurnType::DecideNumAnim;
            break;
          }
        }

        //スペースキーが押されたら、ランダムな出目で出目確定フェーズに遷移する
        if ((CharacterKind == CharacterType::TypeA) && GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::SpaceBar))
        {
          Phase = TurnType::DecideNumAnim;
        }

      }
      //出目確定フェーズの場合
      else if (Phase == TurnType::DecideNumAnim) {
        DecideNunAccumulatedTime = DecideNunAccumulatedTime + DeltaTime;
        if (DecideNunAccumulatedTime >= DiceNameSpace::DecideNumResetTime) {
          DecideNunAccumulatedTime = 0.0f;
          //一定時間、サイコロの出目を見せてから動き始めるフェーズに遷移する
          Phase = TurnType::StartMove;
        }
      }
      //キャラクターが動き始めるフェーズの場合
      else if (Phase == TurnType::StartMove) {

        //AIControllerを取得する
        ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[j].second->GetController());
        //現在位置を取得する
        FVector LastPassedLocation = PreExistSquare->GetLastPassedLocations(j);

        //現在のボードデータ上のX位置とY位置を取得する
        NowX = StaticCast<int32>(StaticCast<int32>(LastPassedLocation.X - BattleNameSpace::SpawnStartYPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));
        NowY = StaticCast<int32>(StaticCast<int32>(LastPassedLocation.Y - BattleNameSpace::SpawnStartXPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));

        //分かれ道にいる場合
        if (bBranchRoad) {

          //分かれ道でMキーを押すと全体マップを表示する
          if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::M) && (!bAllMapCameraChange)) {
            if (!bAllMapUpdateLocation) {
              AllMapCameraLocation = FVector(NowCameraLocation.X - BattleNameSpace::AllMapChangeLocX, NowCameraLocation.Y, NowCameraLocation.Z + BattleNameSpace::AllMapChangeLocZ);
              AllMapCameraRotation = FRotator(NowCameraRotation.Pitch - BattleNameSpace::AllMapChangePitch, NowCameraRotation.Yaw, NowCameraRotation.Roll);
              PreAllMapCameraLocation = NowCameraLocation;
              PreAllMapCameraRotation = NowCameraRotation;
              CameraComp->SetWorldLocation(AllMapCameraLocation);
              CameraComp->SetWorldRotation(AllMapCameraRotation);
              bAllMapUpdateLocation = true;
            }
          }
          //Mキーが離れた場合
          if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::M)) {
            if (!bAllMapCameraChange) {
              bAllMapCameraChange = true;
            }
            else if (bAllMapCameraChange) {
              bAllMapCameraChange = false;
            }
          }
          //既に全体マップを表示した状態で再度Mキーを押すと元のカメラ位置に戻る
          if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::M) && (bAllMapCameraChange)) {
            if (bAllMapUpdateLocation) {
              CameraComp->SetWorldLocation(PreAllMapCameraLocation);
              CameraComp->SetWorldRotation(PreAllMapCameraRotation);
              bAllMapUpdateLocation = false;
            }
          }

          PlayerController->DisplayBranchMessage();

          //現在位置から最短経路で進む場合の次の位置を格納する変数
          FPos NextRoutePos;

          //ゴールまでの最短経路を調べる
          RouteSearch->SearchNearestRoute(NowX, NowY);
          //最短経路までの歩数を取得する
          int32 RouteCount = RouteSearch->GetRoutecount();
          //最短経路の中で現在地の次の位置を取得する
          NextRoutePos = RouteSearch->GetBackTraceLocations((RouteCount - 1) - 1);
          //分かれ道での進むことが可能なマスの中から最短経路に含まれないマスを取得する
          RouteSearch->CheckNotMatchSquare(BranchSquares);
          //最短経路の中で現在地の次の位置を取得する
          FVector NextRouteTarget = CalculateSpawnPos(NextRoutePos.X, NextRoutePos.Y);

          //矢印が無い場合、最初に正面に矢印をスポーンする
          if (!IsValid(Arrow)) {
            Arrow = GetWorld()->SpawnActor<AArrow>(ArrowClass, FVector(NextRouteTarget.X, NextRouteTarget.Y, NextRouteTarget.Z + BattleNameSpace::ChangeAngle), FRotator(BattleNameSpace::RightAngle, 0.0f, 0.0f));
            //矢印の方向を設定する
            Arrow->SetArrowDirection(ArrowDirection::Front);
          }

          //矢印の向きを取得する
          ArrowDirection Direction = Arrow->GetArrowDirection();

          //AキーかDキーで操作した時の左右の矢印をセットする
          SetArrowRightLeft();

          //Wキーを押した場合の正面の矢印をセットする
          if ((GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::W)) || IsFrontOnly) {
            Arrow->Destroy();
            SetArrowFront(NextRouteTarget);
          }

          if ((GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::SpaceBar)) || CharacterKind != CharacterType::TypeA) {

            //矢印の向きを再度取得する
            Direction = Arrow->GetArrowDirection();
            Arrow->Destroy();
            PlayerController->CloseBranchMessage();
            //矢印の方向が前向きの状態でSpaceキーが押されたら、最短経路のマスに進む
            if (Direction == ArrowDirection::Front)
            {
              if ((RouteCount - 1) - DiceNum < 0) {
                NextRoutePos = RouteSearch->GetBackTraceLocations(0);
              }
              //最短経路の中で現在地の次の位置をターゲット位置とする
              Controller->SetTargetLoc(NextRouteTarget);
              //現在地の次の位置を通過済みのマスに追加する
              PreExistSquare->AddPassedLocations(NextRouteTarget, j);

              //DiceNumを1減らす
              DiceNum--;
              bFinishBranch = true;
            }
            //矢印の方向が前向きではない状態でSpaceキーが押されたら、最短経路ではない方のマスに進む
            else if (Direction != ArrowDirection::Front) {
              //最短経路ではないマスを目的位置に設定する
              Controller->SetTargetLoc(BranchSquares[0].Location);
              //最短経路ではない方のマスを通過済みのマスに追加する
              PreExistSquare->AddPassedLocations(BranchSquares[0].Location, j);
              //最短経路ではないマスの方向を進行方向に設定する
              CharacterClasses[j].second->SetCharacterDirection(BranchSquares[0].Direction);

              //DiceNumを1減らす
              DiceNum--;
              bFinishBranch = true;
            }
          }
        }

        //分かれ道ではない場合のターゲット位置と通過済みのマスを決定する
        DecideTargetAndPassed(NowX, NowY, LastPassedLocation);

        if (IsValid(Controller) && (DiceNum == 0 || bBranchRoad || bCorner)) {
          //ビヘイビアツリーの目標地点を更新する
          Controller->DecideTargetPoint();
          //移動アニメーションのフェーズに変更する
          Phase = TurnType::MoveAnim;
        }
      }
      else if (Phase == TurnType::MoveAnim) {

      //現在位置を取得する
      FVector LastPassedLocation = PreExistSquare->GetLastPassedLocations(j);

      //動き始める時にカメラ位置と角度を変更する
      if (!bUpdateLocation) {
        if (bForceMove) {
          NewCameraLocation = FVector(NowCameraLocation.X - BattleNameSpace::ChangeLocX, NowCameraLocation.Y, NowCameraLocation.Z + BattleNameSpace::ChangeLocZ);
        }
        else {
          NewCameraLocation = FVector(NowCameraLocation.X - BattleNameSpace::ChangeLocX, NowCameraLocation.Y, NowCameraLocation.Z + BattleNameSpace::ChangeLocZ);
        }
        NewCameraRotation = FRotator(NowCameraRotation.Pitch - BattleNameSpace::ChangeAngle, NowCameraRotation.Yaw, NowCameraRotation.Roll);
        PreCameraLocation = NowCameraLocation;
        PreCameraRotation = NowCameraRotation;
        bUpdateLocation = true;
      }
      //カメラ位置と角度を滑らかに変更する
      if (!bBranchCameraChange) {
        if (CameraComp)
        {
          if (!bForceMove) {
            FVector CurrentCameraLocation = CameraComp->GetComponentLocation();
            FRotator CurrentCameraRotation = CameraComp->GetComponentRotation();

            FVector InterpolatedLocation = FMath::Lerp(CurrentCameraLocation, NewCameraLocation, StaticCast<float>(CurrentStep) / StaticCast <float>(10));
            FRotator InterpolatedRotation = FMath::Lerp(CurrentCameraRotation, NewCameraRotation, StaticCast<float>(CurrentStep) / StaticCast <float>(10));

            CameraComp->SetWorldLocation(InterpolatedLocation);
            CameraComp->SetWorldRotation(InterpolatedRotation);

            if (CurrentStep < 10) {
              CurrentStep++;
            }
            if (CurrentStep >= 10) {
              CurrentStep = 0;
              bBranchCameraChange = true;
            }
          }
        }
      }

        //ターゲットポイントを取得する
        ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[j].second->GetController());
        FVector TargetPos = Controller->GetTargetPoint();

        //ターゲットポイントとキャラクターの現在位置が一致する場合
        if (NowPos.X == TargetPos.X && NowPos.Y == TargetPos.Y) {
          //AfterCornerNumが残っている場合、強制移動の途中なので、ForceMoveEventに戻る
          if ((AfterCornerNum > 0) && (!bForceMove)) {
            Phase = TurnType::ForceMoveEvent;
          }
          //強制移動の完了後の場合
          else if (bForceMove) {
            Phase = TurnType::WaitingRollDice;
            AfterCornerNum = 0;
            FRotator CharacterRotation = CharacterClasses[j].second->GetActorRotation();
            CharacterRotation.Yaw += 180.0f;
            CharacterClasses[j].second->SetActorRotation(CharacterRotation);
            bUpdateLocation = false;

            //ターンを次のキャラクターに変更する
            ChangeCharacterType(j);
          }
          //DiceNumが0の場合は移動が終わっているので、イベント表示フェーズに遷移する
          else if (DiceNum == 0) {
            if (!bForceMove) {
              Phase = TurnType::DisplayEventUi;
            }
            //サイコロの画像を非表示にする
            for (int i = 0; i < DiceNameSpace::Six; ++i) {
              Dice->CloseDice(i + 1);
            }
            bBranchRoad = false;
            bCorner = false;
            bFinishCorner = true;
          }
          //DiceNumが残っている場合は分かれ道で止まった状態であるため、StartMoveに遷移する
          else if (DiceNum > 0) {
            Phase = TurnType::StartMove;
            if (bFinishBranch) {
              bBranchRoad = false;
              bFinishBranch = false;
            }
            bCorner = false;
          }
        }
      }

      else if (Phase == TurnType::DisplayEventUi) {
      //現在位置を取得する
      FVector LastPassedLocation = PreExistSquare->GetLastPassedLocations(j);

        if (bBranchCameraChange) {
          if (CameraComp)
          {

            FVector CurrentCameraLocation = CameraComp->GetComponentLocation();
            FRotator CurrentCameraRotation = CameraComp->GetComponentRotation();

            FVector InterpolatedLocation = FMath::Lerp(CurrentCameraLocation, FVector(LastPassedLocation.X + BattleNameSpace::CameraChangeX, LastPassedLocation.Y, LastPassedLocation.Z + BattleNameSpace::CameraChangeZ), StaticCast<float>(CurrentStep) / StaticCast <float>(10));
            FRotator InterpolatedRotation = FMath::Lerp(CurrentCameraRotation, PreCameraRotation, StaticCast<float>(CurrentStep) / StaticCast <float>(10));

            CameraComp->SetWorldLocation(InterpolatedLocation);
            CameraComp->SetWorldRotation(InterpolatedRotation);

            if (CurrentStep < 10) {
              CurrentStep++;
            }
            if (CurrentStep >= 10) {
              CurrentStep = 0;
              bBranchCameraChange = false;
              bUpdateLocation = false;

              //止まったマスのイベントに応じてUIを表示
              for (int i = StaticCast<int32>(RoadType::NoEvent); i <= StaticCast<int32>(RoadType::ForceMove); ++i) {
                if (NowRoadType == StaticCast<RoadType>(i)) {
                  if (i > StaticCast<int32>(RoadType::NoEvent)) {
                    //イベント内容を表示する
                    PlayerController->DisplayEvent(i - StaticCast<int32>(RoadType::IncreaseMoney));
                  }
                  //イベントの内容ごとにフェーズ遷移する
                  Phase = TurnType::DisplayEventResultUi;
                }
              }
            }

          }
        }

      }

      else if (Phase == TurnType::DisplayEventResultUi) {
        DecideNunAccumulatedTime = DecideNunAccumulatedTime + DeltaTime;
        if (DecideNunAccumulatedTime >= DiceNameSpace::DecideNumResetTime) {
          DecideNunAccumulatedTime = 0.0f;
          //一定時間経過後、マスのイベントUIを閉じる
          for (int i = StaticCast<int32>(RoadType::NoEvent); i <= StaticCast<int32>(RoadType::ForceMove); ++i) {
            if (NowRoadType == StaticCast<RoadType>(i)) {
              //イベント表示UIを閉じる
              PlayerController->CloseEvent(i - StaticCast<int32>(RoadType::IncreaseMoney));
              //イベントの内容ごとにフェーズ遷移する
              Phase = StaticCast<TurnType>(i - StaticCast<int32>(RoadType::NoEvent) + StaticCast<int32>(TurnType::NoEventPhase));
            }
          }
        }
      }

      //何もイベントがないマスの場合
      else if (Phase == TurnType::NoEventPhase) {
        Phase = TurnType::WaitingRollDice;
        //ターンを次のキャラクターに変更する
        ChangeCharacterType(j);
      }

      //コイン増加イベントの場合
      else if (Phase == TurnType::CoinIncreaseEvent) {
        //所持金を増やす
        if (bCoinIncreased == false) {
          CoinNum->AddCoins(j, CoinNumNameSpace::CoinChangeAmount);
          bCoinIncreased = true;
        }

        CoinStartAccumulatedTime += DeltaTime;

        //コイン増減アニメーションを実行する
        AnimCoin(j, bCoinIncreased, bCoinDecreased, CoinSpawnLocation, ReduceCoinSpawnLocation, CoinSpawnRotation, DeltaTime);
      }

      //コイン減少イベントの場合
      else if (Phase == TurnType::CoinDecreaseEvent) {

        if (bCoinDecreased == false) {
          //所持金を減らす
          CoinNum->RemoveCoins(j, CoinNumNameSpace::CoinChangeAmount);
          bCoinDecreased = true;
          //減らした後の所持金を取得する
          int32 CoinNumResult = CoinNum->GetCoins(j);
          //所持金がマイナスになっていた場合、所持金を0に設定する
          if (CoinNumResult < 0) {
            CoinNum->SetCoins(j, 0);
          }
        }

        CoinStartAccumulatedTime += DeltaTime;
        //コイン増減アニメーションを実行する
        AnimCoin(j, bCoinIncreased, bCoinDecreased, CoinSpawnLocation, ReduceCoinSpawnLocation, CoinSpawnRotation, DeltaTime);
      }

      //強制移動イベントマスの場合
      else if (Phase == TurnType::ForceMoveEvent && (!bForceMove)) {
      //AIControllerを取得する
      ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[j].second->GetController());
      //強制移動後のターゲット位置を設定する
      SetForceMove(j);

        //ビヘイビアツリーの目標地点を更新する
        Controller->DecideTargetPoint();
        Phase = TurnType::MoveAnim;
      }
    }
  }

}

/// <summary>
/// PreInitializeComponents関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::PreInitializeComponents() {
  USugorokuGameInstance* GameInstance = Cast<USugorokuGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  //キャラクターとマスのパスを取得する
  TypeACharacterPath = BattleNameSpace::TypeACharPath;
  TypeACharacterChildPath = BattleNameSpace::TypeACharChildPath;
  TypeBCharacterPath = BattleNameSpace::TypeBCharPath;
  TypeCCharacterPath = BattleNameSpace::TypeCCharPath;
  TypeDCharacterPath = BattleNameSpace::TypeDCharPath;
  SquarePath = BattleNameSpace::SqPath;
  BlueSquarePath = BattleNameSpace::BlueSqPath;
  RedSquarePath = BattleNameSpace::RedSqPath;
  YellowSquarePath = BattleNameSpace::YellowSqPath;
  StartSquarePath = BattleNameSpace::StartSqPath;
  GoalSquarePath = BattleNameSpace::GoalSqPath;
  RouteSearchPath = BattleNameSpace::SearchRtPath;
  FileManagerPath = BattleNameSpace::FileManagPath;

  //キャラクターのパスの情報を使い、キャラクタークラスをロードする
  TypeACharacterClass = TSoftClassPtr<APlayerCharacter>(FSoftObjectPath(*TypeACharacterPath)).LoadSynchronous();
  TypeACharacterChildClass = TSoftClassPtr<APlayerCharacter>(FSoftObjectPath(*TypeACharacterChildPath)).LoadSynchronous();
  TypeBCharacterClass = TSoftClassPtr<APlayerCharacter>(FSoftObjectPath(*TypeBCharacterPath)).LoadSynchronous();
  TypeCCharacterClass = TSoftClassPtr<APlayerCharacter>(FSoftObjectPath(*TypeCCharacterPath)).LoadSynchronous();
  TypeDCharacterClass = TSoftClassPtr<APlayerCharacter>(FSoftObjectPath(*TypeDCharacterPath)).LoadSynchronous();
  PreExistSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*SquarePath)).LoadSynchronous();
  RouteSearchClass = TSoftClassPtr<ARouteSearch>(FSoftObjectPath(*RouteSearchPath)).LoadSynchronous();
  CSVFileManagerClass = TSoftClassPtr<ACSVFileManager>(FSoftObjectPath(*FileManagerPath)).LoadSynchronous();
  DiceClass = TSoftClassPtr<ADice>(FSoftObjectPath(*BattleNameSpace::DicePath)).LoadSynchronous();
  CoinNumClass = TSoftClassPtr<UCoinNum>(FSoftObjectPath(*BattleNameSpace::CoinNumPath)).LoadSynchronous();
  GoldCoinClass = TSoftClassPtr<AGoldCoin>(FSoftObjectPath(*BattleNameSpace::GoldCoinPath)).LoadSynchronous();
  ReduceGoldCoinClass = TSoftClassPtr<AReduceGoldCoin>(FSoftObjectPath(*BattleNameSpace::ReduceGoldCoinPath)).LoadSynchronous();
  WoodBridgeClass = TSoftClassPtr<AWoodBridge>(FSoftObjectPath(*BattleNameSpace::WoodBridgePath)).LoadSynchronous();
  ArrowClass = TSoftClassPtr<AArrow>(FSoftObjectPath(*BattleNameSpace::ArrowPath)).LoadSynchronous();
}

/// <summary>
/// SpawnCharacter関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::SpawnCharacter(FVector& SpawnLoc) {

  CharacterClassesArray.Add(TypeACharacterClass);
  //CharacterClassesArray.Add(TypeBCharacterClass);
  //CharacterClassesArray.Add(TypeCCharacterClass);
  //CharacterClassesArray.Add(TypeDCharacterClass);

  CharactersArray.Add(TypeACharacter);
  //CharactersArray.Add(TypeBCharacter);
  //CharactersArray.Add(TypeCCharacter);
  //CharactersArray.Add(TypeDCharacter);

  float CornerX = SpawnLoc.X;
  float CornerY = SpawnLoc.Y;
  float CornerZ = SpawnLoc.Z;

  for (int32 i = 0; i < CharacterClassesArray.Num(); ++i) {
    //キャラクターをスポーンさせる
    if (CharactersArray[i] == nullptr) {

      FActorSpawnParameters params;
      CharactersArray[i] = GetWorld()->SpawnActor<APlayerCharacter>(CharacterClassesArray[i], FVector((CornerX), (CornerY), CornerZ + BattleNameSpace::SpawnDifferenceZ), FRotator::ZeroRotator, params);
    }
  }

}

/// <summary>
/// SpawnSquares関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::SpawnSquares() {
  //マスのBluePrintクラスをロードする
  TSubclassOf<ASquare> SquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*SquarePath)).LoadSynchronous();
  TSubclassOf<ASquare> BlueSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*BlueSquarePath)).LoadSynchronous();
  TSubclassOf<ASquare> RedSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*RedSquarePath)).LoadSynchronous();
  TSubclassOf<ASquare> YellowSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*YellowSquarePath)).LoadSynchronous();
  TSubclassOf<ASquare> StartSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*StartSquarePath)).LoadSynchronous();
  TSubclassOf<ASquare> GoalSquareClass = TSoftClassPtr<ASquare>(FSoftObjectPath(*GoalSquarePath)).LoadSynchronous();

  //ボードに配置するマスをスポーンさせる
  for (int i = 0; i < SquareNameSpace::Row; i++) {
    for (int j = 0; j < SquareNameSpace::Column; j++) {
      //ボードデータからマスのイベントの種類を取得する
      RoadType BoardRoadType = PreExistSquare->GetBoardData(j, i);
      //スポーン位置を設定する
      FVector SpawnLocation = CalculateSpawnPos(i,j);

      if (BoardRoadType != RoadType::NoRoad) {
        //木の橋をスポーンする
        WoodBridge = GetWorld()->SpawnActor<AWoodBridge>(WoodBridgeClass, FVector(SpawnLocation.X, SpawnLocation.Y, BattleNameSpace::SpawnBridgeHeight), FRotator::ZeroRotator);
      }

      //イベントの種類ごとに色分けしてスポーンさせる
      if (BoardRoadType == RoadType::Start)
      {
        ASquare* StartBoardSquare = GetWorld()->SpawnActor<ASquare>(StartSquareClass, SpawnLocation, FRotator::ZeroRotator);
        //SpawnCharacter(SpawnLocation);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
      else if (BoardRoadType == RoadType::Goal)
      {
        ASquare* GoalBoardSquare = GetWorld()->SpawnActor<ASquare>(GoalSquareClass, SpawnLocation, FRotator::ZeroRotator);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
      else if (BoardRoadType == RoadType::NoEvent)
      {
        ASquare* BoardSquare = GetWorld()->SpawnActor<ASquare>(SquareClass, SpawnLocation, FRotator::ZeroRotator);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
      else if (BoardRoadType == RoadType::IncreaseMoney)
      {
        ASquare* BlueBoardSquare = GetWorld()->SpawnActor<ASquare>(BlueSquareClass, SpawnLocation, FRotator::ZeroRotator);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
      else if (BoardRoadType == RoadType::DecreaseMoney)
      {
        ASquare* RedBoardSquare = GetWorld()->SpawnActor<ASquare>(RedSquareClass, SpawnLocation, FRotator::ZeroRotator);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
      else if (BoardRoadType == RoadType::ForceMove)
      {
        ASquare* YellowBoardSquare = GetWorld()->SpawnActor<ASquare>(YellowSquareClass, SpawnLocation, FRotator::ZeroRotator);
        PreExistSquare->AddTargetLocations(SpawnLocation);
      }
    }
  }
}

/// <summary>
/// CalculateSpawnPos関数の定義
/// </summary>
/// <param = "I">指定したX位置</param>
/// <param = "J">指定したY位置</param>
/// <returns>なし</returns>
FVector ABattleLevel::CalculateSpawnPos(int32 I,int32 J) {
  FVector Loc(BattleNameSpace::SpawnStartYPos + static_cast<float>(BattleNameSpace::SquareDistance * I), BattleNameSpace::SpawnStartXPos + static_cast<float>(BattleNameSpace::SquareDistance * J), BattleNameSpace::SpawnStartHeight);
  return Loc;
}

/// <summary>
/// IsCanWalk関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
bool ABattleLevel::IsCanWalk(RoadType Type) {
  //マスが存在するRoadTypeの場合のみ、trueにする
  if (Type == RoadType::Goal || Type == RoadType::NoEvent || Type == RoadType::IncreaseMoney || Type == RoadType::DecreaseMoney || Type == RoadType::ForceMove) {
    return true;
  }
  return false;
}

/// <summary>
/// DecideTargetAndPassed関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ABattleLevel::DecideTargetAndPassed(int32 X, int32 Y, FVector LastPassedLoc) {
  for (int32 j = 0; j < StaticCast<int32>(CharacterType::TypeMax); ++j) {
    if (CharacterKind == StaticCast<CharacterType>(j)) {

      //AIControllerを取得する
      ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[j].second->GetController());

      //進むことが可能なマスの位置を格納する配列
      TArray<FCharacterRouteAndDirection> CanWalkSquares;

      //通過したマス以外で進むことが可能なマスの位置を格納する配列
      TArray<FCharacterRouteAndDirection> RealCanWalkSquares;

      //進むことが可能なマスの位置を1つ格納する変数
      FCharacterRouteAndDirection CanWalkSquare;
      //通過したマス以外で進むことが可能なマスの位置を1つ格納する変数
      FCharacterRouteAndDirection RealCanWalkSquare;

      //キャラクターの向きの情報を取得する
      CharacterDirection CharacterDirectionType = CharacterClasses[j].second->GetCharacterDirection();

      //分かれ道ではない場合
      if (!bBranchRoad) {
        //現在のマスの種類を取得する
        RoadType NowRoadType = PreExistSquare->GetBoardData(Y, X);
        //右側のマスの種類を取得する
        RoadType RightRoadType = PreExistSquare->GetBoardData(Y + 1, X);
        if (IsCanWalk(RightRoadType)) {
          FVector Road = CalculateSpawnPos(X, Y + 1);
          CanWalkSquare.Direction = CharacterDirection::Right;
          CanWalkSquare.Location = Road;
          CanWalkSquares.Add(CanWalkSquare);
        }
        //左側のマスの種類を取得する
        RoadType LeftRoadType = PreExistSquare->GetBoardData(Y - 1, X);
        if (IsCanWalk(LeftRoadType)) {
          FVector Road = CalculateSpawnPos(X, Y - 1);
          CanWalkSquare.Direction = CharacterDirection::Left;
          CanWalkSquare.Location = Road;
          CanWalkSquares.Add(CanWalkSquare);
        }
        //前側のマスの種類を取得する
        RoadType FrontRoadType = PreExistSquare->GetBoardData(Y, X - 1);
        if (IsCanWalk(FrontRoadType)) {
          FVector Road = CalculateSpawnPos(X - 1, Y);
          CanWalkSquare.Direction = CharacterDirection::Front;
          CanWalkSquare.Location = Road;
          CanWalkSquares.Add(CanWalkSquare);
        }
        //進むことが可能なマスの数が複数ある場合
        if (CanWalkSquares.Num() > 1) {
          for (FCharacterRouteAndDirection Square : CanWalkSquares) {
            //SearchPassedLocationsを初期化する
            PreExistSquare->InitSearchPassedLocations();
            //現在のマスを探索用の通過済みのマスに追加する
            FVector Road = CalculateSpawnPos(X, Y);
            PreExistSquare->AddSearchPassedLocations(Road);
            //該当のマスのボードデータ上のX位置とY位置を取得する
            int32 SquareX = StaticCast<int32>(StaticCast<int32>(Square.Location.X - BattleNameSpace::SpawnStartYPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));
            int32 SquareY = StaticCast<int32>(StaticCast<int32>(Square.Location.Y - BattleNameSpace::SpawnStartXPos) / StaticCast<int32>(BattleNameSpace::SquareDistance));
            //順路とは逆方向のマスではないか確認する
            bool bIsNotBack = RouteSearch->IsNotBack(SquareX, SquareY);
            //既に通過済みのマスかを確認する
            bool IsPassed = PreExistSquare->CheckLocationIsPassed(Square.Location,j);
            if ((bIsNotBack) && (!IsPassed)) {
              //順路と逆方向のマスでも通過したマスでなければ、本当に進むことができるマスとして配列に追加
              RealCanWalkSquares.Add(Square);
            }
          }
          //通過済みではない進むことができるマスが複数ある場合、分かれ道と判定する
          if (RealCanWalkSquares.Num() > 1) {
            GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, "BranchRoad");
            UE_LOG(LogTemp, Warning, TEXT("BranchRoad"));
            bBranchRoad = true;
            //DiceNumを減らさずに、LastPassedLocationをターゲット位置にする
            Controller->SetTargetLoc(LastPassedLoc);
            //分かれ道での進むことが可能なマスと方向を保存する
            BranchSquares = RealCanWalkSquares;

          }
          //通過済みではなく進むことが可能なマスの数が1つの場合、そのマスを通過済みのマスにする
          else if (RealCanWalkSquares.Num() == 1) {
            FCharacterRouteAndDirection RealSquare = RealCanWalkSquares[0];
            PreExistSquare->AddPassedLocations(RealSquare.Location, j);
            int32 CornerSquaresNum = PreExistSquare->GetCornerLocationsNum();

            for (int32 i = 0; i < CornerSquaresNum; ++i) {
              FCharacterRouteAndDirection CornerSquare = PreExistSquare->GetCornerLocations(i);
              if (CornerSquare.Location == RealSquare.Location) {
                Controller->SetTargetLoc(RealSquare.Location);
                if ((DiceNum) > 0) {
                  bCorner = true;
                  DiceNum--;
                }
                break;
              }
            }
            if (!bCorner) {
              bFinishCorner = false;
              if (DiceNum > 0) {
                DiceNum--;
              }
              //DiceNumが0になったら、ターゲット位置を設定する
              if (DiceNum == 0) {
                Controller->SetTargetLoc(RealSquare.Location);
                FString DebugMessage26 = FString::Printf(TEXT("RealSquare.LocationX: %f"), RealSquare.Location.X);
                FString DebugMessage30 = FString::Printf(TEXT("RealSquare.LocationY: %f"), RealSquare.Location.Y);
                GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage26);
                GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage30);
              }
            }
            //キャラクターの向きの情報を設定する
            CharacterClasses[j].second->SetCharacterDirection(RealSquare.Direction);
          }
        }
        //進むことが可能なマスの数が1つの場合、そのマスを通過済みのマスにする
        else if (CanWalkSquares.Num() == 1) {
          FCharacterRouteAndDirection Square = CanWalkSquares[0];
          PreExistSquare->AddPassedLocations(Square.Location, j);
          int32 CornerSquaresNum = PreExistSquare->GetCornerLocationsNum();

          FString DebugMessage23 = FString::Printf(TEXT("CharacterDirectionType: %d"), CharacterDirectionType);
          GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage23);
          FString DebugMessage24 = FString::Printf(TEXT("Square.Direction: %d"), Square.Direction);
          GEngine->AddOnScreenDebugMessage(-1, BattleNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage24);

          //角のマスである場合
          for (int32 i = 0; i < CornerSquaresNum; ++i) {
            FCharacterRouteAndDirection CornerSquare = PreExistSquare->GetCornerLocations(i);
            if (CornerSquare.Location == Square.Location) {
              Controller->SetTargetLoc(Square.Location);
              if ((DiceNum) > 0) {
                bCorner = true;
                DiceNum--;
              }
              break;
            }
          }
          //角のマスではない場合
          if (!bCorner) {
            bFinishCorner = false;
            if (DiceNum > 0) {
              DiceNum--;
            }
            //DiceNumが0になったら、ターゲット位置を設定する
            if (DiceNum == 0) {
              Controller->SetTargetLoc(Square.Location);
            }
          }
          //キャラクターの向きの情報を設定する
          CharacterClasses[j].second->SetCharacterDirection(Square.Direction);
        }

        //進むことが可能なマスが無い場合、ゴールに到着した
        else if (CanWalkSquares.Num() == 0) {
          FVector GoalLocation = PreExistSquare->GetTargetLocations(0);
          PreExistSquare->AddPassedLocations(GoalLocation, j);
          Controller->SetTargetLoc(GoalLocation);
          DiceNum = 0;
          CharacterClasses[j].second->SetGoal(true);
        }
      }
    }
  }
}

/// <summary>
/// SetCharacterType関数の定義
/// </summary>
/// <param = "CharType">キャラクターの種類</param>
/// <returns>なし</returns>
void ABattleLevel::SetCharacterType(CharacterType CharType) {
  CharacterKind = CharType;
}

/// <summary>
/// GetCharacterType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターの種類</returns>
CharacterType ABattleLevel::GetCharacterType() {
  return CharacterKind;
}

/// <summary>
/// ChangeCharacterType関数の宣言
/// </summary>
/// <param = "CharIndex">キャラクターの要素番号</param>
/// <returns>なし</returns>
void ABattleLevel::ChangeCharacterType(int32 CharIndex) {
  //PlayerControllerを取得
  ABattleController* PlayerController = Cast<ABattleController>(GetWorld()->GetFirstPlayerController());
  //現在のターンのキャラクターのAIControllerを取得する
  ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[CharIndex].second->GetController());
  //次のターンのキャラクターの位置を設定するための変数
  FVector NextStartPos;
  //次のターンのキャラクターのAIControllerと開始位置を取得し、次のターンのキャラクターをマスの中心に戻す
  ACharacterAIController* NextController = Cast<ACharacterAIController>(TypeACharacterChild->GetController());
  if (CharacterKind != CharacterType::TypeD) {
    NextController = Cast<ACharacterAIController>(CharacterClasses[CharIndex + 1].second->GetController());
    NextStartPos = PreExistSquare->GetLastPassedLocations(CharIndex + 1);
    CharacterClasses[CharIndex + 1].second->SetActorLocation(FVector(NextStartPos.X, NextStartPos.Y, NextStartPos.Z + BattleNameSpace::ChangeLocZ));
  }
  else if (CharacterKind == CharacterType::TypeD) {
    NextStartPos = PreExistSquare->GetLastPassedLocations(0);
    TypeACharacterChild->SetActorLocation(FVector(NextStartPos.X, NextStartPos.Y, NextStartPos.Z + BattleNameSpace::ChangeLocZ));
  }

  // 次のターンのキャラクターのビヘイビアツリーを再開する
  NextController->GetBrainComponent()->RestartLogic();

  // キャラクターの種類を次のキャラクターにし、カメラも次のキャラクターに切り替える
  if (StaticCast<int32>(CharacterKind) < StaticCast<int32>(CharacterType::TypeD)) {
    CharacterKind = StaticCast<CharacterType>(CharIndex + 1);
    PlayerController->SetViewTargetWithBlend(CharacterClasses[CharIndex + 1].second, BattleNameSpace::SmoothBlendTime);
  }
  else if (CharacterKind == CharacterType::TypeD) {
    CharacterKind = CharacterType::TypeA;
    PlayerController->SetViewTargetWithBlend(TypeACharacterChild, BattleNameSpace::SmoothBlendTime);
  }
  // 現在のターンのキャラクターのビヘイビアツリーを一時停止する
  Controller->GetBrainComponent()->StopLogic("StopLogic");
}

/// <summary>
/// CheckOverlapWithOther関数の宣言
/// </summary>
/// <param = "CharIndex">現在のターンのキャラクターの要素番号</param>
/// <returns>止まったマスに既に止まっている他のキャラクターの人数</returns>
int32 ABattleLevel::CheckOverlapWithOther(int32 CharIndex) {
  FVector LastPassedLocations[DiceNameSpace::Four];

  // すべてのキャラクターの最後に通過した場所を取得
  for (int j = 0; j < DiceNameSpace::Four; ++j)
  {
    LastPassedLocations[j] = PreExistSquare->GetLastPassedLocations(j);
  }

  if (CharIndex == - 1) {
    CharIndex = StaticCast<int32>(CharacterType::TypeD);
  }

  // 前回のターンのキャラクターの最後に通過した場所を取得
  FVector LastPassedLocation = PreExistSquare->GetLastPassedLocations(CharIndex);

  // 最後に通過した場所が一致する数を格納する変数
  int32 Count = 0;

  // 他のキャラクターの最後に通過したマスと一致する場合、Countを増やす
  for (int j = 0; j < DiceNameSpace::Four; ++j)
  {
    if ((LastPassedLocation == LastPassedLocations[j]) && (j != CharIndex)) {
      Count++;
    }
  }
  return Count;
}

/// <summary>
/// ChangeCharacterPos関数の宣言
/// </summary>
/// <param = "Character">キャラクター</param>
/// <returns>なし</returns>
void ABattleLevel::ChangeCharacterPos(int32 CharIndex) {
  // 同じマスにいる他のキャラクターの数を取得する
  int32 OverlapNum = CheckOverlapWithOther(CharIndex - 1);
  // 位置の微調整の値を定数から取得する
  float ChangeLocX = BattleNameSpace::ChangeLocX;
  float ChangeLocY = BattleNameSpace::ChangeLocY;
  float ChangeLocZ = BattleNameSpace::ChangeLocZ;

  // OverlapNumが2か3の場合、ChangeLocXをマイナスにする
  if (OverlapNum > 1) {
    ChangeLocX = - ChangeLocX;
  }
  // OverlapNumが奇数の場合、ChangeLocYをマイナスにする
  if (OverlapNum % DiceNameSpace::Two == 1) {
    ChangeLocY = - ChangeLocY;
  }

  for (int32 i = 0; i < StaticCast<int32>(CharacterType::TypeMax); ++i) {
    if (OverlapNum == i) {
      if (CharacterKind == CharacterType::TypeA) {
        //前のターンのキャラクターの現在位置を取得する
        FVector PreTurnCharacterPos = PreExistSquare->GetLastPassedLocations(StaticCast<int32>(CharacterType::TypeD));
        //TypeDのキャラクターが最初のターンであるか確認する
        bool IsFirstTurn = TypeDCharacter->GetFirstTurn();
        if (!IsFirstTurn) {
          //初めてのターンでなければ、前のターンのキャラクターの位置を調整する
          TypeDCharacter->SetActorLocation(FVector(PreTurnCharacterPos.X + ChangeLocX, PreTurnCharacterPos.Y + ChangeLocY, PreTurnCharacterPos.Z + BattleNameSpace::ChangeLocZ));
        }
      }
      else if (CharacterKind != CharacterType::TypeA) {
        //前のターンのキャラクターの現在位置を取得する
        FVector PreTurnCharacterPos = PreExistSquare->GetLastPassedLocations(CharIndex - 1);
        //前のターンのキャラクターの位置を調整する
        CharacterClasses[CharIndex - 1].second->SetActorLocation(FVector(PreTurnCharacterPos.X + ChangeLocX, PreTurnCharacterPos.Y + ChangeLocY, PreTurnCharacterPos.Z + BattleNameSpace::ChangeLocZ));
      }
    }
  }
}

/// <summary>
/// SetArrowRightLeft関数の定義
/// </summary>
/// <param = "CharDirection">キャラクターの向き</param>
/// <returns>なし</returns>
void ABattleLevel::SetArrowRightLeft() {
  //90度回転させる角度を定数から取得する
  float RightAngle = BattleNameSpace::RightAngle;

  if (BranchSquares[0].Direction == CharacterDirection::Right) {
    //Aキーが押された場合
    if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::A)) {
      SpawnAndSetArrow(RightAngle);
    }
  }
  else if (BranchSquares[0].Direction == CharacterDirection::Left) {
    //９０度の角度を反転させる
    RightAngle = - RightAngle;

    //Dキーが押された場合
    if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::D) || CharacterKind == CharacterType::TypeB) {
      SpawnAndSetArrow(RightAngle);
    }
  }
}

/// <summary>
/// SpawnAndSetArrow関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::SpawnAndSetArrow(float RightAngle) {
  if (!IsValid(Arrow)) {
    Arrow = GetWorld()->SpawnActor<AArrow>(ArrowClass, FVector(BranchSquares[0].Location.X, BranchSquares[0].Location.Y, BranchSquares[0].Location.Z + BattleNameSpace::ChangeAngle), FRotator(0.0f, 0.0f, RightAngle));
  }
  if (IsValid(Arrow)) {
    Arrow->ResetAccumulatedTime();
    //矢印の位置と向きを変更する
    Arrow->SetActorLocationAndRotation(FVector(BranchSquares[0].Location.X, BranchSquares[0].Location.Y, BranchSquares[0].Location.Z + BattleNameSpace::ChangeAngle), FRotator(0.0f, 0.0f, RightAngle));
    //矢印の方向を設定する
    Arrow->SetArrowDirection((StaticCast<ArrowDirection>(StaticCast<int32>(BranchSquares[0].Direction))));
  }
}

/// <summary>
/// SetArrowFront関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleLevel::SetArrowFront(FVector Target) {
  if (!IsValid(Arrow)) {
    Arrow = GetWorld()->SpawnActor<AArrow>(ArrowClass, FVector(Target.X, Target.Y, Target.Z + BattleNameSpace::ChangeAngle), FRotator(BattleNameSpace::RightAngle, 0.0f, 0.0f));
  }
  if (IsValid(Arrow)) {
    //矢印の位置と向きを変更する
    Arrow->SetActorLocationAndRotation(FVector(Target.X, Target.Y, Target.Z + BattleNameSpace::ChangeAngle), FRotator(BattleNameSpace::RightAngle, 0.0f, 0.0f));
    //矢印の方向を設定する
    Arrow->SetArrowDirection(ArrowDirection::Front);
  }
}

/// <summary>
/// FinishCoinEvent関数の定義
/// </summary>
/// <param = "I">コインの要素番号</param>
/// <param = "J">キャラクターのインデックス</param>
/// <param = "IsCoinIncreased">コインが増えたフラグ</param>
/// <param = "IsCoinDecreased">コインが減ったフラグ</param>
/// <returns>なし</returns>
void ABattleLevel::FinishCoinEvent(int32 I, int32 J, bool IsCoinIncreased, bool IsCoinDecreased) {
  //一定時間経過後にコインを消す
  if (CoinAccumulatedTimes[I] >= (GoldCoinNameSpace::ResetTime)) {

    //コインが増えたイベントの場合
    if (IsCoinIncreased) {
      GoldCoins[I]->Destroy();
      GoldCoins[I] = nullptr;
    }
    //コインが減ったイベントの場合
    else if (IsCoinDecreased) {
      ReduceGoldCoins[I]->Destroy();
      ReduceGoldCoins[I] = nullptr;
    }

    //アニメーションを元に戻す
    CharacterClasses[J].second->SwitchAnimation();
    if (CoinAccumulatedTimes[CoinNumNameSpace::CoinChangeAmount - 1] >= (GoldCoinNameSpace::ResetTime) * (CoinNumNameSpace::CoinChangeAmount - 1)) {
      bCoinIncreased = false;
      bCoinDecreased = false;
      //サイコロを振る状態に遷移する
      Phase = TurnType::WaitingRollDice;
      //累積時間をリセットする
      CoinStartAccumulatedTime = 0.0f;
      for (int32 k = 0; k < GoldCoins.Num(); ++k) {
        CoinAccumulatedTimes[k] = 0.0f;
      }
      //ターンを次のキャラクターに変更する
      ChangeCharacterType(J);
    }
  }
}

/// <summary>
/// AnimCoin関数の定義
/// </summary>
/// <param = "J">キャラクターのインデックス</param>
/// <param = "IsCoinIncreased">コインが増えたフラグ</param>
/// <param = "IsCoinDecreased">コインが減ったフラグ</param>
/// <param = "CoinSpawnLocation">コイン増加時のスポーン位置</param>
/// <param = "ReduceCoinSpawnLocation">コイン減少時のスポーン位置</param>
/// <param = "CoinSpawnRotation">コインスポーン時の回転</param>
/// <param = "DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ABattleLevel::AnimCoin(int32 J, bool IsCoinIncreasedFlag, bool IsCoinDecreasedFlag, FVector CoinSpawnLocation, FVector ReduceCoinSpawnLocation, FRotator CoinSpawnRotation, float DeltaTime) {
  for (int32 i = 0; i < GoldCoins.Num(); ++i) {
    if (CoinStartAccumulatedTime >= (i * ReduceGoldCoinNameSpace::CoinStartTime)) {
      if (IsCoinIncreasedFlag) {
        if (GoldCoins[i] == nullptr) {
          // コインをスポーンする
          GoldCoins[i] = GetWorld()->SpawnActor<AGoldCoin>(GoldCoinClass, CoinSpawnLocation, CoinSpawnRotation);
          //キャラクターの状態を切り替える
          CharacterClasses[J].second->SetCharacterStatus(CharacterStatus::Happy);
        }
      }
      else if (IsCoinDecreasedFlag) {
        if (ReduceGoldCoins[i] == nullptr) {
          // コインをスポーンする
          ReduceGoldCoins[i] = GetWorld()->SpawnActor<AReduceGoldCoin>(ReduceGoldCoinClass, ReduceCoinSpawnLocation, CoinSpawnRotation);
          //キャラクターの状態を切り替える
          CharacterClasses[J].second->SetCharacterStatus(CharacterStatus::Regret);
        }
      }
      //アニメーションを切り替える
      CharacterClasses[J].second->SwitchAnimation();
      CoinAccumulatedTimes[i] = CoinAccumulatedTimes[i] + DeltaTime;
    }
    // スポーンしてから一定時間経過後にコインを消す
    FinishCoinEvent(i, J, bCoinIncreased, bCoinDecreased);
  }
}

/// <summary>
/// SetForceMove関数の定義
/// </summary>
/// <param = "CharIndex">キャラクターの要素番号</param>
/// <returns>なし</returns>
void ABattleLevel::SetForceMove(int32 CharIndex) {
  //通過済みのマスの数を取得する
  int32 PassedLocationsNum = PreExistSquare->GetPassedLocationsNum(CharIndex);
  //強制移動の目的位置
  FVector ForceMovedLocation = PreExistSquare->GetPassedLocations(PassedLocationsNum - BattleNameSpace::UTurnWalkNum - 1 + AfterCornerNum, CharIndex);
  //AIControllerを取得する
  ACharacterAIController* Controller = Cast<ACharacterAIController>(CharacterClasses[CharIndex].second->GetController());
  //途中で道の角がない場合は、5マス下がったマスをそのまま目的位置とする
  Controller->SetTargetLoc(ForceMovedLocation);

  bool bFinishSearch = false;

  //5マス以内に角のマスが見つかった場合、角のマスを目的位置とする
  for (int32 i = 0; i < (BattleNameSpace::UTurnWalkNum - AfterCornerNum); ++i) {
    //通過済みのマスからi番目の位置を取得する
    FVector Location = PreExistSquare->GetPassedLocations(PassedLocationsNum - (i + 1) - 1, CharIndex);
    //戻るマスを通過済みのマスから除外する
    PreExistSquare->RemovePassedLocationsElement(PassedLocationsNum - (i + 1), CharIndex);
    int32 CornerSquaresNum = PreExistSquare->GetCornerLocationsNum();
    //角のマスを格納している配列から要素を取り出し、i番目のマスと一致した場合、そのマスを目的位置とする
    for (int32 k = 0; k < CornerSquaresNum; ++k) {
      FCharacterRouteAndDirection CornerSquare = PreExistSquare->GetCornerLocations(k);
      if (CornerSquare.Location == Location) {
        Controller->SetTargetLoc(Location);
        AfterCornerNum = AfterCornerNum + (i + 1);
        bFinishSearch = true;
        break;
      }
    }
    if (bFinishSearch) {
      break;
    }
    //合計5マス移動後にbForceMoveをtrueにする
    if (i == (BattleNameSpace::UTurnWalkNum - AfterCornerNum - 1)) {
      bForceMove = true;
    }
  }

  //AfterCornerNumが5になった場合も5マス移動したことになるので、bForceMoveをtrueにする
  if (AfterCornerNum == BattleNameSpace::UTurnWalkNum) {
    bForceMove = true;
  }

}

/// <summary>
/// GetRandomNum関数の定義
/// </summary>
/// <param = "Min">最小値</param>
/// <param = "Max">最大値</param>
/// <returns>ランダムな整数</returns>
int32 ABattleLevel::GetRandomNum(int32 Min, int32 Max)
{
  // 指定した範囲のランダムな整数を生成
  int32 RandomNumber = FMath::RandRange(Min, Max);
  return RandomNumber;
}

/// <summary>
/// IsFrontOnlyCharacter関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ランダムな整数</returns>
bool ABattleLevel::IsFrontOnlyCharacter(CharacterType CharType) {
  if (CharacterKind == CharacterType::TypeC || CharacterKind == CharacterType::TypeD) {
    return true;
  }
  return false;
}