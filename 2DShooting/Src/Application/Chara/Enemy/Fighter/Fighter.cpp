#include "Fighter.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../Item/Medkit.h"
#include"../../../UI/Score/Score.h"

C_Fighter::C_Fighter()
{
    m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
}

void C_Fighter::Init()
{
    m_hpMax = 5;
    m_hp = m_hpMax;

   
    m_aliveFlg = true;

  
    destructionFlg = false;

   
    // m_pos = { 640 + 64, float(rand() % 656 - 328) };

    m_move = { -3, 0 };

    Weaponanim = 0;
    Shieldanim = 0;
    destructionAnim = 0;
    Engineanim = 0;

    m_rect = { 0,0,64,64 };
    m_Shieldrect = { 0,0,64,64 };
    m_destructionrect = { 0,0,64,64 };
    m_enginerect = { 0,0,64,64 };

    //respawnTimer = 0;

    m_radius = 64.0f;
    m_scalemat = Math::Matrix::CreateScale(2, 2, 1);
    const float SCREEN_TOP = 360.0f;
    const float SCREEN_BOTTOM = -360.0f;
    const float UI_HEIGHT = 65.0f;

    float minY = SCREEN_BOTTOM + UI_HEIGHT + 64;
    float maxY = SCREEN_TOP - 64;

    float y = minY + (rand() % (int)(maxY - minY));


    float x = 640.0f + 64;
    m_pos = { x,y  };
}

void C_Fighter::Action()
{
    if (!m_aliveFlg) return;
    if (destructionFlg) return;
    C_Player* player = m_gameScene->GetPlayer();
    if (!player->GetAliveFlg()) return;
    if (shotwait > 0)
    {
        shotwait--;
    }
    else
    {
    
        float x = player->GetPos().x - m_pos.x;
        float y = player->GetPos().y - m_pos.y;
        float baseDeg = DirectX::XMConvertToDegrees(atan2(y, x));


        for (int i = 0; i < way; i++)
        {
            float deg = baseDeg + (i - way / 2) * interval;

            Bullet b;
            b.pos = m_pos;
            b.deg = deg;
            b.speed = 5.0f;

            // 移動ベクトル
            float rad = DirectX::XMConvertToRadians(deg);
            b.move.x = cosf(rad) * b.speed;
            b.move.y = sinf(rad) * b.speed;

            b.Flg = true;
            b.anim = 0;
            m_bullet.push_back(b);
        }
        shotwait = rand() % 90 + 60;
    }
}

void C_Fighter::Update()
{
    C_Player* player = m_gameScene->GetPlayer();
    Action();
    for (auto& b : m_bullet)
    {
        if (!b.Flg) continue;

        b.pos += b.move;
        b.anim += 0.2f;
        if (b.anim > 8.0)b.anim = 0;
        b.rect = { 0,9 * (int)b.anim,12,9 };
        if (b.pos.x < -700 || b.pos.x>700 || b.pos.y < -360 || b.pos.y>400)b.Flg = false;
    }

    m_bullet.erase(
        std::remove_if(m_bullet.begin(), m_bullet.end(),
            [](Bullet& b) { return !b.Flg; }),
        m_bullet.end()
    );
    for (auto& b : m_bullet)
    {
        b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
        b.rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(b.deg));
        b.scalemat = Math::Matrix::CreateScale(2, 2, 1);
        b.mat = b.scalemat * b.rotatemat * b.transmat;
    }
 
    if (!m_aliveFlg)
    {
        // 破壊アニメ
        if (destructionFlg)
        {
            destructionAnim += 0.2f;
            m_destructionrect = { 0,64 * (int)destructionAnim, 64, 64 };

            if (destructionAnim > 8.0f)
            {
                destructionFlg = false;
                destructionAnim = 0;
            }
        }
        return;
    }
    if (!m_aliveFlg) return;

    m_pos += m_move;
    if (m_pos.x < -640 - 64 && m_aliveFlg)
    {
        m_aliveFlg = false;
        //respawnTimer = rand() % 180 + 60;
        return;
    }
  

    // 武器アニメ
    Weaponanim += 0.2f;
    if (Weaponanim > 6.0f) Weaponanim = 0;
    m_rect = { 0, 64 * (int)Weaponanim,64, 64 };

    Engineanim += 0.2f;
    if (Engineanim > 10.0f)Engineanim = 0;
    m_enginerect = { 0, 64*(int)Engineanim, 64, 64};

    float x = player->GetPos().x - m_pos.x;
    float y = player->GetPos().y - m_pos.y;
    float deg = DirectX::XMConvertToDegrees(atan2(y, x));
    m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(deg));
    m_mat = m_scalemat * m_rotatemat*m_transmat;

}

void C_Fighter::FighterBulletHit()
{
    C_Player* player = m_gameScene->GetPlayer();

    for (auto& b : m_bullet)
    {
        if (!b.Flg) continue;

        float dx = b.pos.x - player->GetPos().x;
        float dy = b.pos.y - player->GetPos().y;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist < player->GetHitRadius())
        {
            if (player->GetShieldTime() <= 0)
            {
                b.Flg = false;
                player->Damage(1);
                player->SetShieldTime(180);
                break;
            }
        }
    }
}

void C_Fighter::PlayerBulletHit()
{
    if (!m_aliveFlg) return;

    C_Player* player = m_gameScene->GetPlayer();
    C_Score* score = m_gameScene->GetScore();
    auto& bullets = player->GetBullets();

    for (auto& b : bullets)
    {
        if (!b.Flg) continue;

        float dx = b.pos.x - m_pos.x;
        float dy = b.pos.y - m_pos.y;
        float dist = sqrtf(dx * dx + dy * dy);

       

        switch (player->GetType())
        {
        case PlayerType::cannon:
            if (dist < 33)
            {
                b.Flg = false;
                m_gameScene->AddExplosion(b.pos);
                m_hp--;

                if (m_hp <= 0)
                {
                    m_hp = 0;
                    m_aliveFlg = false;
                    destructionFlg = true;
                    destructionAnim = 0;
                    int r = rand() % 100;
                    if (r < 10)
                    {
                        m_gameScene->SpawnMedkit(m_pos);
                    }
                    //respawnTimer = rand() % 180 + 120;
                    score->Add(500);
                    player->Exp(5);
                }

                break;
            }
            break;
        case PlayerType::spacegun:
            if (dist < 32 + 6 * player->GetBulletSize())
            {
                if (b.lasthitEnemy == this)continue;
                b.lasthitEnemy = this;
                //b.Flg = false;
                m_gameScene->AddExplosion(b.pos);
                m_hp -= 2 + player->GetBulletSize();
                if (m_hp <= 0)
                {
                    m_hp = 0;
                    m_aliveFlg = false;
                    destructionFlg = true;
                    destructionAnim = 0;
                    int r = rand() % 100;
                    if (r < 10)
                    {
                        m_gameScene->SpawnMedkit(m_pos);
                    }
                    //respawnTimer = rand() % 180 + 120;
                    score->Add(500);
                    player->Exp(5);
                }

                break;
            }
            break;
        }
    }
}

void C_Fighter::Draw()
{
    for (auto& b : m_bullet)
    {
        if (!b.Flg) continue;

        SHADER.m_spriteShader.SetMatrix(b.mat);
        SHADER.m_spriteShader.DrawTex(m_bulletTex, b.rect);
    }
    if (destructionFlg)
    {
        SHADER.m_spriteShader.SetMatrix(m_mat);
        SHADER.m_spriteShader.DrawTex(m_DestructionTex, m_destructionrect);
        return;
    }
    if (!m_aliveFlg) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_EngineTex, m_enginerect);
   
}
