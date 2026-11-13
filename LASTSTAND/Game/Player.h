#pragma once

class Bullet;
class Aim;
class GameCamera;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	//ステート処理
	void ManageState();
	//アニメーションの管理
	void PlayAnimation();
	// 射撃処理
	void Shoot();
	// ダメージ処理
	void TakeDamage(int damage);
	// 現在のHPを取得
	int GetHP() const
	{
		return m_hp;
	}
	// ゲームオーバー状態を取得
	bool IsGameOver() const
	{
		return m_isGameOver;
	}
	// 敵との接触判定
	void CheckEnemyCollision();
	// 弾数を回復
	void RecoverAmmo(int amount);
	bool Start() override;
	// エイム状態を取得
	bool IsAiming() const
	{
		return m_isAiming;
	}
	// リロード処理
	void Reload();
	// リロード状態の更新
	void UpdateReload();


	//メンバ変数
	ModelRender m_modelRender;
	FontRender m_ammoFontRender;
	FontRender m_reloadFontRender;
	// HPバー表示
	SpriteRender m_hpBarBackRender;
	SpriteRender m_hpBarRender;
	Vector3 position;
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Vector3 moveSpeed;
	Quaternion rotation;
	int playerState = 0;
	float m_shootCooldown = 0.0f;
	// リロード管理
	bool m_isReloading = false;       // リロード中か
	float m_reloadTimer = 0.0f;       // リロード経過時間
	float m_reloadTime = 2.0f;        // リロードにかかる時間
	int m_ammo = 30;                 // 現在の弾数
	int m_maxAmmo = 30;              // 最大弾数
	int m_ammoRecovery = 10;         // 回復する弾数
	int m_hp = 100;                  // プレイヤーのHP
	int m_maxHp = 100;
	bool m_isGameOver = false;       // ゲームオーバー状態
	float m_invincibleTimer = 0.0f;  // ダメージを受けた後の無敵時間
	static const int BULLET_POOL_SIZE = 30; // プレイヤー弾のプール
	Bullet* m_bulletPool[BULLET_POOL_SIZE] = {};
	bool m_isAiming = false;  // エイム状態
	Aim* m_aim = nullptr;    // 照準
	GameCamera* m_gameCamera = nullptr;
};

