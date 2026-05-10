#include "TitleScene.h"
#include "../Scene.h"
#include "SceneManager.h"

void C_TitleScene::Init()
{
	m_goGame = false;
	m_goExit = false;
	m_titleTex.Load("Texture/TitleScene/Titleback.png");
	m_startTex.Load("Texture/TitleScene/START.png");
	m_exitTex.Load("Texture/TitleScene/EXIT.png");
	m_pos = { 0,0 };
	m_rect = { 0,0,1280,720 };
	m_startscale = { 1,1 };
	m_startrect = { 0,0,300,135 };
	m_exitrect = { 0,0,236,135 };
	m_exitscale={ 1,1 };
}
void C_TitleScene::ChangeUpdate()
{
	if (m_goGame)
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}
	else if (m_goExit)
	{
		
	}
}
void C_TitleScene::Update()
{
	m_pos.x -= 3;
	if (m_pos.x <= -1280)
	{
		m_pos.x = 0;
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
	if (enter && keyFlg&&!SCENE.GetKeyFlg())
	{
		switch (SelectNum)
		{
		case 0:
			m_goGame = true;
			break;
		case 1:
			SCENEMANAGER.ExitApp();	
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
		m_startscale = { 1.5,1.5 };
		m_exitscale = { 1,1 };
		break;
	case 1:
		m_startscale = { 1,1 };
		m_exitscale = { 1.5,1.5 };
		break;
	}
	
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_titleMat = transmat;
	Math::Matrix transmat2 = Math::Matrix::CreateTranslation(m_pos.x + 1280, 0, 0);
	m_titleMat2 = transmat2;

	Math::Matrix starttrans = Math::Matrix::CreateTranslation(0, -150, 0);
	Math::Matrix startscale = Math::Matrix::CreateScale(m_startscale.x, m_startscale.y, 1);

	m_startMat = startscale * starttrans;

	Math::Matrix exittrans = Math::Matrix::CreateTranslation(0, -250, 0);
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

	SHADER.m_spriteShader.SetMatrix(m_exitMat);
	SHADER.m_spriteShader.DrawTex(&m_exitTex, m_exitrect);
}


void C_TitleScene::Release()
{

	m_titleTex.Release();
	m_startTex.Release();
	m_exitTex.Release();
}
