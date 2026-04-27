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
}

void C_PlayerHp::Update()
{
	C_Player* player = m_gameScene->GetPlayer();
	hpanim = player->GetMaxHp() - player->GetHp();
	m_rect = { 48 * (int)hpanim,0,48,16 };

	m_transmat = Math::Matrix::CreateTranslation(-540,320 , 0);
	m_scalemat = Math::Matrix::CreateScale(5, 5, 1);
	m_mat = m_scalemat * m_transmat;
}

void C_PlayerHp::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rect);
}