#include "ClearScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../UI/Score/Score.h"

void C_ClearScene::Init()
{
	m_goGame = false;
	m_goTitle = false;
	m_backTex.Load("Texture/ClearScene/Titleback.png");
	m_scoreTex.Load("Texture/UI/GameScene/num.png");
	windowTex.Load("Texture/ClearScene/Window.png");
	homeTex.Load("Texture/GameOverScene/home.png");
	returnTex.Load("Texture/GameOverScene/return.png");
	m_pos = { 0,0 };
	m_rect = { 0,0,1280,720 };
	m_scorepos = { -100,30 };
	homescale = { 1,1 };
	returnscale = { 1,1 };
	buttonrect = { 0,0,114,38 };
	windowmat = Math::Matrix::CreateTranslation(0, 0, 0);
}
void C_ClearScene::Update()
{
	m_pos.x -= 3;
	if (m_pos.x <= -1280)
	{
		m_pos.x = 0;
	}
	unsigned long tmp = m_finalScore;
	for (int i = maxDigits - 1; i >= 0; --i)
	{
		m_digits[i] = tmp % 10;
		tmp /= 10;
	}
	bool up = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
	bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
	bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000);

	if (up && keyFlg)
	{
		SelectNum = (SelectNum + 1) % 2;
	}
	if (down && keyFlg)
	{
		SelectNum = (SelectNum + 1) % 2;
	}
	if (enter && keyFlg && !SCENE.GetKeyFlg())
	{
		switch (SelectNum)
		{
		case 0:
			m_goGame = true;
			break;
		case 1:
			m_goTitle = true;
			break;
		}
	}

	if (up || down || enter)
	{
		keyFlg = false;
	}
	else
	{
		keyFlg = true;
	}
	switch (SelectNum)
	{
	case 0:
		homescale = { 1,1 };
		returnscale = { 1.5,1.5 };
		break;
	case 1:
		homescale = { 1.5,1.5 };
		returnscale = { 1,1 };
		break;
	default:
		break;
	}
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_backMat = transmat;
	Math::Matrix transmat2 = Math::Matrix::CreateTranslation(m_pos.x + 1280, 0, 0);
	m_backMat2 = transmat2;
	Math::Matrix hometransmat = Math::Matrix::CreateTranslation(0, -200, 0);
	Math::Matrix homescalemat = Math::Matrix::CreateScale(homescale.x, homescale.y, 1);
	homemat = homescalemat * hometransmat;
	Math::Matrix returntransmat = Math::Matrix::CreateTranslation(0, -100, 0);
	Math::Matrix returnscalemat = Math::Matrix::CreateScale(returnscale.x, returnscale.y, 1);
	returnmat = returnscalemat * returntransmat;
}
void C_ClearScene::ChangeUpdate()
{
	if (m_goGame)
	{
		SCENE.SetNowScene(changeScene::Select);
		SCENEMANAGER.ChangeState(new C_SelectScene());
	}
	else if (m_goTitle)
	{
		SCENE.SetNowScene(changeScene::Select);
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
}
void C_ClearScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_backMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_backMat2);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	Math::Rectangle rc = { 0,0,522,600 };
	SHADER.m_spriteShader.SetMatrix(windowmat);
	SHADER.m_spriteShader.DrawTex(&windowTex, rc);

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 40 * m_digits[i], 0, 40, 40 };

		SHADER.m_spriteShader.DrawTex(
			&m_scoreTex,
			m_scorepos.x + (i * 45), m_scorepos.y,
			65, 65,
			&rc
		);
	}
	SHADER.m_spriteShader.SetMatrix(homemat);
	SHADER.m_spriteShader.DrawTex(&homeTex, buttonrect);

	SHADER.m_spriteShader.SetMatrix(returnmat);
	SHADER.m_spriteShader.DrawTex(&returnTex, buttonrect);
}
void C_ClearScene::Release()
{
	m_backTex.Release();
	m_scoreTex.Release();
	windowTex.Release();
	homeTex.Release();
	returnTex.Release();
}



