#include "Battle/Arrow/Arrow.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
AArrow::AArrow()
  : Direction(ArrowDirection::Front)
  , PreDirection(ArrowDirection::Front)
  , AccumulatedTime(0.0f)
{
  // Tickの実行を有効にする
	PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  if (AccumulatedTime == 0.0f) {
    //矢印の現在位置を取得する
    ArrowLocation = GetActorLocation();
  }
  FVector FrontNewLocation = FVector((ArrowLocation.X + ArrowNameSpace::MoveChangeAmount), ArrowLocation.Y, ArrowLocation.Z);
  FVector NewLocationX = FVector(FVector((ArrowLocation.X), (ArrowLocation.Y + ArrowNameSpace::MoveChangeAmount), (ArrowLocation.Z)));
  
  AccumulatedTime = AccumulatedTime + DeltaTime;

  if (Direction == ArrowDirection::Front) {
    if (AccumulatedTime >= 0.0f && AccumulatedTime < ArrowNameSpace::FirstChangeTime) {
      SetActorLocation(FrontNewLocation);
    }
    if (AccumulatedTime >= ArrowNameSpace::FirstChangeTime && AccumulatedTime < ArrowNameSpace::SecondChangeTime) {
      SetActorLocation(FVector(ArrowLocation));
    }
    if (AccumulatedTime >= ArrowNameSpace::SecondChangeTime) {
      AccumulatedTime = 0.0f;
    }
  }
  else if (Direction == ArrowDirection::Right || Direction == ArrowDirection::Left) {
    if (AccumulatedTime >= 0.0f && AccumulatedTime < ArrowNameSpace::FirstChangeTime) {
      SetActorLocation(NewLocationX);
    }
    if (AccumulatedTime >= ArrowNameSpace::FirstChangeTime && AccumulatedTime < ArrowNameSpace::SecondChangeTime) {
      SetActorLocation(ArrowLocation);
    }
    if (AccumulatedTime > ArrowNameSpace::SecondChangeTime) {
      AccumulatedTime = 0.0f;
    }
  }

  //前回フレームの矢印の方向を今回の矢印の方向で更新する
  PreDirection = Direction;

}

/// <summary>
/// SetArrowDirection関数の宣言
/// </summary>
/// <param = "ArDirection">矢印の方向</param>
/// <returns>なし</returns>
void AArrow::SetArrowDirection(ArrowDirection ArDirection) {
  Direction = ArDirection;
}

/// <summary>
/// GetArrowDirection関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>前回のキャラクターの方向</returns>
ArrowDirection AArrow::GetArrowDirection() {
  return Direction;
}

/// <summary>
/// ResetAccumulatedTime関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AArrow::ResetAccumulatedTime() {
  AccumulatedTime = 0.0f;
}

