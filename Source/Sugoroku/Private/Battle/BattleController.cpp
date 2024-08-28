#include "Battle/BattleController.h"
#include "Battle/BattleUiManager.h"
#include "Kismet/KismetSystemLibrary.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ABattleController::ABattleController()
    : IsPushed(false)
    , IsPushedPreFrame(false)
{

}

/// <summary>
/// SetupInputComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::SetupInputComponent() {
    Super::SetupInputComponent();
    check(InputComponent);

    if (IsValid(InputComponent))
    {
        //アクションマッピングとBattleControllerをつなぐ
        InputComponent->BindAction("Left", IE_Pressed, this, &ABattleController::OnLeft);
        InputComponent->BindAction("Right", IE_Pressed, this, &ABattleController::OnRight);
    }
}

/// <summary>
/// OpenBattle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::OpenBattle() {
    UE_LOG(LogTemp, Warning, TEXT("BattleControllerのOpenBattle"));
    if (IsValid(MyHUD))
    {
        ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
        if (IsValid(UIManager))
        {
            //Battleの画面を開く
            UIManager->OpenBattle();
        }
    }
}


/// <summary>
/// DisplayEvent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::DisplayEvent(int32 Num) {
    UE_LOG(LogTemp, Warning, TEXT("BattleControllerのDisplayMessage"));
    if (IsValid(MyHUD))
    {
        ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
        if (IsValid(UIManager))
        {
            //Battleの画面を開く
          UIManager->OpenEventDisplay(Num);
        }
    }
}

/// <summary>
/// CloseEvent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::CloseEvent(int32 Num) {
  UE_LOG(LogTemp, Warning, TEXT("BattleControllerのDisplayMessage"));
  if (IsValid(MyHUD))
  {
    ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
    if (IsValid(UIManager))
    {
      //Battleの画面を閉じる
      UIManager->CloseEventDisplay(Num);
    }
  }
}

/// <summary>
/// DisplayBranchMessage関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::DisplayBranchMessage() {
  UE_LOG(LogTemp, Warning, TEXT("BattleControllerのDisplayMessage"));
  if (IsValid(MyHUD))
  {
    ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
    if (IsValid(UIManager))
    {
      //Battleの画面を開く
      UIManager->OpenBranchMessageDisplay();
    }
  }
}

/// <summary>
/// CloseBranchMessage関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::CloseBranchMessage() {
  UE_LOG(LogTemp, Warning, TEXT("BattleControllerのDisplayMessage"));
  if (IsValid(MyHUD))
  {
    ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
    if (IsValid(UIManager))
    {
      //Battleの画面を閉じる
      UIManager->CloseBranchMessageDisplay();
    }
  }
}


/// <summary>
/// DisplayCoinNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::DisplayCoinNum() {

  if (IsValid(MyHUD))
  {
    ABattleUiManager* UIManager = Cast<ABattleUiManager>(MyHUD);
    if (IsValid(UIManager))
    {
      //Battleの画面を開く
      UIManager->OpenCoinNumDisplay();
    }
  }
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ABattleController::Tick(float DeltaTime) {

    Super::Tick(DeltaTime);

    //Leftを押された場合
    if (IsInputKeyDown("Left") && IsPushedPreFrame == false) {
        UE_LOG(LogTemp, Warning, TEXT("Left"));
        IsPushed = true;
        OnLeft();
    }
    //Rightを押された場合
    else if (IsInputKeyDown("Right") && IsPushedPreFrame == false) {
        UE_LOG(LogTemp, Warning, TEXT("Right"));
        IsPushed = true;
        OnRight();
    }
    //どちらも押されていない場合
    else if ((!IsInputKeyDown("Right")) && (!IsInputKeyDown("Left"))) {
        IsPushed = false;
    }

    //前回フレームの押されたかのフラグを、今回フレームの押されたかのフラグで更新する
    IsPushedPreFrame = IsPushed;

}

/// <summary>
/// OnLeft関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::OnLeft() {
    UE_LOG(LogTemp, Warning, TEXT("OnLeft"));

    if (IsPushed) {
        //左のキーが押されていたら、
    }
}

/// <summary>
/// OnRight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ABattleController::OnRight() {
    UE_LOG(LogTemp, Warning, TEXT("OnRight"));

    if (IsPushed) {
        //右のキーが押されていたら、
    }
}

/// <summary>
/// IsPush関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>左右どちらかのキーが押されたフラグ</returns>
bool ABattleController::IsPush() {
    return IsPushed;
}

