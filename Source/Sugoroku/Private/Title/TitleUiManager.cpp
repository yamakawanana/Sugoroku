#include "Title/TitleUiManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/SugorokuGameInstance.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ATitleUiManager::ATitleUiManager()
    : TitleWidgetClass(nullptr)
    , TitleWidget(nullptr)
{

}

/// <summary>
/// PreInitializeComponents関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ATitleUiManager::PreInitializeComponents() {
    USugorokuGameInstance* GameInstance = Cast<USugorokuGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    FString TitleWidgetPath = "/Game/Widgets/WBP_Title.WBP_Title_C";

    //取得したTitleWidgetPathのアセットをロードする
    TitleWidgetClass = TSoftClassPtr<USugorokuWidget>(FSoftObjectPath(*TitleWidgetPath)).LoadSynchronous();
    if (TitleWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("TitleWidgetCreateWidget"));
        //タイトルウィジェットを作成する
        TitleWidget = CreateWidget<USugorokuWidget>(GetWorld(), TitleWidgetClass);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("NonTitleWidgetClass"));
    }
}

/// <summary>
/// OpenTitle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ATitleUiManager::OpenTitle() {
    UE_LOG(LogTemp, Warning, TEXT("ATitleUiManagerのOpenTitle"));
    //タイトルウィジェットを開く
    TitleWidget->Open();
}

/// <summary>
/// CloseTitle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ATitleUiManager::CloseTitle() {
    //タイトルウィジェットを終了する
    TitleWidget->Close();
}

