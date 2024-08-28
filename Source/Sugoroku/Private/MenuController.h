#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 *
 */

/// <summary>
/// 名前空間MenuControllerNameSpace
/// </summary>
namespace MenuControllerNameSpace {

}

 /// <summary>
 /// AMenuControllerクラス
 /// </summary>
UCLASS()
class AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	AMenuController();

protected:

	/// <summary>
	/// SetupInputComponent関数の宣言(オーバーライド)
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	void SetupInputComponent() override;

public:

	/// <summary>
	/// OpenTitle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OpenTitle();

	/// <summary>
	/// Tick関数の宣言
	/// </summary>
	/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
	/// <returns>なし</returns>
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// OnDecide関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OnDecide();

	/// <summary>
	/// OnQuit関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OnQuit();

};
