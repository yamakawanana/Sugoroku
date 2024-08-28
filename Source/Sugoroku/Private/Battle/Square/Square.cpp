#include "Battle/Square/Square.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ASquare::ASquare()
{
 	// Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ASquare::BeginPlay()
{
  Super::BeginPlay();

  //ボードにマスを配置して初期化
  //InitializeBoardData();

  PassedLocations.SetNum(DiceNameSpace::Four);
	
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ASquare::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

/// <summary>
/// マスの種類を設定する関数の定義
/// </summary>
/// <param = "X">指定したX位置</param>
/// <param = "Y">指定したY位置</param>
/// <param = "RoadType Type">マスの種類</param>
/// <returns>なし</returns>
void ASquare::SetBoardData(int32 X, int32 Y, RoadType Type)
{
  BoardData[Y][X] = Type;
}

/// <summary>
/// マスの種類を取得する関数の定義
/// </summary>
/// <param = "X">指定したX位置</param>
/// <param = "Y">指定したY位置</param>
/// <returns>マスの種類</returns>
RoadType ASquare::GetBoardData(int32 X, int32 Y) {
  return BoardData[Y][X];
}

/// <summary>
/// ボードを初期化する関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ASquare::InitializeBoardData() {

}

/// <summary>
/// AddTargetLocations関数の定義
/// </summary>
/// <param ="Location">追加する目標地点</param>
/// <returns>なし</returns>
void ASquare::AddTargetLocations(FVector Location) {
  WayPointLocations.Add(Location);
}

/// <summary>
/// AddPassedLocations関数の定義
/// </summary>
/// <param ="Location">追加する既に通過した地点</param>
/// <returns>なし</returns>
void ASquare::AddPassedLocations(FVector Location, int32 CharacterIndex) {
  PassedLocations[CharacterIndex].Locations.Add(Location);
}

/// <summary>
/// AddSearchPassedLocations関数の定義
/// </summary>
/// <param ="Location">追加する幅優先探索用の既に通過した地点</param>
/// <returns>なし</returns>
void ASquare::AddSearchPassedLocations(FVector Location) {
  SearchPassedLocations.Add(Location);
}

/// <summary>
/// InitSearchPassedLocations関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ASquare::InitSearchPassedLocations() {
  //SearchPassedLocationsを初期化する
  SearchPassedLocations.Empty();
}

/// <summary>
/// GetTargetLocations関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>目標地点</returns>
FVector ASquare::GetTargetLocations(int32 Index) {
  return WayPointLocations[Index];
}

/// <summary>
/// GetPassedLocations関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>既に通った地点</returns>
FVector ASquare::GetPassedLocations(int32 Index, int32 CharacterIndex) {
  return PassedLocations[CharacterIndex].Locations[Index];
}

/// <summary>
/// GetTargetLocationsNum関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>TargetLocationsに格納されている位置の数</returns>
int32 ASquare::GetTargetLocationsNum() {
  return WayPointLocations.Num();
}

/// <summary>
/// GetPassedLocationsNum関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>TargetLocationsに格納されている位置の数</returns>
int32 ASquare::GetPassedLocationsNum(int32 CharacterIndex) {
  return PassedLocations[CharacterIndex].Locations.Num();
}

/// <summary>
/// CheckLocationIsPassed関数の宣言
/// </summary>
/// <param>マスの位置情報</param>
/// <returns>引数の位置情報がPassedLocationsに含まれているか</returns>
bool ASquare::CheckLocationIsPassed(FVector& Location, int32 CharacterIndex)
{
  for (FVector PassedLocation : PassedLocations[CharacterIndex].Locations)
  {
    if (PassedLocation == Location)
    {

      UE_LOG(LogTemp, Warning, TEXT("そこは通った"));
      return true;
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("通っていない"));
  return false;
}

/// <summary>
/// CheckSearchLocationIsPassed関数の宣言
/// </summary>
/// <param>マスの位置情報</param>
/// <returns>引数の位置情報がPassedLocationsに含まれているか</returns>
bool ASquare::CheckSearchLocationIsPassed(FVector& Location)
{
  for (FVector SearchPassedLocation : SearchPassedLocations)
  {
    if (SearchPassedLocation == Location)
    {

      UE_LOG(LogTemp, Warning, TEXT("そこは通った"));
      return true;
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("通っていない"));
  return false;
}

/// <summary>
/// GetLastPassedLocations関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>既に通った地点</returns>
FVector ASquare::GetLastPassedLocations(int32 CharacterIndex) {
  return PassedLocations[CharacterIndex].Locations.Last();
}

/// <summary>
/// RemovePassedLocationsElement関数の定義
/// </summary>
/// <param = "Element">要素番号</param>
/// <returns>なし</returns>
void ASquare::RemovePassedLocationsElement(int32 Element, int32 CharacterIndex) {
  PassedLocations[CharacterIndex].Locations.RemoveAt(Element);
}

/// <summary>
/// AddCornerLocations関数の宣言
/// </summary>
/// <param ="Location">分かれ道以外の曲がり角</param>
/// <returns>なし</returns>
void ASquare::AddCornerLocations(FCharacterRouteAndDirection Location) {
  CornerSquares.Add(Location);
}

/// <summary>
/// GetCornerLocations関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>分かれ道以外の曲がり角</returns>
FCharacterRouteAndDirection ASquare::GetCornerLocations(int32 Element) {
  return CornerSquares[Element];
}

/// <summary>
/// CheckCornerLocations関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ASquare::CheckCornerLocations() {
  int32 LocationsNum = GetTargetLocationsNum();
  //周りのマスが通行可能かのフラグを格納する配列
  bool bCanWalk[DiceNameSpace::Four];
  for (int32 i = 0; i < LocationsNum; ++i) {
    FVector Location = WayPointLocations[i];
    int32 SquareX = StaticCast<int32>(StaticCast<int32>(Location.X) - StaticCast<int32>(SquareNameSpace::SpawnStartYPos)) / SquareNameSpace::SquareDistance;
    int32 SquareY = StaticCast<int32>(StaticCast<int32>(Location.Y - SquareNameSpace::SpawnStartXPos)) / SquareNameSpace::SquareDistance;
    //FString DebugMessage31 = FString::Printf(TEXT("FrontRoadType: %d"), FrontRoadType);
    FString DebugMessage32 = FString::Printf(TEXT("SquareY: %d"), SquareY);
    //GEngine->AddOnScreenDebugMessage(-1, SquareNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage31);
    GEngine->AddOnScreenDebugMessage(-1, SquareNameSpace::TimeToDisplay, FColor::Yellow, DebugMessage32);

    // bCanWalk配列を初期化する
    bCanWalk[StaticCast<int32>(CharacterDirection::Front)] = false;
    bCanWalk[StaticCast<int32>(CharacterDirection::Right)] = false;
    bCanWalk[StaticCast<int32>(CharacterDirection::Left)] = false;
    bCanWalk[StaticCast<int32>(CharacterDirection::Back)] = false;

    //前側のマスの種類を取得する
    if ((SquareX - 1) >= 0) {
      RoadType FrontRoadType = GetBoardData(SquareY, SquareX - 1);
      if (FrontRoadType != RoadType::NoRoad) {
        bCanWalk[StaticCast<int32>(CharacterDirection::Front)] = true;
      }
    }

    //右側のマスの種類を取得する
    if ((SquareY + 1) <= SquareNameSpace::Column) {
      RoadType RightRoadType = GetBoardData(SquareY + 1, SquareX);
      if (RightRoadType != RoadType::NoRoad) {
        bCanWalk[StaticCast<int32>(CharacterDirection::Right)] = true;
      }
    }

    //左側のマスの種類を取得する
    if ((SquareY - 1) >= 0) {
      RoadType LeftRoadType = GetBoardData(SquareY - 1, SquareX);
      if (LeftRoadType != RoadType::NoRoad) {
        bCanWalk[StaticCast<int32>(CharacterDirection::Left)] = true;
      }
    }

    //後側のマスの種類を取得する
    if ((SquareX + 1) <= SquareNameSpace::Row) {
      RoadType BackRoadType = GetBoardData(SquareY, SquareX + 1);
      if (BackRoadType != RoadType::NoRoad) {
        bCanWalk[StaticCast<int32>(CharacterDirection::Back)] = true;
      }
    }

    // 1本道のパターンを除外する
    if ((bCanWalk[StaticCast<int32>(CharacterDirection::Front)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Right)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Left)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Back)])||
      (bCanWalk[StaticCast<int32>(CharacterDirection::Front)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Right)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Left)] && bCanWalk[StaticCast<int32>(CharacterDirection::Back)])||
      (!bCanWalk[StaticCast<int32>(CharacterDirection::Front)] && bCanWalk[StaticCast<int32>(CharacterDirection::Right)] && bCanWalk[StaticCast<int32>(CharacterDirection::Left)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Back)])||
      (!bCanWalk[StaticCast<int32>(CharacterDirection::Front)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Right)] && !bCanWalk[StaticCast<int32>(CharacterDirection::Left)] && bCanWalk[StaticCast<int32>(CharacterDirection::Back)])) {
    }
    else {
      //一本道でなければ曲がり角であるため、CornerSquaresに格納する
      FCharacterRouteAndDirection CornerSquare;
      CornerSquare.Location = Location;
      CornerSquares.Add(CornerSquare);
    }

  }
}

/// <summary>
/// GetCornerLocationsNum関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>CornerLocationsに格納されている位置の数</returns>
int32 ASquare::GetCornerLocationsNum() {
  return CornerSquares.Num();
}