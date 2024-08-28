#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimManager.generated.h"

/**
 * 
 */

/// <summary>
/// AnimManagerクラス
/// </summary>
UCLASS()
class UAnimManager : public UAnimInstance
{
	GENERATED_BODY()

public:

  /// </summary>
  // キャラクターが勝利の状態か
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
  bool IsVictory;

  /// </summary>
  // キャラクターが敗北の状態か
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
  bool IsDefeat;

  /// <summary>
  /// SetVictory関数の宣言
  /// </summary>
  /// <param = "Victory">キャラクターが勝利の状態かのフラグ</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "Animations")
  void SetVictory(bool Victory);

  /// <summary>
  /// SetDefeat関数の宣言
  /// </summary>
  /// <param = "Defeat">キャラクターが敗北の状態かのフラグ</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "Animations")
  void SetDefeat(bool Defeat);
	
};
