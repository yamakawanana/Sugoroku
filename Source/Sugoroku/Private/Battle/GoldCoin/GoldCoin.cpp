#include "Battle/GoldCoin/GoldCoin.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
AGoldCoin::AGoldCoin()
{
  // Tickの実行を有効にする
	PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AGoldCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void AGoldCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

