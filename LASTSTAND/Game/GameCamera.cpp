#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include <Windows.h>
#include "system/system.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
	while (ShowCursor(TRUE) < 0)
	{
	}
}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	// カーソルを確実に非表示にする
	while (ShowCursor(FALSE) >= 0)
	{
	}

	return true;
}

void GameCamera::Update()
{
	if (!m_isCameraActive)
	{
		return;
	}

	// ゲームオーバー・クリア中はカメラ操作しない
	if (m_player->IsGameOver())
	{
		return;
	}

	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->position;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 100.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	// マウスの現在位置を取得
	// ゲームウィンドウの中央座標を取得
	RECT rect;
	GetClientRect(g_hWnd, &rect);

	POINT centerPos;
	centerPos.x = (rect.right - rect.left) / 2;
	centerPos.y = (rect.bottom - rect.top) / 2;

	// クライアント座標から画面座標に変換
	ClientToScreen(g_hWnd, &centerPos);

	// マウスの現在位置を取得
	POINT currentMousePos;
	GetCursorPos(&currentMousePos);

	// 中央からの移動量を計算
	float mouseDeltaX =
		static_cast<float>(currentMousePos.x - centerPos.x);

	float mouseDeltaY =
		static_cast<float>(currentMousePos.y - centerPos.y);

	// マウス移動量をカメラ回転量に変換
	float x = mouseDeltaX * 0.05f;
	float y = -mouseDeltaY * 0.05f;

	// カーソルを中央に戻す
	SetCursorPos(centerPos.x, centerPos.y);
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.35f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	// カメラの上下角度制限
	if (m_player->IsAiming())
	{
		// エイム中は見下ろしすぎないようにする
		if (toPosDir.y < -0.2f || toPosDir.y > 0.5f)
		{
			m_toCameraPos = toCameraPosOld;
		}
	}
	else
	{
		// 通常時の角度制限
		if (toPosDir.y < -0.2f || toPosDir.y > 0.9f)
		{
			m_toCameraPos = toCameraPosOld;
		}
	}

	// カメラ位置を計算する
	Vector3 cameraOffset = m_toCameraPos;

	// エイム中は肩越し視点にする
	if (m_player->IsAiming())
	{
		// カメラの高さを抑える
		cameraOffset.y *= 0.1f;

		// カメラまでの距離を調整
		cameraOffset.Normalize();
		cameraOffset *= 230.0f;

		// プレイヤーの右肩側にカメラを移動
		Vector3 cameraRight;
		cameraRight.Cross(m_toCameraPos, Vector3::AxisY);
		cameraRight.Normalize();

		// 注視点を右にずらす
		target += cameraRight * 120.0f;
	}

	// 実際のカメラ位置を計算する
	Vector3 pos = target + cameraOffset;

	// 実際のカメラ位置と注視点を保存
	m_cameraPosition = pos;
	m_cameraTarget = target;

	// メインカメラに注視点と視点を設定する
	g_camera3D->SetTarget(m_cameraTarget);
	g_camera3D->SetPosition(m_cameraPosition);

	// カメラの更新
	g_camera3D->Update();
}