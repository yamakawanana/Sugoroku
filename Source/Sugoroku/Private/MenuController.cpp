#include "MenuController.h"
#include "Title/TitleUiManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Battle/Dice/Dice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
AMenuController::AMenuController() {

}

/// <summary>
/// OpenTitle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AMenuController::OpenTitle() {
    UE_LOG(LogTemp, Warning, TEXT("MenuControllerのOpenTitle"));
    if (IsValid(MyHUD))
    {
        ATitleUiManager* UIManager = Cast<ATitleUiManager>(MyHUD);
        if (IsValid(UIManager))
        {
            UIManager->OpenTitle();
        }
    }
}

/// <summary>
/// SetupInputComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AMenuController::SetupInputComponent() {
    UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent"));

    Super::SetupInputComponent();
    //UE4のアサートマクロ
    check(InputComponent);

    if (IsValid(InputComponent))
    {
        //アクションマッピングとMenuControllerをつなぐ
        InputComponent->BindAction("Decide", IE_Pressed, this, &AMenuController::OnDecide);
        InputComponent->BindAction("Quit", IE_Pressed, this, &AMenuController::OnQuit);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent無効"));
    }
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void AMenuController::Tick(float DeltaTime) {
    //UE_LOG(LogTemp, Warning, TEXT("AMenuController"));

    Super::Tick(DeltaTime);

    //Decideを押された場合
    if (IsInputKeyDown("Decide")) {
        UE_LOG(LogTemp, Warning, TEXT("Decide"));
        OnDecide();
    }
    //Quitを押された場合
    else if (IsInputKeyDown("Quit")) {
        UE_LOG(LogTemp, Warning, TEXT("Quit"));
        OnQuit();
    }
}

/// <summary>
/// OnDecide関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AMenuController::OnDecide() {
    UE_LOG(LogTemp, Warning, TEXT("OnDecide"));
    ATitleUiManager* UIManager = Cast<ATitleUiManager>(MyHUD);
    //タイトルを終了し、画面遷移する
    if (UIManager) {
      UIManager->CloseTitle();
    }
}

/// <summary>
/// OnQuit関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void AMenuController::OnQuit() {
    UE_LOG(LogTemp, Warning, TEXT("OnQuit"));
    //ゲームを終了する
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

