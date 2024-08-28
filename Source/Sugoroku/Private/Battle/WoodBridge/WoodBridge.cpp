#include "Battle/WoodBridge/WoodBridge.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
AWoodBridge::AWoodBridge()
{
 	// // Tickの実行を有効にする
	PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AWoodBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void AWoodBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

