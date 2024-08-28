#include "Battle/BattleUiManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/SugorokuGameInstance.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ABattleUiManager::ABattleUiManager()
    : BattleWidgetClass(nullptr)
    , BattleWidget(nullptr)
{

}

/// <summary>
/// PreInitializeComponents関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::PreInitializeComponents() {
    USugorokuGameInstance* GameInstance = Cast<USugorokuGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    CreateUi(BattleUiNameSpace::BattleUiWidgetPath);
    CreateUi(BattleUiNameSpace::EventDisplayPath);
    CreateUi(BattleUiNameSpace::CoinNumWidgetPath);
    CreateUi(BattleUiNameSpace::BranchMessageWidgetPath);
}

/// <summary>
/// OpenBattle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::OpenBattle() {
    UE_LOG(LogTemp, Warning, TEXT("ABattleUiManagerのOpenBattle"));
    //Battleウィジェットを開く
    BattleWidget->Open();
}

/// <summary>
/// CloseBattle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::CloseBattle() {
    //Battleウィジェットを終了する
    BattleWidget->Close();
}

/// <summary>
/// OpenEventDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::OpenEventDisplay(int32 Num) {
  UE_LOG(LogTemp, Warning, TEXT("ABattleUiManagerのOpenMessage"));
  //Battleウィジェットを開く
  EventDisplayWidget->Open();
  EventDisplayWidget->SetEventIndex(Num);
  EventDisplayWidget->SetVisibility(ESlateVisibility::Visible);
}

/// <summary>
/// CloseEventDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::CloseEventDisplay(int32 Num) {
  //ウィジェットを非表示にする
  EventDisplayWidget->SetVisibility(ESlateVisibility::Collapsed);
}

/// OpenCoinNumDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::OpenCoinNumDisplay() {
  UE_LOG(LogTemp, Warning, TEXT("ABattleUiManagerのOpenMessage"));
  //CoinNumWidgetを開く
  CoinNumWidget->Open();
}

/// <summary>
/// CloseCoinNumDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::CloseCoinNumDisplay() {
  //Battleウィジェットを終了する
  CoinNumWidget->Close();
}

/// OpenBranchMessageDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::OpenBranchMessageDisplay() {
  UE_LOG(LogTemp, Warning, TEXT("ABattleUiManagerのOpenMessage"));
  //CoinNumWidgetを開く
  BranchMessageWidget->Open();
  //ウィジェットを見える状態にする
  BranchMessageWidget->SetVisibility(ESlateVisibility::Visible);
}

/// <summary>
/// CloseBranchMessageDisplay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleUiManager::CloseBranchMessageDisplay() {
  if (IsValid(BranchMessageWidget)) {
    //Battleウィジェットを非表示にする
    BranchMessageWidget->SetVisibility(ESlateVisibility::Collapsed);
  }
}

/// <summary>
/// CreateUi関数の定義
/// </summary>
/// <param="BattleWidgetPath">BattleWidgetPath</param>
/// <returns>なし</returns>
void ABattleUiManager::CreateUi(FString BattleWidgetPath) {

    if (BattleWidgetPath == BattleUiNameSpace::BattleUiWidgetPath) {
      //取得したBattleWidgetPathのアセットをロードする
      BattleWidgetClass = TSoftClassPtr<USugorokuWidget>(FSoftObjectPath(*BattleWidgetPath)).LoadSynchronous();
      if (BattleWidgetClass)
      {
        //Battleウィジェットを作成する
        BattleWidget = CreateWidget<USugorokuWidget>(GetWorld(), BattleWidgetClass);
      }
    }
    else if (BattleWidgetPath == BattleUiNameSpace::EventDisplayPath) {
      //取得したBattleWidgetPathのアセットをロードする
      EventDisplayWidgetClass = TSoftClassPtr<USugorokuWidget>(FSoftObjectPath(*BattleWidgetPath)).LoadSynchronous();
      if (EventDisplayWidgetClass)
      {
        //MessageWidgetを作成する
        EventDisplayWidget = CreateWidget<USugorokuWidget>(GetWorld(), EventDisplayWidgetClass);
      }
    }
    else if (BattleWidgetPath == BattleUiNameSpace::CoinNumWidgetPath) {
      //取得したBattleWidgetPathのアセットをロードする
      CoinNumWidgetClass = TSoftClassPtr<UCoinNum>(FSoftObjectPath(*BattleWidgetPath)).LoadSynchronous();
      if (CoinNumWidgetClass)
      {
        //MessageWidgetを作成する
        CoinNumWidget = CreateWidget<UCoinNum>(GetWorld(), CoinNumWidgetClass);
      }
    }
    else if (BattleWidgetPath == BattleUiNameSpace::BranchMessageWidgetPath) {
      //取得したBattleWidgetPathのアセットをロードする
      BranchMessageWidgetClass = TSoftClassPtr<USugorokuWidget>(FSoftObjectPath(*BattleWidgetPath)).LoadSynchronous();
      if (BranchMessageWidgetClass)
      {
        //MessageWidgetを作成する
        BranchMessageWidget = CreateWidget<USugorokuWidget>(GetWorld(), BranchMessageWidgetClass);
      }
    }
}