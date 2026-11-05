#pragma once
#include "Enemy.h"

class Enemy2 : public Enemy
{
public:
    bool Start() override;
    void Update() override;

private:
    void Move();
    void Attack();
};
