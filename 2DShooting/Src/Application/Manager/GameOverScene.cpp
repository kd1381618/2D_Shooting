#include "GameOverScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../UI/Score/Score.h"

void C_GameOverScene::Init()
{
	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	m_backTex.Load("Texture/GameOverScene/GameOverback.png");
	m_scoreTex.Load("Texture/UI/GameScene/num.png");
	windowTex.Load("Texture/GameOverScene/Window.png");
	m_pos = { 0,0 };
	m_rect = { 0,0,1280,720 };
	m_scorepos = { 0,0 };
	windowmat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void C_GameOverScene::Update()
{
	C_Score* score = m_gameScene->GetScore();
	m_pos.x -= 3;
	if (m_pos.x <= -1280)
	{
		m_pos.x = 0;
	}
	unsigned long tmp = score->GetScore();
	for (int i = maxDigits - 1; i >= 0; --i)
	{
		m_digits[i] = tmp % 10;
		tmp /= 10;
	}
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_backMat = transmat;
	Math::Matrix transmat2 = Math::Matrix::CreateTranslation(m_pos.x + 1280, 0, 0);
	m_backMat2 = transmat2;

}
void C_GameOverScene::ChangeUpdate()
{

}
void C_GameOverScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_backMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_backMat2);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	Math::Rectangle rc = { 0,0,940,1080 };
	SHADER.m_spriteShader.SetMatrix(windowmat);
	SHADER.m_spriteShader.DrawTex(&windowTex,rc);

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 40 * m_digits[i], 0, 40, 40 };

		SHADER.m_spriteShader.DrawTex(
			&m_scoreTex,
			m_scorepos.x + (i * 40), m_scorepos.y,
			56, 56,
			&rc
		);
	}

}
void C_GameOverScene::Release()
{
	m_backTex.Release();
	m_scoreTex.Release();
	windowTex.Release();
}






