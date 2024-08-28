#include "Battle/Dice/Dice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ADice::ADice()
{

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ADice::BeginPlay()
{
  Super::BeginPlay();

  //サイコロのクラスをロードする
  DiceNumWidgetClass = TSoftClassPtr<USugorokuWidget>(FSoftObjectPath(*DiceNameSpace::DiceNumWidgetWidgetPath)).LoadSynchronous();
  //サイコロの目のウィジェットを作成する
  DiceNumWidget = CreateWidget<USugorokuWidget>(GetWorld(), DiceNumWidgetClass);
}

/// <summary>
/// OpenDice関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ADice::OpenDice(int32 Num) {
  UE_LOG(LogTemp, Warning, TEXT("OpenDice"));
  //ウィジェットを開く

  //ウィジェットが存在しない場合は生成する
  if (DiceNumWidget == nullptr) {
    DiceNumWidget = CreateWidget<USugorokuWidget>(GetWorld(), DiceNumWidgetClass);
  }
  //ウィジェットをビューポートに追加する
  DiceNumWidget->Open();
  DiceNumWidget->SetDiceNum(Num - 1);
  //ウィジェットを見える状態にする
  DiceNumWidget->SetVisibility(ESlateVisibility::Visible);

}

/// <summary>
/// CloseDice関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ADice::CloseDice(int32 Num) {
  //ウィジェットを終了する

  //ウィジェットが存在していたら、非表示にする
  DiceNumWidget->SetVisibility(ESlateVisibility::Collapsed);

}

