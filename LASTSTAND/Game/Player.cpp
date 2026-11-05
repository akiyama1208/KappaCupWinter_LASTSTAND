#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

Player::Player()
{
	//アニメーションクリップをロードする
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//ユニティちゃんのモデルを読み込む
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
	//キャラコンを初期化する
	characterController.Init(40.0f, 75.0f, position);
	// 弾数表示の位置
	m_ammoFontRender.SetPosition(Vector3(400.0f, -300.0f, 0.0f));
	// HP表示の位置
	m_hpFontRender.SetPosition(Vector3(-400.0f, 300.0f, 0.0f));
}

Player::~Player()
{

}

void Player::Update()
{
	// ゲームオーバーならプレイヤーの処理を停止
	if (m_isGameOver)
	{
		return;
	}

	//移動処理
	Move();
	// 無敵時間を更新
	if (m_invincibleTimer > 0.0f)
	{
		m_invincibleTimer -= 1.0f / 60.0f;
	}

	// 敵との接触判定
	CheckEnemyCollision();
	//回転処理
	Rotation();
	// 射撃間隔を更新
	if (m_shootCooldown > 0.0f)
	{
		m_shootCooldown -= 1.0f / 60.0f;

		if (m_shootCooldown < 0.0f)
		{
			m_shootCooldown = 0.0f;
		}
	}

	// 射撃処理
	Shoot();
	//ステート管理
	ManageState();
	//アニメーションの再生
	PlayAnimation();
	// 弾数表示を更新
	wchar_t ammoText[64];
	swprintf_s(
		ammoText,
		64,
		L"AMMO: %d / %d",
		m_ammo,
		m_maxAmmo
	);
	m_ammoFontRender.SetText(ammoText);

	// HP表示を更新
	wchar_t hpText[64];
	swprintf_s(
		hpText,
		64,
		L"HP: %d / %d",
		m_hp,
		m_maxHp
	);
	m_hpFontRender.SetText(hpText);

	//絵描きさんの更新処理
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	// 移動速度
	float speed = 400.0f;

	// ダッシュ
	if (g_pad[0]->IsPress(enButtonB))
	{
		speed = 800.0f;
	}

	// スティック入力を移動速度に変換
	right *= stickL.x * speed;
	forward *= stickL.y * speed;

	moveSpeed.x += right.x + forward.x;
	moveSpeed.z += right.z + forward.z;

	//地面に付いていたら
	if (characterController.IsOnGround())
	{
		//重力を無くす
		moveSpeed.y = 0.0f;
		//Aボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる
			moveSpeed.y = 350.0f;
		}
	}
	//地面に付いていなかったら
	else
	{
		//重力を発生させる
		moveSpeed.y -= 4.5f;
	}

	//キャラクターコントローラーを使って座標を移動させる
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える
	m_modelRender.SetPosition(position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//絵描きさんに回転を教える
		m_modelRender.SetRotation(rotation);
	}
}

void Player::ManageState()
{
	//地面に付いていなかったら
	if (characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする
		playerState = 1;
		//ここでManageState関数の処理を終わらせる
		return;
	}

	//地面に付いていたら
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする
		playerState = 2;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)
	else
	{
		//ステートを0(待機)にする
		playerState = 0;
	}
}

void Player::PlayAnimation()
{
	switch (playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Shoot()
{
	// Xボタンを押している間、射撃する
	if (g_pad[0]->IsPress(enButtonX) == false)
	{
		return;
	}

	// 弾数が0なら撃てない
	if (m_ammo <= 0)
	{
		return;
	}

	// 射撃間隔中は発射しない
	if (m_shootCooldown > 0.0f)
	{
		return;
	}

	// 次の射撃まで0.2秒待つ
	m_shootCooldown = 0.2f;

	// 弾数を1発消費
	m_ammo--;

	// プレイヤーが向いている方向を取得
	Vector3 direction = Vector3::AxisZ;
	rotation.Apply(direction);

	// 水平方向に発射する
	direction.y = 0.0f;
	direction.Normalize();

	// 弾の発射位置を設定
	Vector3 bulletPosition = position;
	bulletPosition.y += 60.0f;
	bulletPosition += direction * 100.0f;

	// 弾を生成
	Bullet* bullet = NewGO<Bullet>(0, "bullet");

	// 弾の位置と方向を設定
	bullet->Init(bulletPosition, direction);
}

void Player::RecoverAmmo(int amount)
{
	m_ammo += amount;

	// 最大弾数を超えないようにする
	if (m_ammo > m_maxAmmo)
	{
		m_ammo = m_maxAmmo;
	}
}

void Player::CheckEnemyCollision()
{
	Enemy* enemy = FindGO<Enemy>("enemy");

	if (enemy == nullptr)
	{
		return;
	}

	Vector3 distance = enemy->GetPosition() - position;
	distance.y = 0.0f;

	if (distance.Length() < 300.0f)
	{
		TakeDamage(25);
	}
}

void Player::TakeDamage(int damage)
{
	// ゲームオーバーならダメージを受けない
	if (m_isGameOver)
	{
		return;
	}

	// 無敵時間中ならダメージを受けない
	if (m_invincibleTimer > 0.0f)
	{
		return;
	}

	// HPを減らす
	m_hp -= damage;

	// HPが0以下になったら
	if (m_hp <= 0)
	{
		m_hp = 0;
		m_isGameOver = true;

		OutputDebugStringA("GAME OVER!\n");
		return;
	}

	// 1秒間無敵にする
	m_invincibleTimer = 1.0f;

	char text[100];
	sprintf_s(text, "Player HP: %d\n", m_hp);
	OutputDebugStringA(text);
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	// 弾数を描画
	m_ammoFontRender.Draw(rc);

	// HPを描画
	m_hpFontRender.Draw(rc);
}