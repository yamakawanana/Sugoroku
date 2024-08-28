#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "TitleLevel.generated.h"

/// <summary>
/// 名前空間TitleNameSpace
/// </summary>
namespace TitleNameSpace {

	/// <summary>
	/// 表示時間を定数TimeToDisplayに格納する
	/// </summary>
	static const float TimeToDisplay = 5.0f;
}

/**
 *
 */

 /// <summary>
 /// TitleLevelクラス
 /// </summary>
UCLASS()
class ATitleLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param>なし</param>
	/// <returns>なし</returns>
	ATitleLevel();

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
