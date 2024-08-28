#pragma once

#include "CoreMinimal.h"
#include "SugorokuWidget.h"
#include "Battle/Dice/Dice.h"
#include "CoinNum.generated.h"

/**
 * 
 */

 /// <summary>
 /// 名前空間CoinNumNameSpace
 /// </summary>
namespace CoinNumNameSpace {
  /// <summary>
  /// 所持金表示のウィジェットパスを定数CoinNumWidgetPathに格納する
  /// </summary>
  static const FString CoinNumWidgetPath = "/Game/Widgets/CoinNum/WBP_CoinNum.WBP_CoinNum_C";

  /// <summary>
  /// 所持金増減時の変化量を定数CoinChangeAmountに格納する
  /// </summary>
  static const int32 CoinChangeAmount = 3;

}

/// <summary>
/// CoinNumクラス
/// </summary>
UCLASS()
class UCoinNum : public USugorokuWidget
{
	GENERATED_BODY()

public:

  /// <summary>
  // コイン所持数を格納する配列
  /// <summary>
  UPROPERTY(BlueprintReadWrite, Category = "CoinNums")
  TArray<int32> MoneyNums;

private:

  /// <summary>
  // CoinNumWidgetクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<UCoinNum> CoinNumWidgetClass;

  /// <summary>
  // CoinNumWidget
  /// <summary>
  UPROPERTY()
  UCoinNum* CoinNumWidget;

public:

  /// <summary>
  /// OpenCoinNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void OpenCoinNum();

  /// <summary>
  /// CloseCoinNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseCoinNum();

  /// <summary>
  /// GetMoneyNum関数の宣言
  /// </summary>
  /// <param = "Index">要素番号</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "CoinNums")
  int32 GetMoneyNum(int32 CharacterIndex);

  /// <summary>
  /// AddCoins関数の宣言
  /// </summary>
  /// <param = "CharacterIndex">キャラクターの要素番号</param>
  /// <param = "Amount">所持金変化量</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "CoinNums")
  void AddCoins(int32 CharacterIndex, int32 Amount);

  /// <summary>
  /// RemoveCoins関数の宣言
  /// </summary>
  /// <param = "CharacterIndex">キャラクターの要素番号</param>
  /// <param = "Amount">所持金変化量</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "CoinNums")
  void RemoveCoins(int32 CharacterIndex, int32 Amount);

  /// <summary>
  /// SetCoins関数の宣言
  /// </summary>
  /// <param = "CharacterIndex">キャラクターの要素番号</param>
  /// <param = "Amount">所持金変化量</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "CoinNums")
  void SetCoins(int32 CharacterIndex, int32 Amount);

  /// <summary>
  /// GetCoins関数の宣言
  /// </summary>
  /// <param = "Index">要素番号</param>
  /// <returns>なし</returns>
  UFUNCTION(BlueprintCallable, Category = "CoinNums")
  int32 GetCoins(int32 CharacterIndex);

  /// <summary>
  /// InitCoinNum関数の宣言
  /// </summary>
  /// <param = "CharacterNum">キャラクターの人数</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void InitCoinNum(int32 CharacterNum);

  /// <summary>
  /// InitCoinNumWidget関数の定義
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void InitCoinNumWidget();
	
};
