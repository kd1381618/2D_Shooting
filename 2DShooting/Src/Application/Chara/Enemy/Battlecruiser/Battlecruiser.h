#pragma once
#include "../../CharaBase/CharaBase.h"

class C_GameScene;

class C_Battlecruiser : public C_CharaBase
{
public:
    C_Battlecruiser();
    ~C_Battlecruiser() {}

    void Init() override;
    void Action()override;      // 攻撃行動
    void Update() override;
    void PlayerBulletHit();
    void BossBulletHit();
    void Draw() override;
    
    void ShotConverge();
    void ShotSplit();
    void ShotLockSplit();
    void ShotMine();
    void ShotSpiralCross();
    void ShotConvergeBurst();
    void ShotRotateRing();
    std::vector<Bullet> Bullets;
    bool IsDead() const { return !m_aliveFlg; }
    bool GetDestructionFlg() { return destructionFlg; }
    void SetHpBarTex(KdTexture* tex) { hpbarTex = tex; }
    void SetHpFrameTex(KdTexture* tex) { hpframeTex = tex; }
    int Getphase() { return m_phase; }
    void Setphase(int phase);
private:

    C_GameScene* m_gameScene = nullptr;
   
    int m_phase;        
    int m_timer;        // 行動タイマー
    int m_hpMax;        // 最大HP
    KdTexture* hpbarTex;
    KdTexture* hpframeTex;
    Math::Rectangle hpbarrect;
    Math::Rectangle hpframerect;
    Math::Matrix hpbarmat;
    Math::Matrix hpframemat;
    Math::Matrix hpframetrans;
    Math::Matrix hpbarscale;
    Math::Matrix hpframescale;
    Math::Matrix hpbartrans;
    int m_prevPhase;
    int m_phaseDelay;   // フェーズ移行後の猶予タイマー
};