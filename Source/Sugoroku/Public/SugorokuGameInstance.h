#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SugorokuGameInstance.generated.h"

/**
 *
 */
 /// <summary>
 /// SugorokuGameInstanceクラス
 /// </summary>
UCLASS()
class SUGOROKU_API USugorokuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	USugorokuGameInstance();

private:

	/// <summary>
	// タイトルウィジェットのパス
	/// <summary>
	UPROPERTY()
	FString TitleWidgetPath;

	/// <summary>
	// プレイヤー選択ウィジェットのパス
	/// <summary>
	UPROPERTY()
		FString BattleWidgetPath;

	/// <summary>
	// タイプAのCharacterのパス
	/// <summary>
	UPROPERTY()
	FString TypeACharacterPath;

	/// <summary>
	// タイプBのCharacterのパス
	/// <summary>
	UPROPERTY()
	FString TypeBCharacterPath;

public:

	/// <summary>
	/// GetTitleWidgetPath関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>タイトルウィジェットのパス</returns>
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	FString GetTitleWidgetPath();

	/// <summary>
	/// GetBattleWidgetPath関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>バトルウィジェットのパス</returns>
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		FString GetBattleWidgetPath();

	/// <summary>
	/// GetTypeACharacterPath関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>TypeAキャラクターのパス</returns>
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	FString GetTypeACharacterPath();

	/// <summary>
	/// GetTypeBCharacterPath関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>TypeBキャラクターのパス</returns>
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	FString GetTypeBCharacterPath();

protected:

	/// <summary>
	/// OnStart関数の宣言(オーバーライド)
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	void OnStart() override;
};

