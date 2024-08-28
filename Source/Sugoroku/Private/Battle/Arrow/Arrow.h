#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

/// <summary>
/// 名前空間ArrowNameSpace
/// </summary>
namespace ArrowNameSpace {
  /// <summary>
  /// 切り替える時間を定数ChangeTimeに格納する
  /// </summary>
  static const float FirstChangeTime = 0.5f;

  /// <summary>
  /// 切り替える時間を定数ChangeTimeに格納する
  /// </summary>
  static const float SecondChangeTime = 1.0f;

  /// <summary>
  /// 表示時間を定数TimeToDisplayに格納する
  /// </summary>
  static const float TimeToDisplay = 5.0f;

  /// <summary>
  /// 位置の移動変化量を定数MoveChangeAmountに格納する
  /// </summary>
  static const float MoveChangeAmount = 10.0f;

}

/// <summary>
/// ArrowDirection列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class ArrowDirection : uint8 {
  /// </summary>
  //　前
  /// </summary>
  Front,

  /// </summary>
  //　右
  /// </summary>
  Right,

  /// </summary>
  //　左
  /// </summary>
  Left,
};

/// <summary>
/// Arrowクラス
/// </summary>
UCLASS()
class AArrow : public AActor
{
  GENERATED_BODY()
	
public:	
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  AArrow();

  /// </summary>
  //　矢印の向き
  /// </summary>
  UPROPERTY()
  ArrowDirection Direction;

  /// </summary>
  //　前回フレームの矢印の向き
  /// </summary>
  UPROPERTY()
  ArrowDirection PreDirection;

  /// </summary>
  // 累積時間
  /// </summary>
  UPROPERTY()
  float AccumulatedTime;

  /// </summary>
  // 矢印の位置
  /// </summary>
  UPROPERTY()
  FVector ArrowLocation;

protected:
  /// <summary>
  /// BeginPlay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void BeginPlay() override;

public:	
  /// <summary>
  /// Tick関数の宣言
  /// </summary>
  /// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
  /// <returns>なし</returns>
  virtual void Tick(float DeltaTime) override;

  /// <summary>
  /// SetArrowDirection関数の宣言
  /// </summary>
  /// <param = "ArDirection">矢印の方向</param>
  /// <returns>なし</returns>
  void SetArrowDirection(ArrowDirection ArDirection);

  /// <summary>
  /// GetArrowDirection関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターの方向</returns>
  ArrowDirection GetArrowDirection();

  /// <summary>
  /// ResetAccumulatedTime関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void ResetAccumulatedTime();

};
