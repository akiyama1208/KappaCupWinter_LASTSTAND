#pragma once

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
	// 弾数を回復
	void RecoverAmmo(int amount);

	//メンバ変数
	ModelRender m_modelRender;
	FontRender m_ammoFontRender;
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
	int m_ammo = 30;       // 現在の弾数
	int m_maxAmmo = 30;    // 最大弾数
	int m_ammoRecovery = 10; // 回復する弾数
};

