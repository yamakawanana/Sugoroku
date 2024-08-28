#include "Battle/ABattleLevelModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Battle/BattleUiManager.h"
#include "MenuController.h"
#include "Battle/BattleController.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ABattleLevelModeBase::ABattleLevelModeBase() {
	HUDClass = ABattleUiManager::StaticClass();
	PlayerControllerClass = ABattleController::StaticClass();
	DefaultPawnClass = nullptr;
}

