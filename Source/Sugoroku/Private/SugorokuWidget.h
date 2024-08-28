#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SugorokuWidget.generated.h"

/**
 * 
 */
/// <summary>
/// USugorokuWidgetクラス
/// </summary>
UCLASS()
class USugorokuWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /// <summary>
    /// サイコロの出目
    /// </summary>
    UPROPERTY(BlueprintReadWrite, Category = "DiceNum")
    int32 DiceNum;

    /// <summary>
    /// マスのイベントの種類のインデックス
    /// </summary>
    UPROPERTY(BlueprintReadWrite, Category = "EventIndex")
    int32 EventIndex;

    /// <summary>
    /// Open関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
    void Open();

    /// <summary>
    /// Close関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
    void Close();

    /// <summary>
    /// Closed関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
    void Closed();

    /// <summary>
    /// SetDiceNum関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    UFUNCTION()
    void SetDiceNum(int32 Num);

    /// <summary>
    /// SetEventIndex関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    UFUNCTION()
    void SetEventIndex(int32 Index);

private:

    /// <summary>
    /// Open_Implementation関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    void Open_Implementation();

    /// <summary>
    /// Close_Implementation関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    void Close_Implementation();

    /// <summary>
    /// Closed_Implementation関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    void Closed_Implementation();
};
