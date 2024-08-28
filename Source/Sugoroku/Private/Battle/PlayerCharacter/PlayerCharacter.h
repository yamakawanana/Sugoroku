#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/// <summary>
/// 名前空間PlayerCharacterNameSpace
/// </summary>
namespace PlayerCharacterNameSpace {

  /// <summary>
  /// 表示時間を定数TimeToDisplayに格納する
  /// </summary>
  static const float TimeToDisplay = 5.0f;

}

/// <summary>
/// CharacterStatus列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class CharacterStatus : uint8 {

  /// </summary>
  //　通常時
  /// </summary>
  Normal,

  /// </summary>
  //　喜んでいる
  /// </summary>
  Happy,

  /// </summary>
  //　悔しがっている
  /// </summary>
  Regret,

  /// </summary>
  //　驚いている
  /// </summary>
  Surprise,
};

/// <summary>
/// CharacterDirection列挙体の定義
/// </summary>
UENUM(BlueprintType)
enum class CharacterDirection : uint8 {
  /// </summary>
  //　前
  /// </summary>
  Front,

  /// </summary>
  //　右
  /// </summary>
  Right,

  /// </summary>
  //　左
  /// </summary>
  Left,

  /// </summary>
  //　後ろ
  /// </summary>
  Back,
};

/// <summary>
//CharacterRouteAndDirection構造体型を定義する
/// <summary>
USTRUCT(BlueprintType)
struct FCharacterRouteAndDirection {
  GENERATED_BODY()

  /// <summary>
  /// キャラクターの方向
  /// </summary>
  CharacterDirection Direction;

  /// <summary>
  /// 進むことが可能な位置
  /// </summary>
  FVector Location;
};

/// <summary>
/// PlayerCharacterクラス
/// </summary>
UCLASS()
class APlayerCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
	APlayerCharacter();

  /// </summary>
  // Behavior Tree で使用する巡回目的地
  /// </summary>
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointTargets")
  TArray<ATargetPoint*> WayPointTargets;

private:
  /// </summary>
  // AnimInstanceへのポインタ
  /// </summary>
  class UAnimManager* AnimInstance;

  /// </summary>
  // キャラクターの状態
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
  CharacterStatus StatusType;

  /// </summary>
  // キャラクターの方向
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DirectionType", meta = (AllowPrivateAccess = "true"))
  CharacterDirection DirectionType;

  /// </summary>
  // 前回のキャラクターの方向
  /// </summary>
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DirectionType", meta = (AllowPrivateAccess = "true"))
  CharacterDirection PreDirectionType;

  /// <summary>
  /// 最初のターンであるフラグ
  /// </summary>
  bool bFirstTurn;

  /// <summary>
  /// ゴールしたかのフラグ
  /// </summary>
  bool bGoal;

protected:
  /// </summary>
  // キャラクターのCameraRShoulderLocation
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UArrowComponent* CameraRShoulderLocation;

  /// </summary>
  // キャラクターのArrowコンポーネント
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UArrowComponent* CameraOriginLocation;

  /// </summary>
  // キャラクターのCameraコンポーネント
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UCameraComponent* CameraComp;

  /// </summary>
  // キャラクターのSecondCameraRShoulderLocation
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UArrowComponent* SecondCameraRShoulderLocation;

  /// </summary>
  // キャラクターのSecondArrowコンポーネント
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UArrowComponent* SecondCameraOriginLocation;

  /// </summary>
  // キャラクターのSecondCameraコンポーネント
  /// </summary>
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  class UCameraComponent* SecondCameraComp;

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
  /// SetupPlayerInputComponent関数の宣言
  /// </summary>
  /// <param = "PlayerInputComponent">プレイヤーの入力コンポーネント</param>
  /// <returns>なし</returns>
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  /// <summary>
  /// SwitchAnimation関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SwitchAnimation();

  /// <summary>
  /// SetCharacterStatus関数の宣言
  /// </summary>
  /// <param = "Status">キャラクターの状態</param>
  /// <returns>なし</returns>
  void SetCharacterStatus(CharacterStatus Status);

  /// <summary>
  /// GetCharacterStatus関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターの状態</returns>
  CharacterStatus GetCharacterStatus();

  /// <summary>
  /// GetCharacterCameraComponent関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターのCameraComponent</returns>
  UCameraComponent* GetCharacterCameraComponent();

  /// <summary>
  /// GetCharacterSecondCameraComponent関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターのSecondCameraComponent</returns>
  UCameraComponent* GetCharacterSecondCameraComponent();

  /// <summary>
  /// SetCharacterCameraComponent関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターのCameraComponent</returns>
  void SetCharacterCameraComponent(UCameraComponent* CharacterCameraComponent);

  /// <summary>
  /// SetCharacterSecondCameraComponent関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターのSecondCameraComponent</returns>
  void SetCharacterSecondCameraComponent(UCameraComponent* CharacterSecondCameraComponent);

  /// <summary>
  /// SetCharacterDirection関数の宣言
  /// </summary>
  /// <param = "Direction">キャラクターの方向</param>
  /// <returns>なし</returns>
  void SetCharacterDirection(CharacterDirection Direction);

  /// <summary>
  /// GetCharacterDirection関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターの方向</returns>
  CharacterDirection GetCharacterDirection();

  /// <summary>
  /// SetPreCharacterDirection関数の宣言
  /// </summary>
  /// <param = "Direction">前回のキャラクターの方向</param>
  /// <returns>なし</returns>
  void SetPreCharacterDirection(CharacterDirection Direction);

  /// <summary>
  /// GetPreCharacterDirection関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>前回のキャラクターの方向</returns>
  CharacterDirection GetPreCharacterDirection();

  /// <summary>
  /// SetFirstTurn関数の宣言
  /// </summary>
  /// <param = "FirstTurn">最初のターンであるフラグ</param>
  /// <returns>なし</returns>
  void SetFirstTurn(bool FirstTurn);

  /// <summary>
  /// GetFirstTurn関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最初のターンであるフラグ</returns>
  bool GetFirstTurn();

  /// <summary>
  /// SetGoal関数の宣言
  /// </summary>
  /// <param = "Goaled">ゴールしたフラグ</param>
  /// <returns>なし</returns>
  void SetGoal(bool Goaled);

  /// <summary>
  /// IsGoal関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゴールしたフラグ</returns>
  bool IsGoal();
};
