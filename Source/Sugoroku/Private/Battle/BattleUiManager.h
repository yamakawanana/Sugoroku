#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SugorokuWidget.h"
#include "Battle/CoinNum/CoinNum.h"
#include "BattleUiManager.generated.h"

/**
 *
 */

/// <summary>
/// 名前空間BattleUiNameSpace
/// </summary>
namespace BattleUiNameSpace {
  /// <summary>
  /// バトル開始時のウィジェットパスを定数BattleUiWidgetPathに格納する
  /// </summary>
  static const FString BattleUiWidgetPath = "/Game/Widgets/WBP_Battle.WBP_Battle_C";

  /// <summary>
  /// イベントの内容表示のウィジェットパスを定数EventDisplayPathに格納する
  /// </summary>
  static const FString EventDisplayPath = "/Game/Widgets/WBP_EventDisplay.WBP_EventDisplay_C";

  /// <summary>
  /// 所持金表示のウィジェットパスを定数CoinNumWidgetPathに格納する
  /// </summary>
  static const FString CoinNumWidgetPath = "/Game/Widgets/CoinNum/WBP_CoinNum.WBP_CoinNum_C";

  /// <summary>
  /// 分かれ道表示のウィジェットパスを定数BranchMessageWidgetPathに格納する
  /// </summary>
  static const FString BranchMessageWidgetPath = "/Game/Widgets/WBP_BranchMessage.WBP_BranchMessage_C";

}

/// <summary>
/// BattleUiManagerクラス
/// </summary>
UCLASS()
class ABattleUiManager : public AHUD
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	ABattleUiManager();

private:

	/// <summary>
	// Battleウィジェットクラス
	/// <summary>
	UPROPERTY()
	TSubclassOf<USugorokuWidget> BattleWidgetClass;

	/// <summary>
	// Battleウィジェット
	/// <summary>
	UPROPERTY()
	USugorokuWidget* BattleWidget;

  /// <summary>
  // EventDisplayウィジェットクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<USugorokuWidget> EventDisplayWidgetClass;

  /// <summary>
  // EventDisplayウィジェット
  /// <summary>
  UPROPERTY()
  USugorokuWidget* EventDisplayWidget;

  /// <summary>
  // 所持金表示クラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class UCoinNum> CoinNumWidgetClass;

  /// <summary>
  // 所持金表示
  /// <summary>
  UPROPERTY()
  UCoinNum* CoinNumWidget;

  /// <summary>
  // 分かれ道表示ウィジェットクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<USugorokuWidget> BranchMessageWidgetClass;

  /// <summary>
  // 分かれ道表示ウィジェット
  /// <summary>
  UPROPERTY()
  USugorokuWidget* BranchMessageWidget;

public:

	/// <summary>
	/// PreInitializeComponents関数の宣言(オーバーライド)
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void PreInitializeComponents() override;

	/// <summary>
	/// OpenBattle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void OpenBattle();

	/// <summary>
	/// CloseBattle関数の宣言
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void CloseBattle();

  /// <summary>
  /// OpenEventDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void OpenEventDisplay(int32 Num);

  /// <summary>
  /// CloseEventDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseEventDisplay(int32 Num);

  /// <summary>
  /// OpenCoinNumDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void OpenCoinNumDisplay();

  /// <summary>
  /// CloseCoinNumDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseCoinNumDisplay();

  /// <summary>
  /// OpenBranchMessageDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void OpenBranchMessageDisplay();

  /// <summary>
  /// CloseBranchMessageDisplay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseBranchMessageDisplay();

	/// <summary>
	/// CreateUi関数の宣言
	/// </summary>
	/// <param="BattleWidgetPath">BattleWidgetPath</param>
	/// <returns>なし</returns>
	UFUNCTION()
	void CreateUi(FString BattleWidgetPath);
};
