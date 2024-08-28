#include "Title/TitleLevel.h"
#include "Title/TitleUiManager.h"
#include "MenuController.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ATitleLevel::ATitleLevel()
{
	// Tickの実行を有効にする
	PrimaryActorTick.bCanEverTick = true;
}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ATitleLevel::BeginPlay() {
	Super::BeginPlay();

	//画面にデバッグメッセージを表示する
	//GEngine->AddOnScreenDebugMessage(-1, TitleNameSpace::TimeToDisplay, FColor::Yellow, "TitleLevel");
	//UE_LOG(LogTemp, Warning, TEXT("TitleLevel"));

	AMenuController* MenuController = Cast<AMenuController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(MenuController))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "OpenTitleを開く");
		MenuController->OpenTitle();
	}

}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ATitleLevel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

