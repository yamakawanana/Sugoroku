#include "Battle/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Battle/AnimManager/AnimManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
APlayerCharacter::APlayerCharacter()
  : DirectionType(CharacterDirection::Front)
  , PreDirectionType(CharacterDirection::Front)
  , bFirstTurn(true)
  , bGoal(false)
{
  //WayPointTargetsを初期化する
  WayPointTargets.Empty();

  // Tickの実行を有効にする
  PrimaryActorTick.bCanEverTick = true;

  // Cameraコンポーネントをインスタンス化
  CameraRShoulderLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraRShoulderLocation"));
  CameraOriginLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraOriginLocation"));
  CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
  SecondCameraRShoulderLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("SecondCameraRShoulderLocation"));
  SecondCameraOriginLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("SecondCameraOriginLocation"));
  SecondCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("SecondCameraComp"));

  // Cameraコンポーネントをキャラクターのスケルタルメッシュにアタッチ
  CameraRShoulderLocation->SetupAttachment(GetMesh());
  CameraOriginLocation->SetupAttachment(GetMesh());
  CameraComp->SetupAttachment(GetMesh());
  SecondCameraRShoulderLocation->SetupAttachment(GetMesh());
  SecondCameraOriginLocation->SetupAttachment(GetMesh());
  SecondCameraComp->SetupAttachment(GetMesh());

}

/// <summary>
/// BeginPlay関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void APlayerCharacter::BeginPlay()
{
  Super::BeginPlay();

  AnimInstance = Cast<UAnimManager>(GetMesh()->GetAnimInstance());

}

/// <summary>
/// Tick関数の定義
/// </summary>
/// <param = "float DeltaTime">前回フレーム更新からの経過時間</param>
/// <returns>なし</returns>
void APlayerCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

/// <summary>
/// SetupPlayerInputComponent関数の定義
/// </summary>
/// <param = "PlayerInputComponent">プレイヤーの入力コンポーネント</param>
/// <returns>なし</returns>
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/// <summary>
/// SwitchAnimation関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void APlayerCharacter::SwitchAnimation() {
  if (AnimInstance)
  {
    if (StatusType == CharacterStatus::Happy)
    {
      // キャラクターを勝利の状態にする
      AnimInstance->SetVictory(true);
      StatusType = CharacterStatus::Normal;
    }
    else if (StatusType == CharacterStatus::Regret)
    {
      // キャラクターを敗北の状態にする
      AnimInstance->SetDefeat(true);
      StatusType = CharacterStatus::Normal;
    }
    else if (StatusType == CharacterStatus::Normal)
    {
      // キャラクターの状態を元に戻す
      AnimInstance->SetVictory(false);
      AnimInstance->SetDefeat(false);
    }
  }
}

/// <summary>
/// SetCharacterStatus関数の定義
/// </summary>
/// <param = "Status">キャラクターの状態</param>
/// <returns>なし</returns>
void APlayerCharacter::SetCharacterStatus(CharacterStatus Status) {
  StatusType = Status;
}

/// <summary>
/// GetCharacterStatus関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターの状態</returns>
CharacterStatus APlayerCharacter::GetCharacterStatus() {
  return StatusType;
}

/// <summary>
/// GetCharacterCameraComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターのCameraComponent</returns>
UCameraComponent* APlayerCharacter::GetCharacterCameraComponent() {
  return CameraComp;
}

/// <summary>
/// GetCharacterSecondCameraComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターのCameraComponent</returns>
UCameraComponent* APlayerCharacter::GetCharacterSecondCameraComponent() {
  return SecondCameraComp;
}

/// <summary>
/// SetCharacterCameraComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターのCameraComponent</returns>
void APlayerCharacter::SetCharacterCameraComponent(UCameraComponent* CameraComponent) {
  CameraComp = CameraComponent;
}

/// <summary>
/// SetCharacterSecondCameraComponent関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターのSecondCameraComponent</returns>
void APlayerCharacter::SetCharacterSecondCameraComponent(UCameraComponent* SecondCameraComponent) {
  SecondCameraComp = SecondCameraComponent;
}

/// <summary>
/// SetCharacterDirection関数の定義
/// </summary>
/// <param = "Direction">キャラクターの方向</param>
/// <returns>なし</returns>
void APlayerCharacter::SetCharacterDirection(CharacterDirection Direction) {
  DirectionType = Direction;
}

/// <summary>
/// GetCharacterDirection関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターの方向</returns>
CharacterDirection APlayerCharacter::GetCharacterDirection() {
  return DirectionType;
}

/// <summary>
/// SetPreCharacterDirection関数の定義
/// </summary>
/// <param = "Direction">前回のキャラクターの方向</param>
/// <returns>なし</returns>
void APlayerCharacter::SetPreCharacterDirection(CharacterDirection Direction) {
  PreDirectionType = Direction;
}

/// <summary>
/// GetPreCharacterDirection関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>前回のキャラクターの方向</returns>
CharacterDirection APlayerCharacter::GetPreCharacterDirection() {
  return PreDirectionType;
}

/// <summary>
/// SetFirstTurn関数の宣言
/// </summary>
/// <param = "FirstTurn">最初のターンであるフラグ</param>
/// <returns>なし</returns>
void APlayerCharacter::SetFirstTurn(bool FirstTurn) {
  bFirstTurn = FirstTurn;
}

/// <summary>
/// GetFirstTurn関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>最初のターンであるフラグ</returns>
bool APlayerCharacter::GetFirstTurn() {
  return bFirstTurn;
}

/// <summary>
/// SetGoal関数の宣言
/// </summary>
/// <param = "Goaled">ゴールしたフラグ</param>
/// <returns>なし</returns>
void APlayerCharacter::SetGoal(bool Goaled) {
  bGoal = Goaled;
}

/// <summary>
/// IsGoal関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>ゴールしたフラグ</returns>
bool APlayerCharacter::IsGoal() {
  return bGoal;
}

