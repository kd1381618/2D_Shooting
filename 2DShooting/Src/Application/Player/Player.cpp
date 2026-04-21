#include"Player.h"

C_Player::C_Player()
{
	m_pos = { -500,0 };
	m_move = { 0,0 };
	m_charaFlg = true;
	m_rect = { 0,0,48,48 };
}

C_Player::~C_Player()
{
}

void C_Player::Init()
{
}

void C_Player::Action()
{
	if (m_charaFlg)
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
	}
}

void C_Player::Update()
{
	m_pos += m_move;
	m_move = { 0,0 };
	Math::Matrix m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y,0);
	m_mat = m_trans;
}

void C_Player::Draw()
{
	if (m_charaFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_baseTex, m_rect);
	}
}