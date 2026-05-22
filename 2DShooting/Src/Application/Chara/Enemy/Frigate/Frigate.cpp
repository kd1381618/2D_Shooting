#include "Frigate.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Chara/Player/Player.h"
#include"../../../UI/Score/Score.h"
#include"../../../Item/Medkit.h"

C_Frigate::C_Frigate()
{
    m_gameScene = (C_GameScene*)SCENEMANAGER.GetCurrentState();
}

C_Frigate::~C_Frigate()
{
}

void C_Frigate::Init()
{

    m_hpMax = 10;
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
    m_pos = { x,y };
}

void C_Frigate::Update()
{
    C_Player* player = m_gameScene->GetPlayer();
	// 弾更新
    Action();
    for (auto& b : frigatebullet)
    {
        if (!b.Flg) continue;
        b.timer++;
     
       
        if (b.type == Bullet::BulletType::FrigateBrake)
        {
            b.anim += 0.2f;
            if (b.anim > 10.0)b.anim = 0;
            b.rect = {32* (int)b.anim,0,32,32 };
            if (b.pos.x < -700 || b.pos.x>700 || b.pos.y < -360 || b.pos.y>400)b.Flg = false;
            if (b.timer < 60)        b.pos += b.move;
            else if (b.timer < 100)   b.pos += b.move * 0.3f;
            else                     b.pos += b.move * 0;

            if (b.timer > 300) {
                b.scale -= 0.05f;     
                if (b.scale<= 0.0f)
                {
                    b.Flg = false;
                }
            }
        }
    }
    frigatebullet.erase(
        std::remove_if(frigatebullet.begin(), frigatebullet.end(),
            [](const Bullet& b) { return !b.Flg; }),
        frigatebullet.end()
    );
    for (auto& b : frigatebullet)
    {
        b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
        b.rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
        b.scalemat = Math::Matrix::CreateScale(b.scale, b.scale, 1);
        b.mat = b.scalemat * b.rotatemat * b.transmat;
    }
    if (!m_aliveFlg)
    {
        // 破壊アニメ
        if (destructionFlg)
        {
            destructionAnim += 0.2f;
            m_destructionrect = { 0,64 * (int)destructionAnim, 64, 64 };

            if (destructionAnim > 9.0f)
            {
                destructionFlg = false;
                destructionAnim = 0;
            }
        }
        return;
    }

    //移動
    m_pos += m_move;
    if (m_pos.x < -640 - 64)
    {
        m_aliveFlg = false;
        return;
    }

    //武器アニメ
    Weaponanim += 0.2f;
    if (Weaponanim > 6.0f) Weaponanim = 0;
    m_rect = { 0, 64 * (int)Engineanim,64, 64 };

    Engineanim += 0.2f;
    if (Engineanim > 12.0f)Engineanim = 0;
    m_enginerect = { 0, 64 * (int)Engineanim, 64, 64 };


    float x = player->GetPos().x - m_pos.x;
    float y = player->GetPos().y - m_pos.y;
    float deg = DirectX::XMConvertToDegrees(atan2(y, x));
    m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(deg));
    m_mat = m_scalemat * m_rotatemat * m_transmat;

}

void C_Frigate::FrigateBulletHit()
{
    C_Player* player = m_gameScene->GetPlayer();

    for (auto& b : frigatebullet)
    {
        if (!b.Flg) continue;

        float dx = b.pos.x - player->GetPos().x;
        float dy = b.pos.y - player->GetPos().y;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist < player->GetHitRadius()+5)
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

void C_Frigate::PlayerBulletHit()
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
                   // respawnTimer = rand() % 180 + 120;
                    score->Add(1000);
                    player->Exp(10);
                }

                break;
            }
            break;
        case PlayerType::spacegun:
            if (dist < 32+6*player->GetBulletSize())
            {
                if (b.lasthitEnemy == this)continue;

                b.lasthitEnemy = this;
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
                    score->Add(1000);
                    player->Exp(10);
                }

                break;
            }
            break;
        }
    }
}

void C_Frigate::Action()
{
    if (!m_aliveFlg) return;

    m_shotTimer++;

    if (m_shotTimer > 60)
    {
        m_shotTimer = 0;

        C_Player* player = m_gameScene->GetPlayer();
        if (!player) return;

        Math::Vector2 dir = player->GetPos() - m_pos;
        dir.Normalize();

        Bullet b;
        b.type = Bullet::BulletType::FrigateBrake;
        b.pos = m_pos;
        b.move = dir * 8.0f;
        b.timer = 0;
        b.scale = 2;
        b.Flg = true;
        b.anim = 0;   

        frigatebullet.push_back(b);
    }
}

void C_Frigate::Draw()
{
    for (auto& b : frigatebullet)
    {
        b.color = { 1,1,0,1 };
        SHADER.m_spriteShader.SetMatrix(b.mat);
        SHADER.m_spriteShader.DrawTex_Color(m_bulletTex, b.rect,b.color);
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