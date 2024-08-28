#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/Square/Square.h"
#include "Battle/PlayerCharacter/PlayerCharacter.h"
#include "RouteSearch.generated.h"

/// <summary>
/// 名前空間RouteSearchNameSpace
/// </summary>
namespace RouteSearchNameSpace {

  /// <summary>
  //キューで管理するデータ数の上限
  /// <summary>
  static const int32 QueueSize = 120;

  /// <summary>
  /// マスをスポーンさせる開始Y位置を定数SpawnStartYPosに格納する
  /// </summary>
  static const float SpawnStartYPos = -80.0f;

  /// <summary>
  /// マスをスポーンさせる開始X位置を定数SpawnStartXPosに格納する
  /// </summary>
  static const float SpawnStartXPos = -450.0f;

  /// <summary>
  /// マスをスポーンさせる開始高さを定数SpawnStartHeightに格納する
  /// </summary>
  static const float SpawnStartHeight = -130.0f;

  /// <summary>
  /// マスとマスの間隔を定数SquareDistanceに格納する
  /// </summary>
  static const int32 SquareDistance = 400;

}

/// <summary>
//Pos構造体型を定義する
/// <summary>
USTRUCT(BlueprintType)
struct FPos {
  GENERATED_BODY()

  int32 X; //幅優先探索で使うX位置
  int32 Y; //幅優先探索で使うY位置
  int32 BeforeX; //1つ前に探索したX位置
  int32 BeforeY; //1つ前に探索したY位置
};

/// <summary>
//Queue構造体型を定義する
/// <summary>
USTRUCT(BlueprintType)
struct FQueue {
  GENERATED_BODY()

  int32 Tail; // キューの最後尾
  int32 Head; // キューの最先端
  FPos QueueData[RouteSearchNameSpace::QueueSize];
};

/// <summary>
/// RouteSearchクラス
/// </summary>
UCLASS()
class ARouteSearch : public AActor
{
  GENERATED_BODY()
	
public:	
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ARouteSearch();

private:

  /// </summary>
  //Queue構造体型の変数
  /// </summary>
  UPROPERTY()
  FQueue QueueValue;

  /// </summary>
  //幅優先探索で通過したルートを保存する配列
  /// </summary>
  UPROPERTY()
  FPos Route[RouteSearchNameSpace::QueueSize];

  /// </summary>
  //幅優先探索の最短経路を保存する配列
  /// </summary>
  UPROPERTY()
  FPos BackTrace[RouteSearchNameSpace::QueueSize];

  /// </summary>
  //最短経路までのマスの数
  /// </summary>
  int32 Routecount;

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
  /// ゴールへの最短経路を特定する
  /// </summary>
  /// <param name = "start_x">現在のX位置</param>
  /// <param name = "start_y">現在のY位置</param>
  /// <returns>なし</returns>
  void SearchNearestRoute(int32 StartX, int32 StartY);

  /// <summary>
  /// 幅優先探索で使うキューを初期化する
  /// </summary>
  /// <param name = "QueueVal">Queue構造体型のQueueVal</param>
  /// <returns>なし</returns>
  void InitQueue(FQueue* QueueVal);

  /// <summary>
  /// 幅優先探索で使うRoute配列を初期化する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void InitRoute();

  /// <summary>
  /// 幅優先探索で使うBackTrace配列を初期化する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void InitBackTrace();

  /// <summary>
  /// キューに要素を追加する
  /// </summary>
  /// <param name = "queue">Queue構造体型のqueue</param>
  /// <param name = "input">Pos構造体型のinput</param>
  /// <returns>なし</returns>
  void Enqueue(FQueue* Queue, FPos* Input);

  /// <summary>
  /// キューから要素を取り出す
  /// </summary>
  /// <param name = "queue">Queue構造体型のqueue</param>
  /// <returns>キューから取り出したPos構造体型の要素</returns>
  FPos* Dequeue(FQueue* Queue);

  /// <summary>
  /// ゴールまでの最短経路を保存する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  int32 SaveNearestRoute(int32 ElementNum);

  /// <summary>
  /// CalculateSpawnPos関数の定義
  /// </summary>
  /// <param = "I">指定したX位置</param>
  /// <param = "J">指定したY位置</param>
  /// <returns>なし</returns>
  FVector CalculateSpawnPos(int32 I, int32 J);

  /// <summary>
  /// IsCanWalk関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  bool IsCanWalk(RoadType Type);

  /// <summary>
  /// GetBackTraceLocations関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>BackTraceに格納した地点</returns>
  FPos GetBackTraceLocations(int32 Index);

  /// <summary>
  /// GetRoutecount関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最短経路までのマスの数</returns>
  int32 GetRoutecount();

  /// <summary>
  /// SetSquareClass関数の宣言
  /// </summary>
  /// <param name = "ExistSquare">ExistSquare</param>
  /// <returns>なし</returns>
  void SetSquareClass(ASquare* ExistSquare);

  /// <summary>
  /// CheckMatchSquare関数の宣言
  /// </summary>
  /// <param name = "Squares">複数のマスと方向の情報</param>
  /// <returns>最短経路に含まれないマスと方向の情報</returns>
  void CheckNotMatchSquare(TArray<FCharacterRouteAndDirection>& Squares);

  /// <summary>
  /// 経路が順路と逆方向にならないか確認する
  /// </summary>
  /// <param name = "start_x">探索開始するX位置</param>
  /// <param name = "start_y">探索開始するY位置</param>
  /// <returns>なし</returns>
  bool IsNotBack(int32 StartX, int32 StartY);

  /// <summary>
  /// AddPosAndDirections関数の宣言
  /// </summary>
  /// <param name = "Poss">複数のマスと方向の情報</param>
  /// <param name = "Pos">マスと方向の情報</param>
  /// <param name = "Location">位置情報</param>
  /// <returns>なし</returns>
  void AddPosAndDirections(TArray<FCharacterRouteAndDirection>& Poss, FCharacterRouteAndDirection& Pos, FVector Location);
};
