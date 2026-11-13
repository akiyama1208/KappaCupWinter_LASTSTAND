#pragma once

class Player;

// ゲーム中のカメラを制御する
class GameCamera : public IGameObject
{
public:
    GameCamera();
    ~GameCamera();

    bool Start();
    void Update();

    // 実際のカメラ位置を取得
    const Vector3& GetCameraPosition() const
    {
        return m_cameraPosition;
    }

    // カメラの注視点を取得
    const Vector3& GetCameraTarget() const
    {
        return m_cameraTarget;
    }

    // カメラの向きを取得
    Vector3 GetCameraDirection() const
    {
        Vector3 direction = m_cameraTarget - m_cameraPosition;
        direction.Normalize();
        return direction;
    }

    void SetCameraActive(bool isActive)
    {
        m_isCameraActive = isActive;
    }

    Player* m_player = nullptr;
    Vector3 m_toCameraPos;

private:
    Vector3 m_cameraPosition;
    Vector3 m_cameraTarget;

    bool m_isCameraActive = true;

    // マウスカメラ操作の有効・無効
    bool m_isMouseControlEnabled = true;

    // F1キーの前回状態
    bool m_wasF1Pressed = false;
};