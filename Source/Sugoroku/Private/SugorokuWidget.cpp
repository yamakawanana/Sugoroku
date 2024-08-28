#include "SugorokuWidget.h"

/// <summary>
/// Open_Implementation関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void USugorokuWidget::Open_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ウィジェットOpen_Implementation"));
    //ウィジェットをビューポートに設定する
    if (!IsInViewport()) {
      AddToViewport(0);
    }
}

/// <summary>
/// Close_Implementation関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void USugorokuWidget::Close_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ウィジェットClose_Implementation"));
}

/// <summary>
/// Closed_Implementation関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void USugorokuWidget::Closed_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ウィジェットClosed_Implementation"));
    //ウィジェットをビューポートから外す
    RemoveFromParent();
}

/// <summary>
/// SetDiceNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
UFUNCTION()
void USugorokuWidget::SetDiceNum(int32 Num) {
  DiceNum = Num;
}

/// <summary>
/// SetEventIndex関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
UFUNCTION()
void USugorokuWidget::SetEventIndex(int32 Index) {
  EventIndex = Index;
}

