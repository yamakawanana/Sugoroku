#include "Battle/AI/CharacterAIController.h"
#include "Battle/PlayerCharacter/PlayerCharacter.h"
#include "Battle/Square/Square.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param = "PCIP">ObjectInitializer型のPCIPの参照</param>
/// <returns>なし</returns>
ACharacterAIController::ACharacterAIController(const class FObjectInitializer& PCIP)
  : Super(PCIP)
  , NowPosX(0)
  , NowPosY(0)
  , SquareIndex(1)
{
  // BlackBoardコンポーネントを作成
  Bb = CreateDefaultSubobject <UBlackboardComponent>(TEXT("Black Board"));
}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ACharacterAIController::BeginPlay()
{
  Super::BeginPlay();

  // ASquareのアクターを取得
  SquareClass = ASquare::StaticClass();
  TArray<AActor*> Squares;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), SquareClass, Squares);

  if (Squares.Num())
  {
    Square = Cast<ASquare>(Squares[0]);
    FString message = FString("Squares:") + Square->GetName();
    GEngine->AddOnScreenDebugMessage(-1, CharacterAIControllerNameSpace::TimeToDisplay, FColor::Cyan, message);
  }

  if (IsValid(Bt)) {
    //ビヘイビアツリーを起動
    RunBehaviorTree(Bt);
  }

}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ACharacterAIController::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

/// <summary>
/// DecideTargetPoint関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ACharacterAIController::DecideTargetPoint() {

  if (IsValid(Bb)) {

    //キー名を「WayPoint1」とする
    FString Key = "WayPoint1";

    SquareIndex++;

    // 古いターゲットポイントを削除する
    for (AActor* TargetPoint : WayPointTarget)
    {
      TargetPoint->Destroy();
    }
    WayPointTarget.Empty();

    int32 NumElements = Square->GetTargetLocationsNum();

    //新しいターゲットポイントをスポーンする
    ATargetPoint* TargetPoint = GetWorld()->SpawnActor<ATargetPoint>();
    //指定の位置をターゲットポイントに設定する
    TargetPoint->SetActorLocation(FVector(NewTargetLoc.X, NewTargetLoc.Y, NewTargetLoc.Z));
    //ターゲットポイントを配列に追加する
    WayPointTarget.Add(TargetPoint);
    //ターゲットポイントをBlackBoardの値として設定する
    Bb->SetValueAsObject(*Key, WayPointTarget[0]);

    //以下、WayPoint1が設定されていることの確認用に記載
    UObject* Obj = Bb->GetValueAsObject("WayPoint1");
    AActor* WayPointTargetActorTestObj = Cast<AActor>(Obj);
    FVector WayPointTargetActorTestObjVec = WayPointTargetActorTestObj->GetActorLocation();

    GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Bb");
    UE_LOG(LogTemp, Warning, TEXT("Bb"));
  }
  else {
    GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Bbが無効");
    UE_LOG(LogTemp, Warning, TEXT("Bbが無効"));
  }
}

/// <summary>
/// GetTargetPoint関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FVector ACharacterAIController::GetTargetPoint() {
  //位置情報を格納する変数を用意する
  FVector Location;
  
  for (ATargetPoint* TargetPoint : WayPointTarget)
  {
    if (TargetPoint)
    {
      //WayPointTargetに格納されているTargetPointの位置をLocationに格納する
      Location = TargetPoint->GetActorLocation();
      UE_LOG(LogTemp, Warning, TEXT("Waypointの位置: %s"), *Location.ToString());
    }
  }
  return Location;
}

/// <summary>
/// SetTargetLoc関数の定義
/// </summary>
/// <param = "Loc">ターゲット位置</param>
/// <returns>なし</returns>
void ACharacterAIController::SetTargetLoc(FVector Loc) {
  //ターゲット位置を設定する
  NewTargetLoc = Loc;
}

