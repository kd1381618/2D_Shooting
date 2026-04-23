#include"Back.h"

C_Back::C_Back()
{
	m_pos={ 0,0 };
	m_rect = { 0,0,1280,720 };
}

C_Back::~C_Back()
{

}

void C_Back::Init()
{

}

void C_Back::Update()
{
	m_pos.x -= 3;
	if (m_pos.x <= -1280)
	{
		m_pos.x = 0;
	}

	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = transmat;
	Math::Matrix transmat2= Math::Matrix::CreateTranslation(m_pos.x+1280, 0, 0);
	m_mat2 = transmat2;
}

void C_Back::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_backTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_mat2);
	SHADER.m_spriteShader.DrawTex(m_backTex, m_rect);
}