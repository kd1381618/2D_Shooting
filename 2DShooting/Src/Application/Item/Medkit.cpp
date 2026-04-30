#include "Medkit.h"
#include"../Chara/Player/Player.h"
#include"../Manager/SceneManager.h"

C_Medkit::C_Medkit()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	Init();
}

void C_Medkit::Init()
{
	for (int i = 0; i < MedkitNum; i++)
	{
		m_pos[i] = { 0,0 };
		Flg[i] = false;
		anim[i] = 0;
		m_rect[i] = {0,0,32,32};
		m_scale[i] = Math::Matrix::CreateScale(2, 2, 1);
	}
}

void C_Medkit::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	for (int i = 0; i < MedkitNum; i++)
	{
		if (Flg[i] == true)
		{
			m_pos[i].x -= 5;
			if (m_pos[i].x <= -640 - 16)
			{
				m_pos[i].x = 640 + 16;
			}
			anim[i] += 0.2f;
			if (anim[i] > 12.0f)
			{
				anim[i] = 0;
			}
			m_rect[i] = {32 * (int)anim[i],0,32,32};
			if (player->GetAliveFlg() == true)
			{
				float a = player->GetPos().x - m_pos[i].x;
				float b = player->GetPos().y - m_pos[i].y;
				float c = sqrt(a * a + b * b);
				if (c < 36 + 32)
				{
					Flg[i] = false;
					anim[i] = 0;
					player->SetHp(player->GetHp() + 1);
					break;
				}
			}
		}
	}
	for (int i = 0; i < MedkitNum; i++)
	{
		if (Flg[i] == true)
		{
			m_trans[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
			m_mat[i] = m_scale[i] * m_trans[i];
		}
	}
}

void C_Medkit::Draw()
{
	for (int i = 0; i < MedkitNum; i++)
	{
		if (Flg[i] == true)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(m_tex, m_rect[i]);
		}
	}
}
