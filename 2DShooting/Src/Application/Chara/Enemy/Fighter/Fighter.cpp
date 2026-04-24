#include "Fighter.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Chara/Player/Player.h"

C_Fighter::C_Fighter()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	m_hpMax = 3;
	for (int e = 0; e < FighterNum; e++)
	{
		aliveFlg[e] = true;
		m_move[e].x = -3;
		m_pos[e].x = 640 + 64;
		m_pos[e].y = rand() % 656 + 1 - 328;
		m_rect[e] = { 0,0,64,64 };
		Weaponanim[e] = 0;
		shotwait[e] = 0;
		m_hp[e] = m_hpMax;
	}
	for (int i = 0; i < Fighterbullet.Num; i++)
	{
		Fighterbullet.Flg[i] = false;
		Fighterbullet.rect[i] = { 0,0,4,16 };
		Fighterbullet.anim[i] = 0;
	}
}

C_Fighter::~C_Fighter()
{

}
void C_Fighter::Init()
{

	
}

void C_Fighter::Action()
{
	C_Player* player = m_gameScene->GetPlayer();
	for (int e = 0; e < FighterNum; e++)
	{
		if (aliveFlg[e] == true)
		{
			Angle[e] = atan2(player->GetPos().y - m_pos[e].y, player->GetPos().x - m_pos[e].x);
			for (int i = 0; i < Fighterbullet.Num; i++)
			{
				if (Fighterbullet.Flg[i] == false)
				{
					if (shotwait[e] == 0)
					{
						Fighterbullet.Flg[i] = true;
						Fighterbullet.pos[i].x = m_pos[e].x;
						Fighterbullet.pos[i].y = m_pos[e].y;
						Fighterbullet.move[i].x = cosf(Angle[e]) * 10;
						Fighterbullet.move[i].y = sinf(Angle[e]) * 10;
						shotwait[e] = 60;
						break;
					}
				}
			}
		}
	}
	for (int e = 0; e < FighterNum; e++)
	{
		shotwait[e]--;
		if (shotwait[e] <= 0)
		{
			shotwait[e] = 0;
		}
	}
}

void C_Fighter::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	

	for (int e = 0; e < FighterNum; e++)
	{
		if (aliveFlg[e])
		{
			m_pos[e].x += m_move[e].x;
			if (m_pos[e].x <= -640 - 32)
			{
				m_pos[e].x = 640 + 32;
			}
			for (int i = 0; i < player->GetBulletNum(); i++)
			{
				if (player->GetBulletFlg(i)==true)
				{
					float a = m_pos[e].x - player->GetBulletPos(i).x;
					float b = m_pos[e].y - player->GetBulletPos(i).y;
					float c = sqrt(a * a + b * b);
					if (c < 41)
					{
						m_hp[e]--;
						player->SetBulletFlg(i, false);
						if (m_hp[e] <= 0)
						{
							aliveFlg[e] = false;
						}
						break;
					}
				}
			}

		}
	}
	for (int e = 0; e < FighterNum; e++)
	{
		if (aliveFlg[e])
		{
			Weaponanim[e] += 0.2f;
			if (Weaponanim[e] > 6.0f)
			{
				Weaponanim[e] = 0.0f;
			}
			m_rect[e] = { 64 * (int)Weaponanim[e],0,64,64 };
		}
	}

	for (int i = 0; i < Fighterbullet.Num; i++)
	{
		if (Fighterbullet.Flg[i] == true)
		{
			Fighterbullet.pos[i].x += Fighterbullet.move[i].x;
			Fighterbullet.pos[i].y += Fighterbullet.move[i].y;
			if (Fighterbullet.pos[i].x <= -640 - 16 || Fighterbullet.pos[i].x >= 640 + 16 || Fighterbullet.pos[i].y <= -360 - 16 || Fighterbullet.pos[i].y >= 360 + 16)
			{
				Fighterbullet.Flg[i] = false;
			}
			Fighterbullet.anim[i] += 0.1f;
			if (Fighterbullet.anim[i] > 4.0f)
			{
				Fighterbullet.anim[i] = 0;
			}
			Fighterbullet.rect[i] = { 4*(int)Fighterbullet.anim[i],0,4,16};
		}
	}
	for (int e = 0; e < FighterNum; e++)
	{
		m_transmat[e] = Math::Matrix::CreateTranslation(m_pos[e].x, m_pos[e].y, 0);
		m_rotatemat[e] = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
		m_scalemat[e] = Math::Matrix::CreateScale(2,2,1);
		m_mat[e] =m_scalemat[e]*m_rotatemat[e] *m_transmat[e];
	}
	for (int i = 0; i < Fighterbullet.Num; i++)
	{
		Fighterbullet.transmat[i]= Math::Matrix::CreateTranslation(Fighterbullet.pos[i].x, Fighterbullet.pos[i].y, 0);
		Fighterbullet.rotatemat[i] = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
		Fighterbullet.scalemat[i] = Math::Matrix::CreateScale(2, 2, 1);
		Fighterbullet.mat[i] =Fighterbullet.scalemat[i]* Fighterbullet.rotatemat[i] * Fighterbullet.transmat[i];
	}
}

void C_Fighter::Draw()
{
	for (int e = 0; e < FighterNum; e++)
	{
		if (aliveFlg[e] == true)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[e]);
			SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect[e]);
		}
		for (int i = 0; i < Fighterbullet.Num; i++)
		{
			if (Fighterbullet.Flg[i] == true)
			{
				SHADER.m_spriteShader.SetMatrix(Fighterbullet.mat[i]);
				SHADER.m_spriteShader.DrawTex(m_bulletTex, Fighterbullet.rect[i]);
			}
			
		}
	}
	
}
