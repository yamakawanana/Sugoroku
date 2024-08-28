#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SugorokuWidget.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetSwitcher.h"
#include "Dice.generated.h"

/// <summary>
/// 名前空間DiceNameSpace
/// </summary>
namespace DiceNameSpace {

  /// <summary>
  /// サイコロの目のウィジェットパスを定数DiceNumWidgetWidgetPathに格納する
  /// </summary>
  static const FString DiceNumWidgetWidgetPath = "/Game/Widgets/Dice/WBP_DiceNum1.WBP_DiceNum1_C";

  /// <summary>
  //サイコロの目1を表す整数
  /// <summary>
  static const int32 One = 1;

  /// <summary>
  //サイコロの目2を表す整数
  /// <summary>
  static const int32 Two = 2;

  /// <summary>
  //サイコロの目3を表す整数
  /// <summary>
  static const int32 Three = 3;

  /// <summary>
  //サイコロの目4を表す整数
  /// <summary>
  static const int32 Four = 4;

  /// <summary>
  //サイコロの目5を表す整数
  /// <summary>
  static const int32 Five = 5;

  /// <summary>
  //サイコロの目6を表す整数
  /// <summary>
  static const int32 Six = 6;

  /// <summary>
  /// 累積時間のリセット時間を定数ResetTimeに格納する
  /// </summary>
  static const float ResetTime = 0.6f;

  /// <summary>
  /// 累積時間のリセット時間を定数ChangeTimeに格納する
  /// </summary>
  static const float ChangeTime[] = { 0.0f,0.1f,0.2f,0.3f,0.4f,0.5f,0.6f };

  /// <summary>
  /// 累積時間のリセット時間を定数ResetTimeに格納する
  /// </summary>
  static const float DecideNumResetTime = 1.0f;
}

/// <summary>
/// Diceクラス
/// </summary>
UCLASS()
class ADice : public AHUD
{
  GENERATED_BODY()
  
public:  
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ADice();

private:

  /// <summary>
  // DiceNumWidgetクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<USugorokuWidget> DiceNumWidgetClass;

  /// <summary>
  // DiceNumWidget
  /// <summary>
  UPROPERTY()
  USugorokuWidget* DiceNumWidget;

protected:
  /// <summary>
  /// BeginPlay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void BeginPlay() override;

public:

  /// <summary>
  /// OpenDice関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void OpenDice(int32 Num);

  /// <summary>
  /// CloseDice関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  UFUNCTION()
  void CloseDice(int32 Num);

};
