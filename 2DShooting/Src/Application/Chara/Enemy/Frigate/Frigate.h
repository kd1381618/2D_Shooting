#pragma once
#include "../../CharaBase/CharaBase.h"

class C_GameScene;

class C_Frigate : public C_CharaBase
{
public:
    C_Frigate();
    ~C_Frigate()override;

    void Init() override;
    void Action()override;
    void Update() override;
    void FrigateBulletHit();
    void PlayerBulletHit();
    void Draw() override;
    bool C_Frigate::HasBullet() const {
        return !frigatebullet.empty();
    }
    bool GetDestructionFlg() { return destructionFlg; }
private:
    C_GameScene* m_gameScene = nullptr;
    std::vector<Bullet> frigatebullet;
    int m_shotTimer = 0;  
};