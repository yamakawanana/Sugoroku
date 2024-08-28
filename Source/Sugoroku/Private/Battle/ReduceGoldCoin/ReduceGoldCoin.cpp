#include "Battle/ReduceGoldCoin/ReduceGoldCoin.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
AReduceGoldCoin::AReduceGoldCoin()
{
  // Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AReduceGoldCoin::BeginPlay()
{
  Super::BeginPlay();

}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void AReduceGoldCoin::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}



