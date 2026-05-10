#include "PlayerHp.h"
#include"../Player/Player.h"
#include"../../Manager/SceneManager.h"

C_PlayerHp::C_PlayerHp()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	Init();
}

void C_PlayerHp::Init()
{
	m_tablemat = Math::Matrix::CreateTranslation(0, -327.5, 0);
	m_tablerect = { 0,0,1280,65 };
	m_guiderect = { 0,0,529,46 };
	m_guidemat = Math::Matrix::CreateTranslation(-180, -330, 0);

}

void C_PlayerHp::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	hpanim = player->GetHp();
	m_rect = { 190 * (int)hpanim,0,190,70};

	m_transmat = Math::Matrix::CreateTranslation(-530, -330, 0);
	m_scalemat = Math::Matrix::CreateScale(0.8, 0.8, 1);
	m_mat = m_scalemat * m_transmat;

}

void C_PlayerHp::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_tablemat);
	SHADER.m_spriteShader.DrawTex(m_tableTex, m_tablerect);

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_guidemat);
	SHADER.m_spriteShader.DrawTex(m_guideTex, m_guiderect);
}