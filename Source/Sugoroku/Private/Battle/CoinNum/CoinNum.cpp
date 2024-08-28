#include "Battle/CoinNum/CoinNum.h"

/// <summary>
/// OpenCoinNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void UCoinNum::OpenCoinNum() {
  UE_LOG(LogTemp, Warning, TEXT("OpenCoin"));
  //ウィジェットを開く

  //ウィジェットをビューポートに追加する
  CoinNumWidget->Open();
  //ウィジェットを見える状態にする
  CoinNumWidget->SetVisibility(ESlateVisibility::Visible);

}

/// <summary>
/// CloseCoinNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void UCoinNum::CloseCoinNum() {
  //ウィジェットを終了する

  //ウィジェットが存在していたら、非表示にする
  CoinNumWidget->SetVisibility(ESlateVisibility::Collapsed);

}

/// <summary>
/// GetMoneyNum関数の定義
/// </summary>
/// <param = "Index">要素番号</param>
/// <returns>なし</returns>
int32 UCoinNum::GetMoneyNum(int32 CharacterIndex)
{
  //CharacterIndexで指定したキャラクターの所持金を取得する(WBPのバインディングで呼び出す)
  if (MoneyNums.IsValidIndex(CharacterIndex))
  {
    return MoneyNums[CharacterIndex];
  }
  return 0;
}

/// <summary>
/// AddCoins関数の定義
/// </summary>
/// <param = "CharacterIndex">キャラクターの要素番号</param>
/// <param = "Amount">所持金変化量</param>
/// <returns>なし</returns>
void UCoinNum::AddCoins(int32 CharacterIndex, int32 Amount)
{
  if (CoinNumWidget->MoneyNums.IsValidIndex(CharacterIndex))
  {
    //CharacterIndexで指定したキャラクターの所持金を増やす
    CoinNumWidget->MoneyNums[CharacterIndex] += Amount;
  }
}

/// <summary>
/// RemoveCoins関数の定義
/// </summary>
/// <param = "CharacterIndex">キャラクターの要素番号</param>
/// <param = "Amount">所持金変化量</param>
/// <returns>なし</returns>
void UCoinNum::RemoveCoins(int32 CharacterIndex, int32 Amount)
{
  if (CoinNumWidget->MoneyNums.IsValidIndex(CharacterIndex))
  {
    //CharacterIndexで指定したキャラクターの所持金を減らす
    CoinNumWidget->MoneyNums[CharacterIndex] -= Amount;
  }
}

/// <summary>
/// SetCoins関数の定義
/// </summary>
/// <param = "CharacterIndex">キャラクターの要素番号</param>
/// <param = "Amount">所持金変化量</param>
/// <returns>なし</returns>
void UCoinNum::SetCoins(int32 CharacterIndex, int32 Amount)
{
  if (CoinNumWidget->MoneyNums.IsValidIndex(CharacterIndex))
  {
    //CharacterIndexで指定したキャラクターの所持金を設定
    CoinNumWidget->MoneyNums[CharacterIndex] = Amount;
  }
}

/// <summary>
/// GetCoins関数の定義
/// </summary>
/// <param = "Index">要素番号</param>
/// <returns>なし</returns>
int32 UCoinNum::GetCoins(int32 CharacterIndex)
{
  //CharacterIndexで指定したキャラクターの所持金を取得する
  if (CoinNumWidget->MoneyNums.IsValidIndex(CharacterIndex))
  {
    return CoinNumWidget->MoneyNums[CharacterIndex];
  }
  return 0;
}

/// <summary>
/// InitCoinNum関数の定義
/// </summary>
/// <param = "CharacterNum">キャラクターの人数</param>
/// <returns>なし</returns>
void UCoinNum::InitCoinNum(int32 CharacterNum) {
  //所持金の数をキャラクター人数分、0で初期化する
  CoinNumWidget->MoneyNums.Init(0, CharacterNum);
}

/// <summary>
/// InitCoinNumWidget関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void UCoinNum::InitCoinNumWidget() {
  //所持金表示のクラスをロードする
  CoinNumWidgetClass = TSoftClassPtr<UCoinNum>(FSoftObjectPath(*CoinNumNameSpace::CoinNumWidgetPath)).LoadSynchronous();
  //ウィジェットを生成する
  CoinNumWidget = CreateWidget<UCoinNum>(GetWorld(), CoinNumWidgetClass);
}