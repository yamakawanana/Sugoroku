#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/Square/Square.h"
#include "Battle/File/CSVFileManager.h"
#include "Battle/RouteSearch/RouteSearch.h"
#include "Battle/PlayerCharacter/PlayerCharacter.h"
#include "Battle/CoinNum/CoinNum.h"
#include "Battle/WoodBridge/WoodBridge.h"
#include "Battle/Arrow/Arrow.h"
#include "Math/UnrealMathUtility.h"
#include "Camera/CameraActor.h"
#include "BattleLevel.generated.h"

/// <summary>
/// 名前空間BattleNameSpace
/// </summary>
namespace BattleNameSpace {

  /// <summary>
  /// 表示時間を定数TimeToDisplayに格納する
  /// </summary>
  static const float TimeToDisplay = 5.0f;

  /// <summary>
  /// マスをスポーンさせる開始Y位置を定数SpawnStartYPosに格納する
  /// </summary>
  static const float SpawnStartYPos = -80.0f;

  /// <summary>
  /// マスをスポーンさせる開始X位置を定数SpawnStartXPosに格納する
  /// </summary>
  static const float SpawnStartXPos = -450.0f;

  /// <summary>
  /// マスをスポーンさせる開始高さを定数SpawnStartHeightに格納する
  /// </summary>
  static const float SpawnStartHeight = -130.0f;

  /// <summary>
  /// 木の橋をスポーンさせる開始高さを定数SpawnBridgeHeightに格納する
  /// </summary>
  static const float SpawnBridgeHeight = -230.0f;

  /// <summary>
  /// マスとマスの間隔を定数SquareDistanceに格納する
  /// </summary>
  static const int32 SquareDistance = 400;

  /// <summary>
  /// 強制移動で戻る歩数を定数UTurnWalkNumに格納する
  /// </summary>
  static const int32 UTurnWalkNum = 5;

  /// <summary>
  /// マスとキャラクターのスポーン高さの差を定数SpawnDifferenceZに格納する
  /// </summary>
  static const float SpawnDifferenceZ = 90.0f;

  /// <summary>
  /// キャラクターAのパスを定数TypeACharacterPathに格納する
  /// </summary>
  static const FString TypeACharPath = "/Game/Blueprints/BP_TypeACharacter.BP_TypeACharacter_C";

  /// <summary>
  /// TypeACharChildのパスを定数TypeACharChildPathに格納する
  /// </summary>
  static const FString TypeACharChildPath = "/Game/Blueprints/BP_TypeACharacter_Child.BP_TypeACharacter_Child_C";

  /// <summary>
  /// キャラクターBのパスを定数TypeBCharacterPathに格納する
  /// </summary>
  static const FString TypeBCharPath = "/Game/Blueprints/BP_TypeBCharacter2.BP_TypeBCharacter2_C";

  /// <summary>
  /// キャラクターCのパスを定数TypeCCharacterPathに格納する
  /// </summary>
  static const FString TypeCCharPath = "/Game/Blueprints/BP_TypeCCharacter.BP_TypeCCharacter_C";

  /// <summary>
  /// キャラクターDのパスを定数TypeDCharacterPathに格納する
  /// </summary>
  static const FString TypeDCharPath = "/Game/Blueprints/BP_TypeDCharacter.BP_TypeDCharacter_C";

  /// <summary>
  /// 白いマスのパスを定数SquarePathに格納する
  /// </summary>
  static const FString SqPath = "/Game/Blueprints/BP_Square.BP_Square_C";

  /// <summary>
  /// 青いマスのパスを定数BlueSquarePathに格納する
  /// </summary>
  static const FString BlueSqPath = "/Game/Blueprints/BP_BlueSquare.BP_BlueSquare_C";

  /// <summary>
  /// 赤いマスのパスを定数RedSquarePathに格納する
  /// </summary>h
  static const FString RedSqPath = "/Game/Blueprints/BP_RedSquare.BP_RedSquare_C";

  /// <summary>
  /// 黄色いマスのパスを定数YellowSquarePathに格納する
  /// </summary>
  static const FString YellowSqPath = "/Game/Blueprints/BP_YellowSquare.BP_YellowSquare_C";

  /// <summary>
  /// スタートのマスのパスを定数StartSquarePathに格納する
  /// </summary>
  static const FString StartSqPath = "/Game/Blueprints/BP_StartSquare.BP_StartSquare_C";

  /// <summary>
  /// ゴールのマスのパスを定数GoalSquarePathに格納する
  /// </summary>
  static const FString GoalSqPath = "/Game/Blueprints/BP_GoalSquare.BP_GoalSquare_C";

  /// <summary>
  /// 経路探索のパスを定数SearchRtPathに格納する
  /// </summary>
  static const FString SearchRtPath = "/Game/Blueprints/BP_RouteSearch.BP_RouteSearch_C";

  /// <summary>
  /// ファイルマネージャーのパスを定数SearchRtPathに格納する
  /// </summary>
  static const FString FileManagPath = "/Game/Blueprints/BP_CSVFileManager.BP_CSVFileManager_C";

  /// <summary>
  /// サイコロのパスを定数DicePathに格納する
  /// </summary>
  static const FString DicePath = "/Game/Blueprints/BP_Dice.BP_Dice_C";

  /// <summary>
  /// 所持金表示のパスを定数CoinNumPathに格納する
  /// </summary>
  static const FString CoinNumPath = "/Game/Blueprints/BP_CoinNum.BP_CoinNum_C";

  /// <summary>
  /// コインのパスを定数GoldCoinPathに格納する
  /// </summary>
  static const FString GoldCoinPath = "/Game/Blueprints/BP_GoldCoin.BP_GoldCoin_C";

  /// <summary>
  /// 減少時のコインのパスを定数ReduceGoldCoinPathsに格納する
  /// </summary>
  static const FString ReduceGoldCoinPath = "/Game/Blueprints/BP_ReduceGoldCoin.BP_ReduceGoldCoin_C";

  /// <summary>
  /// 木の橋のパスを定数WoodBridgePathに格納する
  /// </summary>
  static const FString WoodBridgePath = "/Game/Blueprints/BP_WoodBridge.BP_WoodBridge_C";

  /// <summary>
  /// 矢印のパスを定数ArrowPathに格納する
  /// </summary>
  static const FString ArrowPath = "/Game/Blueprints/BP_Arrow.BP_Arrow_C";

  /// <summary>
  /// ターゲットポイントのX位置を微調整する値を定数MiniAdjustmentXに格納する
  /// </summary>
  static const float MiniAdjustmentX = 100.0f;

  /// <summary>
  /// ターゲットポイントのX位置を大きく調整する値を定数BigAdjustmentXに格納する
  /// </summary>
  static const float BigAdjustmentX = 200.0f;

  /// <summary>
  /// CameraのX位置を調整する値を定数CameraChangeXに格納する
  /// </summary>
  static const float CameraChangeX = 350.0f;

  /// <summary>
  /// CameraのX位置を調整する値を定数CameraChangeZに格納する
  /// </summary>
  static const float CameraChangeZ = 200.0f;

  /// <summary>
  //キューで管理するデータ数の上限
  /// <summary>
  static const int32 QueueSize = 120;

  /// <summary>
  /// 90度回転する時の角度を定数RightAngleに格納する
  /// </summary>
  static const float RightAngle = 90.0f;

  /// <summary>
  /// 分かれ道で調整する角度を定数ChangeAngleに格納する
  /// </summary>
  static const float ChangeAngle = 20.0f;

  /// <summary>
  /// 微調整するX位置を定数ChangeLocXに格納する
  /// </summary>
  static const float ChangeLocX = 80.0f;

  /// <summary>
  /// 微調整するY位置を定数ChangeLocYに格納する
  /// </summary>
  static const float ChangeLocY = 80.0f;

  /// <summary>
  /// 微調整するZ位置を定数ChangeLocZに格納する
  /// </summary>
  static const float ChangeLocZ = 95.0f;

  /// <summary>
  /// カメラを切り替える時のブレンド時間を定数SmoothBlendTimeに格納する
  /// </summary>
  static const float SmoothBlendTime = 0.75f;

  /// <summary>
  /// カメラを切り替える時のブレンド時間を定数SecondSmoothBlendTimeに格納する
  /// </summary>
  static const float SecondSmoothBlendTime = 0.25f;

  /// <summary>
  /// 全体マップ表示時に微調整するZ位置を定数AllMapChangeLocZに格納する
  /// </summary>
  static const float AllMapChangeLocX = 700.0f;

  /// <summary>
  /// 全体マップ表示時に微調整するZ位置を定数AllMapChangeLocZに格納する
  /// </summary>
  static const float AllMapChangeLocZ = 6300.0f;

  /// <summary>
  /// 全体マップ表示時に微調整するPitchを定数AllMapChangePitchに格納する
  /// </summary>
  static const float AllMapChangePitch = 50.0f;
}

/**
 *
 */

 /// <summary>
 /// TurnType列挙体の定義
 /// </summary>
UENUM(BlueprintType)
enum class TurnType : uint8 {

  /// </summary>
  //　サイコロを振る入力待ち
  /// </summary>
  WaitingRollDice,

  /// </summary>
  //　出目確定アニメーション
  /// </summary>
  DecideNumAnim,

  /// </summary>
  //　動き始めるフェーズ
  /// </summary>
  StartMove,

  /// </summary>
  //　マス移動アニメーション
  /// </summary>
  MoveAnim,

  /// </summary>
  //　移動途中のマスに着地したフェーズ
  /// </summary>
  OnTheWay,

  /// </summary>
  //　マスイベントUI表示
  /// </summary>
  DisplayEventUi,

  /// </summary>
  //　マスイベント実行結果UI表示
  /// </summary>
  DisplayEventResultUi,

  /// </summary>
  //　コイン増加イベント
  /// </summary>
  NoEventPhase,

  /// </summary>
  //　コイン増加イベント
  /// </summary>
  CoinIncreaseEvent,

  /// </summary>
  //　コイン減少イベント
  /// </summary>
  CoinDecreaseEvent,

  /// </summary>
  //　強制移動イベント
  /// </summary>
  ForceMoveEvent,

  /// </summary>
  //　分かれ道
  /// </summary>
  BranchRoad,
};

/// <summary>
/// CharacterType列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class CharacterType : uint8 {
  /// </summary>
  //　TypeA
  /// </summary>
  TypeA,

  /// </summary>
  //　TypeB
  /// </summary>
  TypeB,

  /// </summary>
  //　TypeC
  /// </summary>
  TypeC,

  /// </summary>
  //　TypeD
  /// </summary>
  TypeD,

  /// </summary>
  //　種類の最大値
  /// </summary>
  TypeMax,
};

/// <summary>
/// BattleLevelクラス
/// </summary>
UCLASS()
class ABattleLevel : public ALevelScriptActor
{
  GENERATED_BODY()

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ABattleLevel();

  /// <summary>
  /// スポーンポイント
  /// </summary>
  UPROPERTY(EditAnywhere, Category = "SpawnPoint")
  ATargetPoint* SpawnPoint;

  /// <summary>
  /// 撮影ポイント
  /// </summary>
  UPROPERTY(EditAnywhere, Category = "SpawnPoint")
  ATargetPoint* FilmingPoint;

  /// </summary>
  //　フェーズ
  /// </summary>
  UPROPERTY()
  TurnType Phase;

  /// <summary>
  /// キャラクターAのパス
  /// </summary>
  UPROPERTY()
  FString TypeACharacterPath;

  /// <summary>
  /// TypeACharacterChildのパス
  /// </summary>
  UPROPERTY()
  FString TypeACharacterChildPath;

  /// <summary>
  /// キャラクターBのパス
  /// </summary>
  UPROPERTY()
  FString TypeBCharacterPath;

  /// <summary>
  /// キャラクターCのパス
  /// </summary>
  UPROPERTY()
  FString TypeCCharacterPath;

  /// <summary>
  /// キャラクターDのパス
  /// </summary>
  UPROPERTY()
  FString TypeDCharacterPath;

  /// <summary>
  /// 白いマスのパス
  /// </summary>
  UPROPERTY()
  FString SquarePath;

  /// <summary>
  /// 青いマスのパス
  /// </summary>
  UPROPERTY()
  FString BlueSquarePath;

  /// <summary>
  /// 赤いマスのパス
  /// </summary>
  UPROPERTY()
  FString RedSquarePath;

  /// <summary>
  /// 黄色いマスのパス
  /// </summary>
  UPROPERTY()
  FString YellowSquarePath;

  /// <summary>
  /// スタートのマスのパス
  /// </summary>
  UPROPERTY()
  FString StartSquarePath;

  /// <summary>
  /// ゴールのマスのパス
  /// </summary>
  UPROPERTY()
  FString GoalSquarePath;

  /// <summary>
  /// 経路探索のパス
  /// </summary>
  UPROPERTY()
  FString RouteSearchPath;

  /// <summary>
  /// ファイルマネージャーのパス
  /// </summary>
  UPROPERTY()
  FString FileManagerPath;

  /// <summary>
  /// サイコロの出目
  /// </summary>
  int32 DiceNum;

  /// <summary>
  /// 分かれ道に来たかのフラグ
  /// </summary>
  bool bBranchRoad;

  /// <summary>
  /// 所持金を増やしたフラグ
  /// </summary>
  bool bCoinIncreased;

  /// <summary>
  /// 所持金を減らしたフラグ
  /// </summary>
  bool bCoinDecreased;

  /// <summary>
  /// 強制移動中のフラグ
  /// </summary>
  bool bForceMove;

  /// <summary>
  /// 分かれ道以外の曲がり角に来ているかのフラグ
  /// </summary>
  bool bCorner;

  /// <summary>
  /// 分かれ道を抜けたフラグ
  /// </summary>
  bool bFinishBranch;

  /// <summary>
  /// 曲がり角を抜けたフラグ
  /// </summary>
  bool bFinishCorner;

  /// <summary>
  /// 分かれ道での進むことが可能なマスと方向を保存する配列
  /// </summary>
  TArray<FCharacterRouteAndDirection> BranchSquares;

  /// <summary>
  /// 強制移動の途中で曲がり角を通った際に使用する変数
  /// </summary>
  int32 AfterCornerNum;

  /// <summary>
  /// 分かれ道に来た時にカメラ位置を変更したフラグ
  /// </summary>
  bool bBranchCameraChange;

  /// <summary>
  /// 全体マップ表示時にカメラ位置を変更したフラグ
  /// </summary>
  bool bAllMapCameraChange;

  /// <summary>
  /// 前回フレームのカメラ位置
  /// </summary>
  FVector PreCameraLocation;

  /// <summary>
  /// 前回フレームのカメラ回転
  /// </summary>
  FRotator PreCameraRotation;

  /// <summary>
  /// 新しいカメラ位置
  /// </summary>
  FVector NewCameraLocation;

  /// <summary>
  /// 新しいカメラ回転
  /// </summary>
  FRotator NewCameraRotation;

  /// <summary>
  /// ブレンド中であるフラグ
  /// </summary>
  bool bIsBlending;

  /// <summary>
  /// 位置を更新したかのFlag
  /// </summary>
  bool bUpdateLocation;

  /// <summary>
  /// 全体マップ表示時の位置を更新したかのFlag
  /// </summary>
  bool bAllMapUpdateLocation;

  /// <summary>
  /// 全体マップ表示時の位置を更新したかのFlag
  /// </summary>
  bool bReverseAllMapLocation;

  /// <summary>
  /// 全体マップ表示する時のカメラ位置
  /// </summary>
  FVector AllMapCameraLocation;

  /// <summary>
  /// 全体マップ表示する時のカメラ回転
  /// </summary>
  FRotator AllMapCameraRotation;

  /// <summary>
  /// 全体マップ表示する前のカメラ位置
  /// </summary>
  FVector PreAllMapCameraLocation;

  /// <summary>
  /// 全体マップ表示する前のカメラ回転
  /// </summary>
  FRotator PreAllMapCameraRotation;

private:

  /// <summary>
  // TypeACharacterクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class APlayerCharacter> TypeACharacterClass;

  /// <summary>
  // TypeACharacter
  /// <summary>
  UPROPERTY()
  APlayerCharacter* TypeACharacter;

  /// <summary>
  // TypeACharacterChildクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class APlayerCharacter> TypeACharacterChildClass;

  /// <summary>
  // TypeACharacterChild
  /// <summary>
  UPROPERTY()
  APlayerCharacter* TypeACharacterChild;

  /// <summary>
  // TypeBCharacterクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class APlayerCharacter> TypeBCharacterClass;

  /// <summary>
  // TypeBCharacter
  /// <summary>
  UPROPERTY()
  APlayerCharacter* TypeBCharacter;

  /// <summary>
  // TypeCCharacterクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class APlayerCharacter> TypeCCharacterClass;

  /// <summary>
  // TypeCCharacter
  /// <summary>
  UPROPERTY()
  APlayerCharacter* TypeCCharacter;

  /// <summary>
  // TypeDCharacterクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class APlayerCharacter> TypeDCharacterClass;

  /// <summary>
  // TypeDCharacter
  /// <summary>
  UPROPERTY()
  APlayerCharacter* TypeDCharacter;

  /// </summary>
  // キャラクターの種類
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterType", meta = (AllowPrivateAccess = "true"))
  CharacterType CharacterKind;

  /// <summary>
  // スポーンするCharacterクラスを格納する配列
  /// <summary>
  UPROPERTY()
  TArray<TSubclassOf<APlayerCharacter>> CharacterClassesArray;

  /// <summary>
  // スポーンするCharacterを格納する配列
  /// <summary>
  UPROPERTY()
  TArray<APlayerCharacter*> CharactersArray;

  /// <summary>
  // レベル上のCharacterクラスを格納する配列
  /// <summary>
  UPROPERTY()
  TArray<TSubclassOf<APlayerCharacter>> FoundClassesArray;

  /// <summary>
  // レベル上のCharacterを格納する配列
  /// <summary>
  UPROPERTY()
  TArray<APlayerCharacter*> FoundCharactersArray;

  /// <summary>
  // レベル上のCharacterを格納する配列
  /// <summary>
  std::vector<std::pair<UClass*, APlayerCharacter*&>> CharacterClasses;

  /// <summary>
  // PreExistSquareクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class ASquare> PreExistSquareClass;

  /// <summary>
  // PreExistSquare
  /// <summary>
  UPROPERTY()
  ASquare* PreExistSquare;

  /// <summary>
  // 経路探索クラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class ARouteSearch> RouteSearchClass;

  /// <summary>
  // 経路探索
  /// <summary>
  UPROPERTY()
  ARouteSearch* RouteSearch;

  /// <summary>
  // ファイルマネージャークラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class ACSVFileManager> CSVFileManagerClass;

  /// <summary>
  // ファイルマネージャー
  /// <summary>
  UPROPERTY()
  ACSVFileManager* CSVFileManager;

  /// <summary>
  // サイコロクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class ADice> DiceClass;

  /// <summary>
  // サイコロ
  /// <summary>
  UPROPERTY()
  ADice* Dice;

  /// <summary>
  // 所持金表示クラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class UCoinNum> CoinNumClass;

  /// <summary>
  // 所持金表示
  /// <summary>
  UPROPERTY()
  UCoinNum* CoinNum;

  /// <summary>
  // コインクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class AGoldCoin> GoldCoinClass;

  /// <summary>
  // コイン
  /// <summary>
  UPROPERTY()
  TArray<AGoldCoin*> GoldCoins;

  /// <summary>
  // 減少時のコインクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class AReduceGoldCoin> ReduceGoldCoinClass;

  /// <summary>
  // 減少時のコイン
  /// <summary>
  UPROPERTY()
  TArray<AReduceGoldCoin*> ReduceGoldCoins;

  /// <summary>
  // 木の橋クラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class AWoodBridge> WoodBridgeClass;

  /// <summary>
  // 木の橋
  /// <summary>
  UPROPERTY()
  AWoodBridge* WoodBridge;

  /// <summary>
  // 矢印クラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class AArrow> ArrowClass;

  /// <summary>
  // 最短経路を指す矢印
  /// <summary>
  UPROPERTY()
  AArrow* Arrow;

  /// <summary>
  // 遠回りの経路を指す矢印
  /// <summary>
  UPROPERTY()
  AArrow* RoundaboutArrow;

  /// </summary>
  // 累積時間
  /// </summary>
  UPROPERTY()
  float AccumulatedTime;

  /// </summary>
  //　出目確定フェーズの累積時間
  /// </summary>
  UPROPERTY()
  float DecideNunAccumulatedTime;

  /// </summary>
  // コインの表示時間で使用する累積時間
  /// </summary>
  UPROPERTY()
  float CoinAccumulatedTimes[CoinNumNameSpace::CoinChangeAmount];

  /// </summary>
  // コイン落下開始までの累積時間
  /// </summary>
  UPROPERTY()
  float CoinStartAccumulatedTime;

  /// </summary>
  // ブレンドの割合
  /// </summary>
  UPROPERTY()
  float BlendAlpha;

  /// </summary>
  // WaitTimerHandle
  /// </summary>
  FTimerHandle WaitTimerHandle;

  /// </summary>
  // 待ち時間
  /// </summary>
  float WaitTime;

  /// </summary>
  // カメラを少しずつ移動させる際に使用するインデックス
  /// </summary>
  int32 CurrentStep;

  /// </summary>
  // 2つ目のカメラ位置を設定するためのActor
  /// </summary>
  UPROPERTY()
  AActor* SecondCameraActor;

protected:

  /// <summary>
  /// BeginPlay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void BeginPlay() override;

  /// <summary>
  /// EndPlay関数の宣言
  /// </summary>
  /// <param>終了する理由</param>
  /// <returns>なし</returns>
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  /// <summary>
  /// PreInitializeComponents関数の宣言(オーバーライド)
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void PreInitializeComponents() override;

public:
  /// <summary>
  /// Tick関数の宣言
  /// </summary>
  /// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
  /// <returns>なし</returns>
  virtual void Tick(float DeltaTime) override;

  /// <summary>
  /// SpawnCharacter関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SpawnCharacter(FVector& SpawnLoc);

  /// <summary>
  /// SpawnSquares関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SpawnSquares();

  /// <summary>
  /// CalculateSpawnPos関数の定義
  /// </summary>
  /// <param = "I">指定したX位置</param>
  /// <param = "J">指定したY位置</param>
  /// <returns>なし</returns>
  FVector CalculateSpawnPos(int32 I, int32 J);

  /// <summary>
  /// IsCanWalk関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  bool IsCanWalk(RoadType Type);

  /// <summary>
  /// DecideTargetAndPassed関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void DecideTargetAndPassed(int32 X, int32 Y, FVector LastPassedLoc);

  /// <summary>
  /// SetCharacterType関数の宣言
  /// </summary>
  /// <param = "CharType">キャラクターの種類</param>
  /// <returns>なし</returns>
  void SetCharacterType(CharacterType CharType);

  /// <summary>
  /// GetCharacterType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターの種類</returns>
  CharacterType GetCharacterType();

  /// <summary>
  /// ChangeCharacterType関数の宣言
  /// </summary>
  /// <param = "CharIndex">キャラクターの要素番号</param>
  /// <returns>なし</returns>
  void ChangeCharacterType(int32 CharIndex);

  /// <summary>
  /// CheckOverlapWithOther関数の宣言
  /// </summary>
  /// <param = "CharIndex">現在のターンのキャラクターの要素番号</param>
  /// <returns>止まったマスに既に止まっている他のキャラクターの人数</returns>
  int32 CheckOverlapWithOther(int32 CharIndex);

  /// <summary>
  /// ChangeCharacterPos関数の宣言
  /// </summary>
  /// <param = "Character">キャラクター</param>
  /// <returns>なし</returns>
  void ChangeCharacterPos(int32 CharIndex);

  /// <summary>
  /// SetArrowRightLeft関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetArrowRightLeft();

  /// <summary>
  /// SetArrowFront関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetArrowFront(FVector Target);

  /// <summary>
  /// SpawnAndSetArrow関数の宣言
  /// </summary>
  /// <param = "RightAngle">矢印を傾ける角度</param>
  /// <returns>なし</returns>
  void SpawnAndSetArrow(float RightAngle);

  /// <summary>
  /// FinishCoinEvent関数の宣言
  /// </summary>
  /// <param = "I">コインの要素番号</param>
  /// <param = "J">キャラクターのインデックス</param>
  /// <param = "IsCoinIncreased">コインが増えたフラグ</param>
  /// <param = "IsCoinDecreased">コインが減ったフラグ</param>
  /// <returns>なし</returns>
  void FinishCoinEvent(int32 I, int32 J, bool IsCoinIncreased, bool IsCoinDecreased);

  /// <summary>
  /// AnimCoin関数の宣言
  /// </summary>
  /// <param = "J">キャラクターのインデックス</param>
  /// <param = "IsCoinIncreased">コインが増えたフラグ</param>
  /// <param = "IsCoinDecreased">コインが減ったフラグ</param>
  /// <param = "CoinSpawnRotation">コインスポーン時の回転</param>
  /// <param = "DeltaTime">前回フレーム更新からの経過時間</param>
  /// <returns>なし</returns>
  void AnimCoin(int32 J, bool IsCoinIncreasedFlag, bool IsCoinDecreasedFlag,FVector CoinSpawnLocation, FVector ReduceCoinSpawnLocation, FRotator CoinSpawnRotation, float DeltaTime);

  /// <summary>
  /// SetForceMove関数の宣言
  /// </summary>
  /// <param = "CharIndex">キャラクターの要素番号</param>
  /// <returns>なし</returns>
  void SetForceMove(int32 CharIndex);

  /// <summary>
  /// GetRandomNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ランダムな整数</returns>
  int32 GetRandomNum(int32 Min, int32 Max);

  /// <summary>
  /// IsFrontOnlyCharacter関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ランダムな整数</returns>
  bool IsFrontOnlyCharacter(CharacterType CharType);
};
