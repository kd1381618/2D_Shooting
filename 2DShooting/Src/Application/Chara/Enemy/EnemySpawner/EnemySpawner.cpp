#include "EnemySpawner.h"
#include"../Scout/Scout.h"
#include"../Fighter/Fighter.h"
#include"../Frigate/Frigate.h"

C_EnemySpawner::C_EnemySpawner()
{
    Init();
}

void C_EnemySpawner::Init()
{
     m_frame = 0;
     m_timeFrame = 0;
}

void C_EnemySpawner::Update()
{
    m_frame++;      // 1フレームごとに +1
    m_timeFrame++;  // 経過フレーム（秒数計算用）

    float elapsedSec = m_timeFrame / 60.0f;

    // 難易度カーブ付きスポーン間隔
    float spawnInterval = 120 - elapsedSec * 1.0f;  
    if (spawnInterval < 80) spawnInterval = 80;     

    // スポーン処理
    if (m_frame >= spawnInterval)
    {
        SpawnEnemyByTime();
        m_frame = 0;
    }
}

void C_EnemySpawner::SpawnEnemyByTime()
{
    if (m_stopSpawn) return;
    if (m_scoutList->size() >= m_maxScout &&
        m_fighterList->size() >= m_maxFighter&&
        m_frigateList->size()>=m_maxFrigate)
    {
        return;
    }
    if (m_frigateList->size() >= m_maxFrigate)
    {
        SpawnFighter();
        return;
    }
    // Fighter が上限なら Scout だけ出す
    if (m_fighterList->size() >= m_maxFighter)
    {
        SpawnScout();
        return;
    }
    // Scout が上限なら Fighter だけ出す
    if (m_scoutList->size() >= m_maxScout)
    {
        SpawnFighter();
        return;
    }

  
    // 経過秒数で敵の種類を変える
    float elapsedSec = m_timeFrame / 60.0f;

    if (elapsedSec < 20)
    {
        SpawnScout();
    }
    else if (elapsedSec < 40)
    {
        if (rand() % 100 < 70) SpawnScout();
        else SpawnFighter();
    }
    else if(elapsedSec<60)
    {
        int r = rand() % 100;
        if (r < 40) SpawnScout();
        else if (r < 80) SpawnFighter();
        else SpawnFrigate();
    }
    else
    {
        int r = rand() % 100;
        if (r < 20) SpawnScout();
        else if (r < 60) SpawnFighter();
        else SpawnFrigate();
    }
}

void C_EnemySpawner::SpawnScout()
{
    C_Scout* s = new C_Scout();


    s->SetBaseTex(m_scoutBase);
    s->SetEngineTex(m_scoutEngine);
    s->SetBulletTex(m_scoutBullet);
    s->SetDestructionTex(m_scoutDestruction);
    s->SetShieldTex(m_scoutShield);

    s->Init();
    s->SetPos(CalcSpawnPos(s->GetRadius()));
   
    m_scoutList->push_back(s);
}

void C_EnemySpawner::SpawnFighter()
{
    C_Fighter* f = new C_Fighter();

    f->SetBaseTex(m_fighterBase);
    f->SetEngineTex(m_fighterEngine);
    f->SetBulletTex(m_fighterBullet);
    f->SetDestructionTex(m_fighterDestruction);
    f->SetShieldTex(m_fighterShield);
    f->SetPos(CalcSpawnPos(f->GetRadius()));
    f->Init();  
  
    

    m_fighterList->push_back(f);
}

void C_EnemySpawner::SpawnFrigate()
{
    C_Frigate* e = new C_Frigate();

    e->SetBaseTex(m_frigateBase);
    e->SetEngineTex(m_frigateEngine);
    e->SetBulletTex(m_frigateBullet);
    e->SetDestructionTex(m_frigateDestruction);
    e->SetShieldTex(m_frigateShield);
    e->SetPos(CalcSpawnPos(e->GetRadius()));
    e->Init();

   

    m_frigateList->push_back(e);
}

Math::Vector2 C_EnemySpawner::CalcSpawnPos(float radius)
{
    const float SCREEN_TOP = 360.0f;
    const float SCREEN_BOTTOM = -360.0f;
    const float UI_HEIGHT = 65.0f;

    float minY = SCREEN_BOTTOM + UI_HEIGHT + radius;
    float maxY = SCREEN_TOP - radius;

    float y = minY + (rand() % (int)(maxY - minY));

   
    float x = 640.0f + radius;

    return { x, y };
}
