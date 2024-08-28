#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/PlayerCharacter/PlayerCharacter.h"
#include "Battle/Dice/Dice.h"
#include "Square.generated.h"

/// <summary>
/// 名前空間SquareNameSpace
/// </summary>
namespace SquareNameSpace {

  /// <summary>
  /// 表示時間を定数TimeToDisplayに格納する
  /// </summary>
  static const float TimeToDisplay = 5.0f;

  /// <summary>
  /// BoardDataの行の数を定数Rowに格納する
  /// </summary>
  static const int32 Row = 17;

  /// <summary>
  /// BoardDataの列の数を定数Columnに格納する
  /// </summary>
  static const int32 Column = 7;

  /// <summary>
  /// マスとマスの間隔を定数SquareDistanceに格納する
  /// </summary>
  static const int32 SquareDistance = 400;

  /// <summary>
  /// マスをスポーンさせる開始Y位置を定数SpawnStartYPosに格納する
  /// </summary>
  static const float SpawnStartYPos = -80.0f;

  /// <summary>
  /// マスをスポーンさせる開始X位置を定数SpawnStartXPosに格納する
  /// </summary>
  static const float SpawnStartXPos = -450.0f;
}

/// <summary>
/// RoadType列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class RoadType : uint8 {

  /// </summary>
  //　道ではない
  /// </summary>
  NoRoad,

  /// </summary>
  //　スタート
  /// </summary>
  Start,

  /// </summary>
  //　ゴール
  /// </summary>
  Goal,

  /// </summary>
  //　何もイベントがない
  /// </summary>
  NoEvent,

  /// </summary>
  //　所持金が増加するマス
  /// </summary>
  IncreaseMoney,

  /// </summary>
  //　所持金が減少するマス
  /// </summary>
  DecreaseMoney,

  /// </summary>
  //　強制移動するマス
  /// </summary>
  ForceMove,
};

/// <summary>
//FPassedLocationArray構造体型を定義する
/// <summary>
USTRUCT(BlueprintType)
struct FPassedLocationArray {
  GENERATED_BODY()

  /// <summary>
  /// 通過済みのマス
  /// </summary>
  UPROPERTY()
  TArray<FVector> Locations;

};

/// <summary>
/// Squareクラス
/// </summary>
UCLASS()
class ASquare : public AActor
{
  GENERATED_BODY()
	
public:	
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ASquare();

private:
  /// <summary>
  /// ボードデータ
  /// </summary>
  RoadType BoardData[SquareNameSpace::Row][SquareNameSpace::Column];

  /// <summary>
  /// 目的位置を格納する配列
  /// </summary>
  UPROPERTY()
  TArray<FVector> WayPointLocations;

  /// <summary>
  /// 既に通った位置を格納する配列
  /// </summary>
  UPROPERTY()
  TArray<FPassedLocationArray> PassedLocations;

  /// <summary>
  /// 幅優先探索で既に通った位置を格納する配列
  /// </summary>
  UPROPERTY()
  TArray<FVector> SearchPassedLocations;

  /// <summary>
  /// 分かれ道以外の曲がり角の情報を保存する配列
  /// </summary>
  TArray<FCharacterRouteAndDirection> CornerSquares;

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
  /// マスの種類を設定する関数の宣言
  /// </summary>
  /// <param = "X">指定したX位置</param>
  /// <param = "Y">指定したY位置</param>
  /// <param = "RoadType Type">マスの種類</param>
  /// <returns>なし</returns>
  void SetBoardData(int x, int y, RoadType Type);

  /// <summary>
  /// マスの種類を取得する関数の宣言
  /// </summary>
  /// <param = "X">指定したX位置</param>
  /// <param = "Y">指定したY位置</param>
  /// <returns>マスの種類</returns>
  RoadType GetBoardData(int32 x, int32 y);

  /// <summary>
  /// ボードを初期化する関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void InitializeBoardData();

  /// <summary>
  /// AddTargetLocations関数の宣言
  /// </summary>
  /// <param ="Location">追加する目標地点</param>
  /// <returns>なし</returns>
  void AddTargetLocations(FVector Location);

  /// <summary>
  /// AddPassedLocations関数の宣言
  /// </summary>
  /// <param ="Location">追加する既に通過した地点</param>
  /// <returns>なし</returns>
  void AddPassedLocations(FVector Location, int32 CharacterIndex);

  /// <summary>
  /// AddSearchPassedLocations関数の宣言
  /// </summary>
  /// <param ="Location">追加する幅優先探索用の既に通過した地点</param>
  /// <returns>なし</returns>
  void AddSearchPassedLocations(FVector Location);

  /// <summary>
  /// InitSearchPassedLocations関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void InitSearchPassedLocations();

  /// <summary>
  /// GetTargetLocations関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>目標地点</returns>
  FVector GetTargetLocations(int32 Index);

  /// <summary>
  /// GetPassedLocations関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>既に通った地点</returns>
  FVector GetPassedLocations(int32 Index, int32 CharacterIndex);

  /// <summary>
  /// GetTargetLocationsNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>TargetLocationsに格納されている位置の数</returns>
  int32 GetTargetLocationsNum();

  /// <summary>
  /// GetPassedLocationsNum関数の定義
  /// </summary>
  /// <param>なし</param>
  /// <returns>PassedLocationsに格納されている位置の数</returns>
  int32 GetPassedLocationsNum(int32 CharacterIndex);

  /// <summary>
  /// CheckLocationIsPassed関数の宣言
  /// </summary>
  /// <param>マスの位置情報</param>
  /// <returns>引数の位置情報がPassedLocationsに含まれているか</returns>
  bool CheckLocationIsPassed(FVector& Location, int32 CharacterIndex);

  /// <summary>
  /// CheckSearchLocationIsPassed関数の宣言
  /// </summary>
  /// <param>マスの位置情報</param>
  /// <returns>引数の位置情報がSearchPassedLocationsに含まれているか</returns>
  bool CheckSearchLocationIsPassed(FVector& Location);

  /// <summary>
  /// GetLastPassedLocations関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最後に通った地点</returns>
  FVector GetLastPassedLocations(int32 CharacterIndex);

  /// <summary>
  /// RemovePassedLocationsElement関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>なし</returns>
  void RemovePassedLocationsElement(int32 Element, int32 CharacterIndex);

  /// <summary>
  /// AddCornerLocations関数の宣言
  /// </summary>
  /// <param ="Location">分かれ道以外の曲がり角</param>
  /// <returns>なし</returns>
  void AddCornerLocations(FCharacterRouteAndDirection Location);

  /// <summary>
  /// GetCornerLocations関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>分かれ道以外の曲がり角</returns>
  FCharacterRouteAndDirection GetCornerLocations(int32 Element);

  /// <summary>
  /// CheckCornerLocations関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void CheckCornerLocations();

  /// <summary>
  /// GetCornerLocationsNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>CornerLocationsに格納されている位置の数</returns>
  int32 GetCornerLocationsNum();
};
