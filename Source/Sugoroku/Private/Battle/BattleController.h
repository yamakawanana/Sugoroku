#pragma once

#include "CoreMinimal.h"
#include "MenuController.h"
#include "UObject/ScriptInterface.h"
#include "BattleController.generated.h"

 /// <summary>
 /// BattleControllerクラス
 /// </summary>
UCLASS()
class ABattleController : public AMenuController
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	ABattleController();

private:

	/// <summary>
	// 左右どちらかのキーが押されたフラグ
	/// <summary>
	UPROPERTY()
	bool IsPushed;

	/// <summary>
	// 前回フレームで左右どちらかのキーが押されたフラグ
	/// <summary>
	UPROPERTY()
	bool IsPushedPreFrame;

protected:

	/// <summary>
	/// SetupInputComponent関数の宣言(オーバーライド)
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	void SetupInputComponent() override;

public:

	/// <summary>
	/// OpenBattle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OpenBattle();

	/// <summary>
	/// DisplayEvent関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void DisplayEvent(int32 Num);

  /// <summary>
  /// CloseEvent関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseEvent(int32 Num);

  /// <summary>
  /// DisplayBranchMessage関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void DisplayBranchMessage();

  /// <summary>
  /// CloseBranchMessage関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseBranchMessage();

  /// <summary>
  /// DisplayCoinNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void DisplayCoinNum();

	/// <summary>
	/// Tick関数の宣言
	/// </summary>
	/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
	/// <returns>なし</returns>
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// IsPush関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>左右どちらかのキーが押されたフラグ</returns>
	UFUNCTION()
	bool IsPush();

private:

	/// <summary>
	/// OnLeft関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OnLeft();

	/// <summary>
	/// OnRight関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OnRight();

};
