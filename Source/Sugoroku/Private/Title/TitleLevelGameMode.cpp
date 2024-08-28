#include "Title/TitleLevelGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Title/TitleUiManager.h"
#include "MenuController.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ATitleLevelGameMode::ATitleLevelGameMode() {
	HUDClass = ATitleUiManager::StaticClass();
	PlayerControllerClass = AMenuController::StaticClass();
	DefaultPawnClass = nullptr;
}

