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
	
	m_pos = { 0,0 };
	m_alive = true;
	anim = 0;
	m_rect = {0,0,32,32};
	m_scale = Math::Matrix::CreateScale(2, 2, 1);
	
}

void C_Medkit::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	
	if (!m_alive)return;

		m_pos.x -= 5;
		if (m_pos.x <= -640 - 16)
		{
			m_alive = false;
			return;
		}
			anim += 0.2f;
			if (anim > 12.0f)
			{
				anim = 0;
			}
			m_rect = {32 * (int)anim,0,32,32};
			if (player->GetAliveFlg() == true)
			{
				float dx = m_pos.x-player->GetPos().x;
				float dy = m_pos.y-player->GetPos().y;
				float dist = sqrt(dx * dx + dy * dy);
				if (dist < GetRadius()+player->GetRadius())
				{
					player->Heal(1);
					m_alive = false;
					anim = 0;
					return;
					
				}
			}
	
	
	
	if (m_alive == true)
	{
		m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scale * m_trans;

	}
}

void C_Medkit::Draw()
{
	
	
	if (m_alive == true)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect);
	}
	
}
