#include "Battle/File/CSVFileManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ACSVFileManager::ACSVFileManager()
{
  // Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ACSVFileManager::BeginPlay()
{
  Super::BeginPlay();
	
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ACSVFileManager::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

/// <summary>
/// SetDataFromFile関数の定義
/// </summary>
/// <param>なし</param>
/// <returns></returns>
void ACSVFileManager::SetDataFromFile() {

  //プロジェクトファイルのパスを取得する
  FString ProjectPath = FPaths::ProjectDir();
  //CSVファイル名を取得する
  FString FileName = ProjectPath + FileNameSpace::MapDataCSV;

  //CSVファイルからデータを取得する
  FString CsvDataFile;
  FFileHelper::LoadFileToString(CsvDataFile, *FileName);

  //列で分解した値を保持する
  TArray<FString> RowData;
  CsvDataFile.ParseIntoArray(RowData, TEXT("\n"), true);

  // CSVファイルのデータをBoardDataに格納する
  for (int32 RowIndex = 0; RowIndex < SquareNameSpace::Row && RowIndex < RowData.Num(); ++RowIndex)
  {
    //行で分解した値を保持する
    TArray<FString> ColumnData;
    RowData[RowIndex].ParseIntoArray(ColumnData, TEXT(","), true);

    for (int32 ColumnIndex = 0; ColumnIndex < SquareNameSpace::Column && ColumnIndex < ColumnData.Num(); ++ColumnIndex)
    {
      //CSVファイルの文字列のデータを整数に変換した値ごとに、RoadTypeの要素を格納する
      switch (FCString::Atoi(*ColumnData[ColumnIndex])) {
      case static_cast<int32>(RoadType::NoRoad):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::NoRoad);
        break;
      case static_cast<int32>(RoadType::Start):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::Start);
        break;
      case static_cast<int32>(RoadType::Goal):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::Goal);
        break;
      case static_cast<int32>(RoadType::NoEvent):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::NoEvent);
        break;
      case static_cast<int32>(RoadType::IncreaseMoney):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::IncreaseMoney);
        break;
      case static_cast<int32>(RoadType::DecreaseMoney):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::DecreaseMoney);
        break;
      case static_cast<int32>(RoadType::ForceMove):
        PreExistSquare->SetBoardData(ColumnIndex, RowIndex, RoadType::ForceMove);
        break;
      }
    }
  }
}

/// <summary>
/// SetSquareClass関数の定義
/// </summary>
/// <param name = "ExistSquare">ExistSquare</param>
/// <returns>なし</returns>
void ACSVFileManager::SetSquareClass(ASquare* ExistSquare) {
  PreExistSquare = ExistSquare;
}