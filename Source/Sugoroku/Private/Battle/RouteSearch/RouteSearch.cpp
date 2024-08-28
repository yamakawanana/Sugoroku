#include "Battle/RouteSearch/RouteSearch.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ARouteSearch::ARouteSearch()
{
  // Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ARouteSearch::BeginPlay()
{
  Super::BeginPlay();
  
}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void ARouteSearch::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

/// <summary>
/// ゴールへの最短経路を特定する
/// </summary>
/// <param name = "start_x">現在のX位置</param>
/// <param name = "start_y">現在のY位置</param>
/// <returns>なし</returns>
void ARouteSearch::SearchNearestRoute(int32 StartX, int32 StartY) {
  //キューを初期化する
  InitQueue(&QueueValue);
  //Route配列を初期化する
  InitRoute();
  //BackTrace配列を初期化する
  InitBackTrace();
  //Routecountを初期化する
  Routecount = 0;
  //SearchPassedLocationsを初期化する
  PreExistSquare->InitSearchPassedLocations();

  //Pos構造体の宣言
  FPos Pos;

  //Route配列の要素番号の整数を用意する
  int32 ElementNum = 0;

  //探索するX位置とY位置に、現在の位置を格納する
  Pos.X = StartX;
  Pos.Y = StartY;

  //スタート時は1つ前の探索位置が無いため、-1にする
  Pos.BeforeX = -1;
  Pos.BeforeY = -1;

  //Queue構造体と探索位置の情報をキューに追加する
  Enqueue(&QueueValue, &Pos);

  while (true) {
    //探索するX位置
    int32 XPos;
    //探索するY位置
    int32 YPos;

    //キューから要素を取り出し、次の探索位置とする
    FPos* Next = Dequeue(&QueueValue);

    //キューから取り出した次の探索候補の要素のX位置とY位置を探索する位置にする
    XPos = Next->X;
    YPos = Next->Y;

    //キューから取り出した次の探索候補の要素をRoute配列に保存してから、Route配列の要素番号を増やす
    Route[ElementNum] = *Next;
    ElementNum++;

    //探索位置のボードデータ上のマスの種類を取得する
    RoadType MapType = PreExistSquare->GetBoardData(YPos, XPos);

    //ゴールに着いたら、処理を終了する
    if (MapType == RoadType::Goal) {

      //最短経路を保存する
      //最短経路までの歩数も保存する
      Routecount = SaveNearestRoute(ElementNum);

      break;
    }

    //XPosとYPosから該当するマスの位置を取得する
    FVector PassedPos = CalculateSpawnPos(XPos, YPos);
    //既に探索した位置を通過済みのマスとして配列に追加する
    PreExistSquare->AddSearchPassedLocations(PassedPos);

    //右側のマスの種類を取得する
    RoadType RightRoadType = PreExistSquare->GetBoardData(YPos + 1, XPos);
    //右方向に進める場合
    if (IsCanWalk(RightRoadType)) {
      //XPosとYPosから該当するマスの位置を取得する
      FVector RightPos = CalculateSpawnPos(XPos, YPos + 1);
      //既に探索済みのマスではないか確認する
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(RightPos);

      if (!IsPassed) {
        Pos.X = XPos;
        Pos.Y = (std::min)(YPos + 1, SquareNameSpace::Row - 1);
        Pos.BeforeX = XPos;
        Pos.BeforeY = YPos;

        //右上方向の位置をキューに追加する
        Enqueue(&QueueValue, &Pos);
      }

    }

    //左側のマスの種類を取得する
    RoadType LeftRoadType = PreExistSquare->GetBoardData(YPos - 1, XPos);
    //左方向に進める場合
    if (IsCanWalk(LeftRoadType)) {
      //XPosとYPosから該当するマスの位置を取得する
      FVector LeftPos = CalculateSpawnPos(XPos, YPos - 1);
      //既に探索済みのマスではないか確認する
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(LeftPos);

      if (!IsPassed) {
        Pos.X = XPos;
        Pos.Y = (std::max)(YPos - 1, 0);
        Pos.BeforeX = XPos;
        Pos.BeforeY = YPos;

        //左方向の位置をキューに追加する
        Enqueue(&QueueValue, &Pos);
      }
    }

    //前側のマスの種類を取得する
    RoadType FrontRoadType = PreExistSquare->GetBoardData(YPos, XPos - 1);
    if (IsCanWalk(FrontRoadType)) {
      //XPosとYPosから該当するマスの位置を取得する
      FVector FrontPos = CalculateSpawnPos(XPos - 1, YPos);
      //既に探索済みのマスではないか確認する
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(FrontPos);

      if (!IsPassed) {
        Pos.X = (std::max)(XPos - 1, 0);
        Pos.Y = YPos;
        Pos.BeforeX = XPos;
        Pos.BeforeY = YPos;

        //前方向の位置をキューに追加する
        Enqueue(&QueueValue, &Pos);
      }
    }
  }
}

/// <summary>
/// 幅優先探索で使うキューを初期化する
/// </summary>
/// <param name = "QueueVal">Queue構造体型のQueueVal</param>
/// <returns>なし</returns>
void ARouteSearch::InitQueue(FQueue* QueueVal) {

  //キューの先頭と末尾を空の状態に初期化する
  QueueVal->Head = 0;
  QueueVal->Tail = -1;
}

/// <summary>
/// 幅優先探索で使うRoute配列を初期化する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ARouteSearch::InitRoute() {
  for (int i = 0; i < RouteSearchNameSpace::QueueSize; ++i) {
    Route[i].X = 0;
    Route[i].Y = 0;
    Route[i].BeforeX = 0;
    Route[i].BeforeY = 0;
  }
}

/// <summary>
/// 幅優先探索で使うBackTrace配列を初期化する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ARouteSearch::InitBackTrace() {
  for (int i = 0; i < RouteSearchNameSpace::QueueSize; ++i) {
    BackTrace[i].X = 0;
    BackTrace[i].Y = 0;
    BackTrace[i].BeforeX = 0;
    BackTrace[i].BeforeY = 0;
  }
}

/// <summary>
/// キューに要素を追加する
/// </summary>
/// <param name = "queue">Queue構造体型のポインタ</param>
/// <param name = "input">Pos構造体型のポインタ</param>
/// <returns>なし</returns>
void ARouteSearch::Enqueue(FQueue* Queue, FPos* Input) {
  // データをデータの最後尾の１つ後ろに格納
  Queue->QueueData[(Queue->Tail + 1) % RouteSearchNameSpace::QueueSize] = *Input;

  // データの最後尾を１つ後ろに移動
  Queue->Tail = (Queue->Tail + 1) % RouteSearchNameSpace::QueueSize;
}

/// <summary>
/// キューから要素を取り出す
/// </summary>
/// <param name = "queue">Queue構造体のポインタ</param>
/// <returns>キューから取り出したPos構造体型の要素</returns>
FPos* ARouteSearch::Dequeue(FQueue* Queue) {
  //返す値であるPos構造体型のポインタreturn_dataを定義する
  FPos* ReturnData;

  //キューが空である場合
  if ((Queue->Tail + 1) % RouteSearchNameSpace::QueueSize == Queue->Head) {
    return NULL;
  }

  // 先頭からデータを取得する
  ReturnData = &(Queue->QueueData[Queue->Head]);

  // データの先頭を１つ後ろにずらす 
  Queue->Head = (Queue->Head + 1) % RouteSearchNameSpace::QueueSize;

  // 取得したデータを返す
  return ReturnData;
}

/// <summary>
/// ゴールまでの最短経路を保存する
/// </summary>
/// <param = "element_num"></param>
/// <returns>なし</returns>
int32 ARouteSearch::SaveNearestRoute(int32 ElementNum) {

  //BackTraceの要素番号として使う整数を用意する
  int32 Count = 0;

  //最後に通った位置の要素番号
  int32 Element = ElementNum - 1;

  while (true) {

    //route_配列内の、要素番号に対応する通過した位置の情報をpos変数に格納する
    FPos Pos = Route[Element];
    //back_trace_配列のcount番目の要素に通過した位置の情報posを格納する
    BackTrace[Count] = Pos;

    Count++;

    //前に通過した位置が無ければ、処理を終了する
    if (Pos.BeforeX == -1 && Pos.BeforeY == -1) {
      break;
    }

    //現在の探索位置の前に通過した位置の要素番号
    int BeforeElement = Element - 1;

    //現在の位置の前に通過した位置と一致する位置がroute_配列内にあったら、その位置をelementに設定する
    for (BeforeElement; BeforeElement >= 0; BeforeElement--) {
      if (Route[BeforeElement].X == Pos.BeforeX && Route[BeforeElement].Y == Pos.BeforeY) {
        Element = BeforeElement;
        break;
      }
    }
  }

  for (int32 ElementNumber = Count - 1; ElementNumber >= 0; ElementNumber--) {
    //ゴールからスタートまでの経路を表示する
    //FString DebugMessage15 = FString::Printf(TEXT("BackTrace[ElementNumber].X: %d"), BackTrace[ElementNumber].X);
    //GEngine->AddOnScreenDebugMessage(-1, 40.0f, FColor::White, DebugMessage15);
    //FString DebugMessage16 = FString::Printf(TEXT("BackTrace[ElementNumber].Y: %d"), BackTrace[ElementNumber].Y);
    //GEngine->AddOnScreenDebugMessage(-1, 40.0f, FColor::White, DebugMessage16);

  }

  return Count;

}

/// <summary>
/// CalculateSpawnPos関数の定義
/// </summary>
/// <param = "I">指定したX位置</param>
/// <param = "J">指定したY位置</param>
/// <returns>なし</returns>
FVector ARouteSearch::CalculateSpawnPos(int32 I, int32 J) {
  FVector Loc(RouteSearchNameSpace::SpawnStartYPos + static_cast<float>(RouteSearchNameSpace::SquareDistance * I), RouteSearchNameSpace::SpawnStartXPos + static_cast<float>(RouteSearchNameSpace::SquareDistance * J), RouteSearchNameSpace::SpawnStartHeight);
  return Loc;
}

/// <summary>
/// IsCanWalk関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
bool ARouteSearch::IsCanWalk(RoadType Type) {
  //マスが存在するRoadTypeの場合のみ、trueにする
  if (Type == RoadType::Goal || Type == RoadType::NoEvent || Type == RoadType::IncreaseMoney || Type == RoadType::DecreaseMoney || Type == RoadType::ForceMove) {
    return true;
  }
  return false;
}

/// <summary>
/// GetBackTraceLocations関数の定義
/// </summary>
/// <param>要素番号</param>
/// <returns>既に通った地点</returns>
FPos ARouteSearch::GetBackTraceLocations(int32 Index) {
  return BackTrace[Index];
}

/// <summary>
/// GetRoutecount関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>最短経路までのマスの数</returns>
int32 ARouteSearch::GetRoutecount() {
  return Routecount;
}

/// <summary>
/// SetSquareClass関数の定義
/// </summary>
/// <param name = "ExistSquare">ExistSquare</param>
/// <returns>なし</returns>
void ARouteSearch::SetSquareClass(ASquare* ExistSquare) {
  PreExistSquare = ExistSquare;
}

/// <summary>
/// CheckMatchSquare関数の定義
/// </summary>
/// <param name = "Squares">複数のマスと方向の情報</param>
/// <returns>最短経路に含まれないマスと方向の情報</returns>
void ARouteSearch::CheckNotMatchSquare(TArray<FCharacterRouteAndDirection>& Squares) {

  for (int32 Index = 0; Index < RouteSearchNameSpace::QueueSize; ++Index)
  {
    // BackTraceに格納されているX位置とY位置を取得する
    int32 X = BackTrace[Index].X;
    int32 Y = BackTrace[Index].Y;

    // X位置とY位置に対応するFVectorの位置を取得する
    FVector Location = CalculateSpawnPos(X, Y);

    for (int32 SquareIndex = 0; SquareIndex < Squares.Num(); ++SquareIndex)
    {
      FCharacterRouteAndDirection& Square = Squares[SquareIndex];
      // BackTraceの位置とSquaresの位置が一致するか確認
      if (Square.Location == Location)
      {
        // 一致する場合、Squareを消す
        Squares.RemoveAt(SquareIndex);
      }
    }
  }
}

/// <summary>
/// 経路が順路と逆方向にならないか確認する
/// </summary>
/// <param name = "start_x">探索開始するX位置</param>
/// <param name = "start_y">探索開始するY位置</param>
/// <returns>なし</returns>
bool ARouteSearch::IsNotBack(int32 StartX, int32 StartY) {
  //Route配列を初期化する
  InitRoute();
  //Routecountを初期化する
  Routecount = 0;

  //探索開始地点を通過済みのマスとして追加する
  FVector FirstRoad = CalculateSpawnPos(StartX, StartY);
  PreExistSquare->AddSearchPassedLocations(FirstRoad);

  //進むことが可能なマスの位置を格納する配列
  TArray<FCharacterRouteAndDirection> CanWalkSquares;
  FCharacterRouteAndDirection CanWalkSquare;

  // 全てのマスの数を取得する
  int32 NumElements = PreExistSquare->GetTargetLocationsNum();
  for (int32 i = 0; i < NumElements; ++i) {

    //前側のマスの種類を取得する
    RoadType FrontRoadType = PreExistSquare->GetBoardData(StartY, StartX - 1);
    if (IsCanWalk(FrontRoadType)) {
      FVector Road = CalculateSpawnPos(StartX - 1, StartY);
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(Road);
      if (!IsPassed) {
        CanWalkSquare.Direction = CharacterDirection::Front;
        AddPosAndDirections(CanWalkSquares, CanWalkSquare, Road);
        StartX = StartX - 1;
        continue;
      }
    }

    //右側のマスの種類を取得する
    RoadType RightRoadType = PreExistSquare->GetBoardData(StartY + 1, StartX);
    if (IsCanWalk(RightRoadType)) {

      FVector Road = CalculateSpawnPos(StartX, StartY + 1);
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(Road);
      if (!IsPassed) {
        CanWalkSquare.Direction = CharacterDirection::Right;
        AddPosAndDirections(CanWalkSquares, CanWalkSquare, Road);
        StartY = StartY + 1;
        continue;
      }
    }

    //左側のマスの種類を取得する
    RoadType LeftRoadType = PreExistSquare->GetBoardData(StartY - 1, StartX);
    if (IsCanWalk(LeftRoadType)) {
      FVector Road = CalculateSpawnPos(StartX, StartY - 1);
      bool IsPassed = PreExistSquare->CheckSearchLocationIsPassed(Road);
      if (!IsPassed) {
        CanWalkSquare.Direction = CharacterDirection::Left;
        AddPosAndDirections(CanWalkSquares, CanWalkSquare, Road);
        StartY = StartY - 1;
        continue;
      }
    }

  }

  //最終的に止まった箇所のマスの種類を取得する
  RoadType FinalRoadType = PreExistSquare->GetBoardData(StartY, StartX);

  if (FinalRoadType == RoadType::Goal) {
    return true;
  }
  //最終的に止まった箇所がゴールでない場合は通行不可能なマスを探索したことになる
  return false;
}

/// <summary>
/// AddPosAndDirections関数の定義
/// </summary>
/// <param name = "Poss">複数のマスと方向の情報</param>
/// <param name = "Pos">マスと方向の情報</param>
/// <param name = "Location">位置情報</param>
/// <returns>なし</returns>
void ARouteSearch::AddPosAndDirections(TArray<FCharacterRouteAndDirection>& Poss, FCharacterRouteAndDirection& Pos, FVector Location) {
  //探索用の通過済みのマスにLocationを追加
  PreExistSquare->AddSearchPassedLocations(Location);
  Pos.Location = Location;
  //マスと方向の情報を格納する配列に保存する
  Poss.Add(Pos);
}

