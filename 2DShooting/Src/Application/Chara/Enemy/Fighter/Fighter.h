#pragma once
#include "../../CharaBase/CharaBase.h"
class C_GameScene;

class C_Fighter : public C_CharaBase
{
public:
    C_Fighter();
    ~C_Fighter(){}
    void Init() override;
    void Action() override;
    void Update() override;
    void FighterBulletHit();
    void PlayerBulletHit();
    void Draw() override;
    bool GetDestructionFlg() { return destructionFlg; }
    bool C_Fighter::HasBullet() const {
        return !m_bullet.empty();
    }

private:
    C_GameScene* m_gameScene = nullptr;
    float m_speed = -4.0f;
    float m_radius = 32.0f;
    const int way = 5;
    const float interval = 10.0f;
    std::vector<Bullet> m_bullet;
    int respawnTimer;
    int shotwait = 0;
    int ShieldTime;
    int frame;
    bool destructionFlg;


};