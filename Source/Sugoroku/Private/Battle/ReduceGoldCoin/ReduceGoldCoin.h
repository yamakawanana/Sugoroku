#include "GameFramework/Actor.h"
#include "ReduceGoldCoin.generated.h"

/// <summary>
/// 名前空間ReduceGoldCoinNameSpace
/// </summary>
namespace ReduceGoldCoinNameSpace {
  /// <summary>
  /// 累積時間のリセット時間を定数ResetTimeに格納する
  /// </summary>
  static const float ResetTime = 0.4f;

  /// <summary>
  /// コイン上昇開始の時間差を定数CoinStartTimeに格納する
  /// </summary>
  static const float CoinStartTime = 0.3f;

  /// <summary>
  /// コインのスポーン位置のX位置調整の値を定数CoinSpawnXに格納する
  /// </summary>
  static const float CoinSpawnX = 12.0f;

  /// <summary>
  /// コインのスポーン位置のY位置調整の値を定数CoinSpawnYに格納する
  /// </summary>
  static const float CoinSpawnY = 0.0f;

  /// <summary>
  /// コインのスポーン位置のZ位置調整の値を定数CoinSpawnZに格納する
  /// </summary>
  static const float CoinSpawnZ = 80.0f;

}

/// <summary>
/// ReduceGoldCoinクラス
/// </summary>
UCLASS()
class AReduceGoldCoin : public AActor
{
  GENERATED_BODY()

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  AReduceGoldCoin();

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

