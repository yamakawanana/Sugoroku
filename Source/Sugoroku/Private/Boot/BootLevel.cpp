#include "BootLevel.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ABootLevel::ABootLevel()
	: AccumulatedTime(0.0f)
	, Phase(PhaseType::Idol)
{
	// Tickの実行を有効にする
	PrimaryActorTick.bCanEverTick = true;
}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABootLevel::BeginPlay() {
	Super::BeginPlay();

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.SetRes 1280x720w");
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ABootLevel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (Phase == PhaseType::Idol) {
		AccumulatedTime = AccumulatedTime + DeltaTime;
		if (AccumulatedTime >= BootNameSpace::ChangeLevelTime) {
			Phase = PhaseType::LevelChange;
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("TitleLevel"), true);
		}
	}

}

