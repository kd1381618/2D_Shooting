#pragma once
class C_Scout;
class C_Fighter;
class C_Frigate;

class C_EnemySpawner
{
public:
    C_EnemySpawner();
    ~C_EnemySpawner() {}

    void Init();
    void Update();

    // Scout 用
    void SetScoutBaseTex(KdTexture* tex) { m_scoutBase = tex; }
    void SetScoutEngineTex(KdTexture* tex) { m_scoutEngine = tex; }
    void SetScoutBulletTex(KdTexture* tex) { m_scoutBullet = tex; }
    void SetScoutDestructionTex(KdTexture* tex) { m_scoutDestruction = tex; }
    void SetScoutShieldTex(KdTexture* tex) { m_scoutShield = tex; }

    // Fighter 用
    void SetFighterBaseTex(KdTexture* tex) { m_fighterBase = tex; }
    void SetFighterEngineTex(KdTexture* tex) { m_fighterEngine = tex; }
    void SetFighterBulletTex(KdTexture* tex) { m_fighterBullet = tex; }
    void SetFighterDestructionTex(KdTexture* tex) { m_fighterDestruction = tex; }
    void SetFighterShieldTex(KdTexture* tex) { m_fighterShield = tex; }

    void SetFrigateBaseTex(KdTexture* tex) { m_frigateBase = tex; }
    void SetFrigateEngineTex(KdTexture* tex) { m_frigateEngine = tex; }
    void SetFrigateBulletTex(KdTexture* tex) { m_frigateBullet = tex; }
    void SetFrigateDestructionTex(KdTexture* tex) { m_frigateDestruction = tex; }
    void SetFrigateShieldTex(KdTexture* tex) { m_frigateShield = tex; }

    void SetScoutList(std::vector<C_Scout*>* list) { m_scoutList = list; }
    void SetFighterList(std::vector<C_Fighter*>* list) { m_fighterList = list; }
    void SetFrigateList(std::vector<C_Frigate*>* list) { m_frigateList = list; }
    void StopSpawn(bool stop) { m_stopSpawn = stop; ; }
private:
    float m_time = 0.0f;
    float m_spawnTimer = 0.0f;

    // 敵リスト
    std::vector<C_Scout*>* m_scoutList = nullptr;
    std::vector<C_Fighter*>* m_fighterList = nullptr;
    std::vector<C_Frigate*>* m_frigateList = nullptr;
    // Scout テクスチャ
    KdTexture* m_scoutBase = nullptr;
    KdTexture* m_scoutEngine = nullptr;
    KdTexture* m_scoutBullet = nullptr;
    KdTexture* m_scoutDestruction = nullptr;
    KdTexture* m_scoutShield = nullptr;

    // Fighter テクスチャ
    KdTexture* m_fighterBase = nullptr;
    KdTexture* m_fighterEngine = nullptr;
    KdTexture* m_fighterBullet = nullptr;
    KdTexture* m_fighterDestruction = nullptr;
    KdTexture* m_fighterShield = nullptr;

    KdTexture* m_frigateBase = nullptr;
    KdTexture* m_frigateEngine = nullptr;
    KdTexture* m_frigateBullet = nullptr;
    KdTexture* m_frigateDestruction = nullptr;
    KdTexture* m_frigateShield = nullptr;
    float m_frame = 0.0f;
    float m_timeFrame = 0.0f;

    int m_maxScout = 5;
    int m_maxFighter = 3;
    int m_maxFrigate = 3;

    bool m_stopSpawn = false;

    void SpawnEnemyByTime();
    void SpawnScout();
    void SpawnFighter();
    void SpawnFrigate();
    Math::Vector2 CalcSpawnPos(float radius);
};