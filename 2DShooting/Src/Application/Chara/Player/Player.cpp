#include"Player.h"

C_Player::C_Player()
{
	m_pos = { -500,0 };
	m_move = { 0,0 };
	m_scale = { 1.5,1.5 };
	m_aliveFlg = true;
	m_rect = { 0,0,48,48 };
	Engineanim = 0;
	
	m_enginerect = { 0,0,48,48 };
	m_weaponrect = { 0,0,48,48 };
	for (int i = 0; i < playerbullet.Num; i++)
	{
		playerbullet.anim[i] = 0;
		playerbullet.rect[i] = { 0,0,32,32 };
		playerbullet.Flg[i] = 0;
	}
}

C_Player::~C_Player()
{
}

void C_Player::Init()
{
}

void C_Player::Action()
{
	if (m_aliveFlg)
	{
		if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_move.x = -7;
		}
		if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_move.x = 7;
		}
		if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_move.y = -7;
		}
		if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_move.y = 7;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (playerbullet.shotwait == 0)
			{
				for (int i = 0; i < playerbullet.Num; i++)
				{
					if (playerbullet.Flg[i] == 0)
					{
						playerbullet.Flg[i] = 1;
						playerbullet.x[i] = m_pos.x;
						playerbullet.y[i] = m_pos.y;
						playerbullet.shotwait = 10;
						break;
					}
				}
			}
			Weaponanim += 0.2f;
		}
		else
		{
			Weaponanim = 0.0f;
		}
		
		playerbullet.shotwait--;
		if (playerbullet.shotwait < 0)
		{
			playerbullet.shotwait = 0;
		}
	}
}

void C_Player::Update()
{
	if (m_aliveFlg)
	{
		for (int i = 0; i < playerbullet.Num; i++)
		{
			if (playerbullet.Flg[i] == 1)
			{
				playerbullet.x[i] += 15;
				if (playerbullet.x[i] >= 720 + 48)
				{
					playerbullet.Flg[i] = 0;
				}
			}
		}

		Engineanim += 0.1f;
		if (Engineanim > 4.0f)
		{
			Engineanim = 0.0f;
		}
		if (Weaponanim > 7.0f)
		{
			Weaponanim = 0.0f;
		}
		for (int i = 0; i < playerbullet.Num; i++)
		{
			playerbullet.anim[i] += 0.1f;
			if (playerbullet.anim[i] > 4.0f)
			{
				playerbullet.anim[i] = 0.0f;
			}
		}
		m_pos += m_move;
		m_move = { 0,0 };
		m_enginerect = { 48 * (int)Engineanim,0,48,48 };
		m_weaponrect = { 48 * (int)Weaponanim,0,48,48 };
		for (int i = 0; i < playerbullet.Num; i++)
		{
			playerbullet.rect[i] = { 32 * (int)playerbullet.anim[i],0,32,32 };
		}
	}
	Math::Matrix m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y,0);
	Math::Matrix m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y,1);
	m_mat = m_scaleMat*m_transMat;
	Math::Matrix m_EnginetransMat = Math::Matrix::CreateTranslation(m_pos.x-10, m_pos.y, 0);
	Math::Matrix m_EnginescaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_EngineEffectMat = m_EnginescaleMat * m_EnginetransMat;
	for (int i = 0; i < playerbullet.Num; i++)
	{
		playerbullet.transmat[i] = Math::Matrix::CreateTranslation(playerbullet.x[i], playerbullet.y[i], 0);
		playerbullet.scalemat[i] = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
		playerbullet.mat[i] = playerbullet.scalemat[i] * playerbullet.transmat[i];
	}
}

void C_Player::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);

		SHADER.m_spriteShader.SetMatrix(m_EngineEffectMat);
		SHADER.m_spriteShader.DrawTex(m_EngineEffectTex,m_enginerect);

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_WeaponTex, m_weaponrect);
		for (int i = 0; i < playerbullet.Num; i++)
		{

			SHADER.m_spriteShader.SetMatrix(playerbullet.mat[i]);
			SHADER.m_spriteShader.DrawTex(m_bulletTex, playerbullet.rect[i]);
		}
	}
}