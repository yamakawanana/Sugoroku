#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Battle/Square/Square.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "CSVFileManager.generated.h"

/// <summary>
/// 名前空間FileNameSpace
/// </summary>
namespace FileNameSpace {

  /// <summary>
  /// ボードデータを保存するファイル名を定数MapDataCSVに格納する
  /// </summary>
  static const FString MapDataCSV = "Content/CSVFiles/mapdata.csv";

  /// <summary>
  /// 文字を格納する変数bufの要素数を定数kBufElementに格納する
  /// </summary>
  static const int32 BufElement = 10;
}

/// <summary>
/// CSVFileManagerクラス
/// </summary>
UCLASS()
class ACSVFileManager : public AActor
{
  GENERATED_BODY()
	
public:	
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ACSVFileManager();

private:

  /// <summary>
  // PreExistSquareクラス
  /// <summary>
  UPROPERTY()
  TSubclassOf<class ASquare> PreExistSquareClass;

  /// <summary>
  // PreExistSquare
  /// <summary>
  UPROPERTY()
  ASquare* PreExistSquare;

protected:
  /// <summary>
  /// BeginPlay関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void BeginPlay() override;

public:	
  /// <summary>
  /// Tick関数の宣言
  /// </summary>
  /// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
  /// <returns>なし</returns>
  virtual void Tick(float DeltaTime) override;

  /// <summary>
  /// SetDataFromFile関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns></returns>
  void SetDataFromFile();

  /// <summary>
  /// SetSquareClass関数の宣言
  /// </summary>
  /// <param name = "ExistSquare">ExistSquare</param>
  /// <returns>なし</returns>
  void SetSquareClass(ASquare* ExistSquare);

};
