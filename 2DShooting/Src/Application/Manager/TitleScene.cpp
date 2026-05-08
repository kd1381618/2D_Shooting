#include "TitleScene.h"
#include "../Scene.h"
#include "SceneManager.h"

void C_TitleScene::Init()
{

	m_titleTex.Load("Texture/TitleScene/Titleback.png");
	m_startTex.Load("Texture/TitleScene/START.png");
	m_exitTex.Load("Texture/TitleScene/EXIT.png");
	m_guideTex.Load("Texture/TitleScene/GUIDE.png");
	m_pos = { 0,0 };
	m_rect = { 0,0,1280,720 };
	m_startscale = { 1,1 };
	m_startrect = { 0,0,300,135 };
	m_exitrect = { 0,0,236,135 };
	m_exitscale={ 1,1 };
	m_guidescale = { 1,1 };
	m_guiderect = { 0,0,300,135 };
}
void C_TitleScene::ChangeUpdate()
{
	
}
void C_TitleScene::Update()
{
	m_pos.x -= 3;
	if (m_pos.x <= -1280)
	{
		m_pos.x = 0;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000||GetAsyncKeyState('W')&0x8000) { // 左キーが押された瞬間だけ処理
		if (keyFlg == true)
		{
			SelectNum = (SelectNum + 2) % 3; // 現在の選択項目を一つ上にずらす(逆ループする)
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000|| GetAsyncKeyState('S') & 0x8000) { // 右キーが押された瞬間だけ処理
		if (keyFlg == true)
		{
			SelectNum = (SelectNum + 1) % 3; // 現在の選択項目を一つ下にずらす(ループする)
		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == true)
		{
			switch (SelectNum)
			{
			case 0:
				SCENE.SetNowScene(changeScene::Game);
				SCENEMANAGER.ChangeState(new C_GameScene());
				break;
			case 1:

				break;
			case 2:

				break;
			default:
				break;
			}
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
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
		m_startscale = { 1.5,1.5 };
		m_guidescale = { 1,1 };
		m_exitscale = { 1,1 };
		break;
	case 1:
		m_startscale = { 1,1 };
		m_guidescale = { 1.5,1.5 };
		m_exitscale = { 1,1 };
		break;
	case 2:
		m_startscale = { 1,1 };
		m_guidescale = { 1,1 };
		m_exitscale = { 1.5,1.5 };
		break;
	default:
		break;
	}
	
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_titleMat = transmat;
	Math::Matrix transmat2 = Math::Matrix::CreateTranslation(m_pos.x + 1280, 0, 0);
	m_titleMat2 = transmat2;

	Math::Matrix starttrans = Math::Matrix::CreateTranslation(0, -100, 0);
	Math::Matrix startscale = Math::Matrix::CreateScale(m_startscale.x, m_startscale.y, 1);

	m_startMat = startscale * starttrans;

	Math::Matrix guidetrans = Math::Matrix::CreateTranslation(0, -200, 0);
	Math::Matrix guidescale = Math::Matrix::CreateScale(m_guidescale.x, m_guidescale.y, 1);

	m_guideMat = guidescale * guidetrans;

	Math::Matrix exittrans = Math::Matrix::CreateTranslation(0, -300, 0);
	Math::Matrix exitscale = Math::Matrix::CreateScale(m_exitscale.x, m_exitscale.y, 1);

	m_exitMat = exitscale * exittrans;


}
void C_TitleScene::Draw()
{

	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_titleMat2);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, m_startrect);

	SHADER.m_spriteShader.SetMatrix(m_guideMat);
	SHADER.m_spriteShader.DrawTex(&m_guideTex, m_guiderect);

	SHADER.m_spriteShader.SetMatrix(m_exitMat);
	SHADER.m_spriteShader.DrawTex(&m_exitTex, m_exitrect);
}


void C_TitleScene::Release()
{

	m_titleTex.Release();
	m_startTex.Release();
	m_exitTex.Release();
}
