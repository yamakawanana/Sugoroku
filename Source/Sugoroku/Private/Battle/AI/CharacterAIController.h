#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Containers/Array.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "CharacterAIController.generated.h"

/// <summary>
/// 名前空間CharacterAIControllerNameSpace
/// </summary>
namespace CharacterAIControllerNameSpace {

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
    /// スポーン時のX位置を微調整する値を定数AdjustmentXに格納する
    /// </summary>
    static const float AdjustmentX = 50.0f;
}

/**
 * 
 */
/// <summary>
/// CharacterAIControllerクラス
/// </summary>
UCLASS()
class ACharacterAIController : public AAIController
{
	  GENERATED_BODY()

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    ACharacterAIController(const class FObjectInitializer& PCIP);

protected:

    /// <summary>
    /// ビヘイビアツリー
    /// </summary>
    UPROPERTY(BlueprintReadWrite)
    class UBehaviorTree* Bt;

    /// <summary>
    /// ブラックボード
    /// </summary>
    UPROPERTY(BlueprintReadWrite)
    class UBlackboardComponent* Bb;

    /// <summary>
    /// ターゲットポイントを格納する配列
    /// </summary>
    UPROPERTY(BlueprintReadWrite)
    TArray<ATargetPoint*> WayPointTarget;

    /// <summary>
    /// ターゲット位置
    /// </summary>
    UPROPERTY(BlueprintReadWrite)
    FVector NewTargetLoc;

    /// <summary>
    /// ボードの二次元配列上のキャラクターの現在X位置
    /// </summary>
    int32 NowPosX;

    /// <summary>
    /// ボードの二次元配列上のキャラクターの現在Y位置
    /// </summary>
    int32 NowPosY;

    /// <summary>
    /// マス目番号
    /// </summary>
    int32 SquareIndex;

    /// <summary>
    // Squareクラス
    /// <summary>
    UPROPERTY()
    TSubclassOf<class ASquare> SquareClass;

    /// <summary>
    // Square
    /// <summary>
    UPROPERTY()
    ASquare* Square;

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
    /// DecideTargetPoint関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    void DecideTargetPoint();

    /// <summary>
    /// GetTargetPoint関数の宣言
    /// </summary>
    /// <param>なし</param>
    /// <returns>なし</returns>
    FVector GetTargetPoint();

    /// <summary>
    /// SetTargetLoc関数の宣言
    /// </summary>
    /// <param = "Loc">ターゲットポイントにする位置</param>
    /// <returns>なし</returns>
    void SetTargetLoc(FVector Loc);
	
};
