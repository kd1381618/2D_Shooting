#include "Battlecruiser.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../Item/Medkit.h"
#include"../../BulletUpdate/BulletUpdate.h"

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
    m_hpMax = 100;
    m_rect = { 0,0,128,128 };
    hpframerect = { 0,0,38,15 };
    hpbarrect = { 0,0,32,5 };
    m_hp = m_hpMax;
    Weaponanim = 0;
    bulletAnim = 0;
    destructionAnim = 0;
    m_scalemat = Math::Matrix::CreateScale(3, 3, 1);
    m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
    hpframescale = Math::Matrix::CreateScale(4, 4, 1);
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
    //フェーズ1：戦闘
    if (m_phase == 1)
    {
        Action();
        // 武器アニメ
        Weaponanim += 0.2f;
        if (Weaponanim > 30.0f) Weaponanim = 0;
        m_rect = { 128 * (int)Weaponanim,0,128, 128 };
        for (auto& b : Bullets)
        {
            b.anim += 0.2f;
            if (b.anim > 8.0)b.anim = 0;
            b.rect = { 8*(int)b.anim,0,8,8};
            UpdateBullet(b, Bullets);
            if (b.pos.x < -700||b.pos.x>700||b.pos.y<-360||b.pos.y>400) b.Flg = false;
        }
        // 死んだ弾を削除
        Bullets.erase(
            std::remove_if(Bullets.begin(), Bullets.end(),
                [](const Bullet& b) { return !b.Flg; }),
            Bullets.end()
        );
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
    hpframetrans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y + 150, 0);
    hpframemat = hpframescale * hpframetrans;
    hpbarscale = Math::Matrix::CreateScale(0.04*m_hp,4, 1);
    hpbartrans = Math::Matrix::CreateTranslation(m_pos.x-(m_hpMax-m_hp)/1.75, m_pos.y + 150 + 4, 0);
    hpbarmat = hpbarscale * hpbartrans;
}
void C_Battlecruiser::PlayerBulletHit()
{
    if (!m_aliveFlg) return;

    C_Player* player = m_gameScene->GetPlayer();
    auto& bullets = player->GetBullets();

    for (auto& b : bullets)
    {
        if (!b.Flg) continue;

        float dx = b.pos.x - m_pos.x;
        float dy = b.pos.y - m_pos.y;
        float dist = sqrtf(dx * dx + dy * dy);



        if (dist < 100)
        {
            b.Flg = false;
            if (m_phase == 0)return;
            m_hp--;

            if (m_hp <= 0)
            {
                m_hp = 0;
                m_aliveFlg = false;
                destructionFlg = true;
                destructionAnim = 0;
                m_gameScene->SetclearFlg(true);
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
    if (m_timer % 60 == 0) ShotConverge();
    if (m_timer % 120 == 0) ShotSplit();
    if (m_timer % 180 == 0)ShotMine();
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

