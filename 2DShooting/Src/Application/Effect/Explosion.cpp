#include "Explosion.h"

C_Explosion::C_Explosion(Math::Vector2 pos)
{
	m_pos = pos;
	Init();
}

void C_Explosion::Init()
{
	anim = 0;
	Flg = true;
	m_scalemat = Math::Matrix::CreateScale(2, 2, 1);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Explosion::Update()
{
	anim += 0.2;
	if (anim > 7)Flg = false;
	m_rect = { 32 * (int)anim,0,32,32 };
	
	m_mat = m_scalemat * m_transmat;
	
}

void C_Explosion::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rect);
}


