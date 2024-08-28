#include "Battle/AnimManager/AnimManager.h"

/// <summary>
/// SetVictory関数の定義
/// </summary>
/// <param = "Victory">キャラクターが勝利の状態かのフラグ</param>
/// <returns>なし</returns>
UFUNCTION(BlueprintCallable, Category = "Animations")
void UAnimManager::SetVictory(bool Victory) {
  IsVictory = Victory;
}

/// <summary>
/// SetDefeat関数の定義
/// </summary>
/// <param = "Defeat">キャラクターが敗北の状態かのフラグ</param>
/// <returns>なし</returns>
UFUNCTION(BlueprintCallable, Category = "Animations")
void UAnimManager::SetDefeat(bool Defeat) {
  IsDefeat = Defeat;
}

