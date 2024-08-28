#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WoodBridge.generated.h"

/// <summary>
/// 名前空間WoodBridgeNameSpace
/// </summary>
namespace WoodBridgeNameSpace {

}

/// <summary>
/// WoodBridgeクラス
/// </summary>
UCLASS()
class AWoodBridge : public AActor
{
	GENERATED_BODY()
	
public:	
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
	AWoodBridge();

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
