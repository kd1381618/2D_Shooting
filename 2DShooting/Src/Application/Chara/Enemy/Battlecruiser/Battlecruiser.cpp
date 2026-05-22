#include "Battlecruiser.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../Item/Medkit.h"
#include"../../BulletUpdate/BulletUpdate.h"
#include"../../../UI/Score/Score.h"

C_Battlecruiser::C_Battlecruiser()
{
    m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
}

void C_Battlecruiser::Init()
{
    m_aliveFlg = true;
    destructionFlg = false;

    //右端の外に出現
    m_pos = { 700.0f, 0.0f };
    m_phase = 0;
    m_timer = 0;
    m_hpMax = 300;
    m_rect = { 0,0,128,128 };
    hpframerect = { 0,0,38,15 };
    hpbarrect = { 0,0,32,5 };
    m_Shieldrect = { 0,0,128,128 };
    m_hp = m_hpMax;
    Weaponanim = 0;
    bulletAnim = 0;
    destructionAnim = 0;
    Engineanim = 0;
    Shieldanim = 0;
    m_scalemat = Math::Matrix::CreateScale(3, 3, 1);
    m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
    hpframescale = Math::Matrix::CreateScale(15, 5, 1);
    m_prevPhase = 1;
    m_phaseDelay = 240;
}

void C_Battlecruiser::Update()
{
    if (!m_aliveFlg)
    {
        // 破壊アニメ
        if (destructionFlg)
        {
            destructionAnim += 0.2f;
            m_destructionrect = { 128 * (int)destructionAnim,0, 128, 128 };

            if (destructionAnim > 14.0f)
            {
                destructionFlg = false;
                destructionAnim = 0;
            }
        }
        return;
    }

    m_timer++;

    //フェーズ0：右端から入場
    if (m_phase == 0)
    {
        m_pos.x -= 2.0f; 

        if (m_pos.x <= 450.0f) // 戦闘位置
        {
            m_phase = 1;
            m_timer = 0;
        }
    }
    Engineanim += 0.2f;
    if (Engineanim > 12.0f)Engineanim = 0;
    m_enginerect = { 128 * (int)Engineanim,0,  128, 128 };

    Shieldanim += 0.2f;
    if (Shieldanim > 16.0f)  Shieldanim = 0;
    m_Shieldrect = { 128 * (int)Shieldanim,0,128, 128 };
    //フェーズ1：戦闘
    if (m_phase != 0)
    {
        Action();
        float hpRate = (float)m_hp / (float)m_hpMax;

        if (hpRate > 0.66f)      m_phase = 1;
        else if (hpRate > 0.33f) m_phase = 2;
        else                     m_phase = 3;
        if (m_phase != m_prevPhase)
        {
            m_phaseDelay = 240;   
            m_prevPhase = m_phase;
        }
        // 武器アニメ
        Weaponanim += 0.2f;
        if (Weaponanim > 30.0f) Weaponanim = 0;
        m_rect = { 128 * (int)Weaponanim,0,128, 128 };
 
        std::vector<Bullet>newBullets;
        for (int i = 0; i < Bullets.size(); i++)
        {
            Bullet& b = Bullets[i];

            // アニメ更新
            b.anim += 0.2f;
            if (b.anim > 8.0f) b.anim = 0;
            b.rect = { 8 * (int)b.anim, 0, 8, 8 };

            // 弾の挙動更新
            UpdateBullet(b, newBullets);

        
            if (b.type != Bullet::RotateRing)
            {
                if (b.pos.x < -700 || b.pos.x > 700 || b.pos.y < -360 || b.pos.y > 400)b.Flg = false;
            }

            if (!b.Flg)
            {
                Bullets.erase(Bullets.begin() + i);
                i--; // インデックス調整
                continue;
            }
        }
        for (auto& nb : newBullets)
        {
            Bullets.push_back(nb);
        }
        for (auto& b : Bullets)
        {
            b.transmat = Math::Matrix::CreateTranslation(b.pos.x, b.pos.y, 0);
            b.rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
            b.scalemat = Math::Matrix::CreateScale(2, 2, 1);
            b.mat = b.scalemat * b.rotatemat * b.transmat;
        }
    }
    m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scalemat*m_rotatemat * m_transmat;
    hpframetrans = Math::Matrix::CreateTranslation(0, 320, 0);
    hpframemat = hpframescale * hpframetrans;
    hpbarscale = Math::Matrix::CreateScale((15.0f/300)*m_hp,5, 1);
    hpbartrans = Math::Matrix::CreateTranslation(0-(m_hpMax-m_hp)/1.325, 320+5, 0);
    hpbarmat = hpbarscale * hpbartrans;
}
void C_Battlecruiser::PlayerBulletHit()
{
    C_Score* score = m_gameScene->GetScore();
    if (!m_aliveFlg) return;

    C_Player* player = m_gameScene->GetPlayer();
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
            if (dist < 100)
            {
                b.Flg = false;
                m_gameScene->AddExplosion(b.pos);
                if (m_phase == 0)return;
                if (m_phaseDelay > 0)return;
                m_hp--;

                if (m_hp <= 0)
                {
                    m_hp = 0;
                    m_aliveFlg = false;
                    destructionFlg = true;
                    destructionAnim = 0;
                    score->Add(15000);
                    m_gameScene->SetclearFlg(true);
                }

                break;
            }
            break;
        case PlayerType::spacegun:
             if (dist < 100+6*player->GetBulletSize())
            {
                //b.Flg = false;
                 if (b.lasthitEnemy == this)continue;
                 b.lasthitEnemy = this;
                m_gameScene->AddExplosion(b.pos);
                if (m_phase == 0)return;
                if (m_phaseDelay > 0)return;
                m_hp -= 2 + player->GetBulletSize();

                if (m_hp <= 0)
                {
                    m_hp = 0;
                    m_aliveFlg = false;
                    destructionFlg = true;
                    destructionAnim = 0;
                    score->Add(15000);
                    m_gameScene->SetclearFlg(true);
                }

                break;
            }
            break;
        }
       
    }
}

void C_Battlecruiser::BossBulletHit()
{

    C_Player* player = m_gameScene->GetPlayer();

    for (auto& b : Bullets)
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

void C_Battlecruiser::Action()
{
   // if (m_timer % 60 == 0) ShotConverge();
    //if (m_timer % 120 == 0) ShotSplit();
    //if (m_timer % 180 == 0)ShotMine();
    //if (m_timer % 1 == 0)ShotSpiralCross();
    //if (m_timer % 60 == 0)ShotConvergeBurst();
     //if (m_timer % 60 == 0)ShotRotateRing();
    if (m_phaseDelay > 0)
    {
        m_phaseDelay--;
        return;  
    }
     switch (m_phase)
     {
     case 1:
         if (m_timer % 120 == 0) ShotConverge();
         if (m_timer % 60 == 0)ShotRotateRing();
         break;
     case 2:
         if (m_timer % 60 == 0)ShotConvergeBurst();
         if (m_timer % 120 == 0)ShotMine();
         break;
     case 3:
         if (m_timer % 1 == 0)ShotSpiralCross();
         if (m_timer % 120 == 0) ShotLockSplit();
         break;
     }
}

void C_Battlecruiser::Draw()
{
    for (auto& b : Bullets)
    {
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
    if (m_phase == 0 || m_phaseDelay > 0)
    {
        SHADER.m_spriteShader.SetMatrix(m_mat);
        SHADER.m_spriteShader.DrawTex(m_ShieldTex, m_Shieldrect);
    }

    SHADER.m_spriteShader.SetMatrix(hpframemat);
    SHADER.m_spriteShader.DrawTex(hpframeTex, hpframerect);
  
    SHADER.m_spriteShader.SetMatrix(hpbarmat);
    SHADER.m_spriteShader.DrawTex(hpbarTex, hpbarrect);
}

void C_Battlecruiser::ShotConverge()
{
    C_Player* player = m_gameScene->GetPlayer();
    for (int i = 0; i < 8; i++)
    {
        float angle = DirectX::XMConvertToRadians(i * 45.0f);

        Bullet b;
        b.Flg = true;
        b.type = Bullet::Converge;
        b.anim = 0;
        b.timer = 0;
        b.converge = false;

        b.pos = m_pos;  // 中ボスの位置
        b.move = { cosf(angle) * 3.0f, sinf(angle) * 3.0f };

        // プレイヤーの位置をターゲットにする
        b.target = player->GetPos();

       Bullets.push_back(b);
    }
}

void C_Battlecruiser::ShotSplit()
{
    Bullet b;
    b.Flg = true;
    b.type = Bullet::Split;

    b.timer = 0;
    b.split = false;
    b.anim = 0;
    b.pos = m_pos;
    b.move = { -7,0  };   

    Bullets.push_back(b);
}

void C_Battlecruiser::ShotLockSplit()
{
    C_Player* player = m_gameScene->GetPlayer();

    Bullet b;
    b.Flg = true;
    b.type = Bullet::lockSplit;

    b.pos = m_pos;

    // プレイヤー方向
    float dx = player->GetPos().x - b.pos.x;
    float dy = player->GetPos().y - b.pos.y;
    float angle = atan2f(dy, dx);

    b.ang = angle;
    b.move = { cosf(angle) * 6.0f, sinf(angle) * 6.0f };
    b.timer = 0;

    Bullets.push_back(b);
}

void C_Battlecruiser::ShotMine()
{
    Bullet b;
    b.Flg = true;
    b.type = Bullet::Mine;
    b.anim = 0;
    b.pos = m_pos;
    b.move = { -5, 0 };
    b.timer = 0;

    Bullets.push_back(b);
}

void C_Battlecruiser::ShotSpiralCross()
{
    float a1 = m_timer * 0.1f;
    float a2 = -m_timer * 0.1f;

    auto fire = [&](float angle)
        {
            Bullet b;
            b.Flg = true;
            b.type = Bullet::SpiralCross;
            b.pos = m_pos;
            b.ang = angle;
            b.speed = 4.0f;
            b.move = { cosf(angle), sinf(angle) };
            b.timer = 0;
            Bullets.push_back(b);
        };

    fire(a1);
    fire(a2);
}

void C_Battlecruiser::ShotConvergeBurst()
{
    C_Player* player = m_gameScene->GetPlayer();
    Bullet b;
    b.Flg = true;
    b.type = Bullet::ConvergeBurst;
    b.pos = m_pos;

    float angle = atan2(player->GetPos().y - m_pos.y, player->GetPos().x - m_pos.x);
    b.ang = angle;
    b.speed = 7.0f;
    b.move = { cosf(angle), sinf(angle) };
    b.timer = 0;

    Bullets.push_back(b);
}

void C_Battlecruiser::ShotRotateRing()
{
    const float PI = 3.14f;
    const int count = 12;
    float interval = (PI * 2.0f) / count;

    for (int i = 0; i < count; i++)
    {
        Bullet b;
        b.Flg = true;
        b.type = Bullet::RotateRing;

        b.origin = m_pos;        
        b.rad = 0;              
        b.baseAngle = interval * i;
        b.rotateSpeed = 0.01f;   
        b.timer = 0;

        Bullets.push_back(b);
    }
}

void C_Battlecruiser::Setphase(int phase)
{
    m_phase = phase;
    m_prevPhase = phase;   
    m_phaseDelay = 0;  

    if (phase == 1) {
        m_hp = m_hpMax * 0.80f;  // 80% 以上
    }
    else if (phase == 2) {
        m_hp = m_hpMax * 0.50f;  // 50% くらい
    }
    else if (phase == 3) {
        m_hp = m_hpMax * 0.20f;  // 20% 以下
    }

    // 弾を消す
    Bullets.clear();
}



