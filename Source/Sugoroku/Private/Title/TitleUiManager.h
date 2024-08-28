#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SugorokuWidget.h"
#include "TitleUiManager.generated.h"

/**
 *
 */

/// <summary>
/// TitleUiManagerクラス
/// </summary>
UCLASS()
class ATitleUiManager : public AHUD
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	ATitleUiManager();

private:

	/// <summary>
	// タイトルウィジェットクラス
	/// <summary>
	UPROPERTY()
	TSubclassOf<USugorokuWidget> TitleWidgetClass;

	/// <summary>
	// タイトルウィジェット
	/// <summary>
	UPROPERTY()
	USugorokuWidget* TitleWidget;

public:

	/// <summary>
	/// PreInitializeComponents関数の宣言(オーバーライド)
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void PreInitializeComponents() override;

	/// <summary>
	/// OpenTitle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OpenTitle();

	/// <summary>
	/// CloseTitle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void CloseTitle();

};
