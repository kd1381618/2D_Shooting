#include "Battlecruiser.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"
#include"../../../Item/Medkit.h"

C_Battlecruiser::C_Battlecruiser()
{
    m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
    m_phase = 0;
    m_timer = 0;
    m_hpMax = 3;
    m_rect = { 0,0,128,128 };
}

void C_Battlecruiser::Init()
{
    m_aliveFlg = true;
    destructionFlg = false;

    // ★ 右端の外に出現
    m_pos = { 700.0f, 0.0f };

    m_hp = m_hpMax;
    m_scalemat = Math::Matrix::CreateScale(3, 3, 1);
    m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
}

void C_Battlecruiser::Update()
{
    if (!m_aliveFlg)
    {
        // 爆発アニメなどはここで後で追加
        return;
    }

    m_timer++;

    // ★ フェーズ0：右端から入場
    if (m_phase == 0)
    {
        m_pos.x -= 2.0f; // 左へ移動

        if (m_pos.x <= 500.0f) // 戦闘位置
        {
            m_phase = 1;
            m_timer = 0;
        }
    }

    // ★ フェーズ1：戦闘
    if (m_phase == 1)
    {
        Action();
    }
    m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scalemat*m_rotatemat * m_transmat;
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
            }

            break;
        }
    }
}

void C_Battlecruiser::Action()
{
    // ★ とりあえず何もしない（後で攻撃追加）
}

void C_Battlecruiser::Draw()
{
    if (!m_aliveFlg) return;
    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);
  
}