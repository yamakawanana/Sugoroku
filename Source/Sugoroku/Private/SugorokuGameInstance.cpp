#include "SugorokuGameInstance.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
USugorokuGameInstance::USugorokuGameInstance()
	:TitleWidgetPath("")
	, BattleWidgetPath("")
	, TypeACharacterPath("")
	, TypeBCharacterPath("")
{

}

/// <summary>
/// GetTitleWidgetPath関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>タイトルウィジェットのパス</returns>
FString USugorokuGameInstance::GetTitleWidgetPath() {
	return TitleWidgetPath;
}

/// <summary>
/// GetBattleWidgetPath関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>バトルウィジェットのパス</returns>
FString USugorokuGameInstance::GetBattleWidgetPath() {
	return BattleWidgetPath;
}

/// <summary>
/// GetTypeACharacterPath関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>TypeAキャラクターのパス</returns>
FString USugorokuGameInstance::GetTypeACharacterPath() {
	return TypeACharacterPath;
}

/// <summary>
/// GetTypeBCharacterPath関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>TypeBキャラクターのパス</returns>
FString USugorokuGameInstance::GetTypeBCharacterPath() {
	return TypeBCharacterPath;
}

/// <summary>
/// OnStart関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void USugorokuGameInstance::OnStart() {
	FString TitlePath = FString(TEXT(""));
	GConfig->GetString(TEXT("UMGSettings"), TEXT("TitleWidgetPath"), TitlePath, GGameIni);

	FString BattlePath = FString(TEXT(""));
	GConfig->GetString(TEXT("UMGSettings"), TEXT("BattleWidgetPath"), BattlePath, GGameIni);

	FString CharacterAPath = FString(TEXT(""));
	GConfig->GetString(TEXT("UMGSettings"), TEXT("TypeACharacterPath"), CharacterAPath, GGameIni);

	FString CharacterBPath = FString(TEXT(""));
	GConfig->GetString(TEXT("UMGSettings"), TEXT("TypeBCharacterPath"), CharacterBPath, GGameIni);
}


