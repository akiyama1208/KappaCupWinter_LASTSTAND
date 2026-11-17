#include "Enemy.h"

class Enemy3 : public Enemy
{
public:
    bool Start() override;
    void Update() override;

private:
    void Move();

    // 突進関連
    float m_chargeTimer = 0.0f;
    float m_chargeInterval = 3.0f;
    float m_chargeDuration = 1.5f;
    float m_chargeElapsed = 0.0f;

    bool m_isCharging = false;
    bool m_hasHitPlayer = false;       // 突進中にダメージを与えたか

    Vector3 m_chargeDirection;
};