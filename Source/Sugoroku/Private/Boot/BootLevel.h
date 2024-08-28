#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BootLevel.generated.h"

/**
 *
 */

/// <summary>
/// 名前空間BootNameSpace
/// </summary>
namespace BootNameSpace {
	/// <summary>
	/// 次のレベルに切り替える時間を定数ChangeLevelTimeに格納する
	/// </summary>
	static const float ChangeLevelTime = 2.0f;

	/// <summary>
	/// 表示時間を定数TimeToDisplayに格納する
	/// </summary>
	static const float TimeToDisplay = 5.0f;
}

/// <summary>
/// PhaseType列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class PhaseType : uint8 {

	/// </summary>
	//　アイドル
	/// </summary>
	Idol,

	/// </summary>
	//　レベル遷移
	/// </summary>
	LevelChange,
};

/// <summary>
/// BootLevelクラス
/// </summary>
UCLASS()
class ABootLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	ABootLevel();

private:

	/// </summary>
	//　累積時間
	/// </summary>
	UPROPERTY()
	float AccumulatedTime;

	/// </summary>
	//　フェーズ
	/// </summary>
	UPROPERTY()
	PhaseType Phase;

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

};
