#include "SelectScene.h"
#include"SceneManager.h"
#include "../Scene.h"
#include"../Chara/Player/Player.h"

void C_SelectScene::Init()
{
	m_backTex.Load("Texture/SelectScene/Titleback.png");
	cannonTex.Load("Texture/SelectScene/CANNON.png");
	spacegunTex.Load("Texture/SelectScene/SPACEGUN.png");
	rocketTex.Load("Texture/SelectScene/ROCKET.png");
	cannonwindowTex.Load("Texture/SelectScene/cannonWindow.png");
	spacegunwindowTex.Load("Texture/SelectScene/spacegunWindow.png");
	rocketwindowTex.Load("Texture/SelectScene/rocketWindow.png");

	m_pos = { 0,0 };
	m_rect = { 0,0,1280,720 };
	cannonrect = { 0,0,273,100 };
	spacegunrect = { 0,0,312,100 };
	rocketrect = { 0,0,262,100 };
	cannonwindowrect = { 0,0,350,402 };
	spacegunwindowrect = { 0,0,350,402 };
	rocketwindowrect = { 0,0,350,402 };

	m_cannontrans = Math::Matrix::CreateTranslation(-400, -200, 0);
	m_spaceguntrans = Math::Matrix::CreateTranslation(0, -200, 0);
	m_rockettrans = Math::Matrix::CreateTranslation(400, -200, 0);
	cannonwindowmat = Math::Matrix::CreateTranslation(-400,100,0);
	spacegunwindowmat = Math::Matrix::CreateTranslation(0, 100, 0);
	rocketwindowmat = Math::Matrix::CreateTranslation(400,100,0);

	cannonscale = { 1,1 };
	spacegunscale = { 1,1 };
	rocketscale = { 1,1 };
	m_selectcannon = false;
	m_selectspacegun = false;
	m_selectrocket = false;
}

void C_SelectScene::ChangeUpdate()
{
	if (m_selectcannon)
	{
		SCENEMANAGER.ChangeState(new C_GameScene(PlayerType::cannon));
	}
	else if (m_selectspacegun)
	{
		SCENEMANAGER.ChangeState(new C_GameScene(PlayerType::spacegun));
	}
	else if (m_selectrocket)
	{
		SCENEMANAGER.ChangeState(new C_GameScene(PlayerType::rocket));
	}
	
}

void C_SelectScene::Update()
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
		SelectNum = (SelectNum + 1) % 3;
	}
	if (down && keyFlg)
	{
		SelectNum = (SelectNum + 2) % 3;
	}
	if (enter && keyFlg && !SCENE.GetKeyFlg())
	{
		switch (SelectNum)
		{
		case 0:
			m_selectcannon = true;
			break;
		case 1:
			m_selectspacegun = true;
			break;
		case 2:
			m_selectrocket = true;
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
		cannonscale = { 1.5,1.5 };
		spacegunscale = { 1,1 };
		rocketscale = { 1,1 };
		break;
	case 1:
		cannonscale = { 1,1 };
		spacegunscale = { 1.5,1.5 };
		rocketscale = { 1,1 };
		break;
	case 2:
		cannonscale = { 1,1};
		spacegunscale = { 1,1 };
		rocketscale = { 1.5,1.5 };
		break;
	}

	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_backMat = transmat;
	Math::Matrix transmat2 = Math::Matrix::CreateTranslation(m_pos.x + 1280, 0, 0);
	m_backMat2 = transmat2;

	Math::Matrix cannonscalemat = Math::Matrix::CreateScale(cannonscale.x, cannonscale.y, 1);
	m_cannonmat = cannonscalemat*m_cannontrans;
	

	Math::Matrix spacegunscalemat = Math::Matrix::CreateScale(spacegunscale.x, spacegunscale.y, 1);
	m_spacegunmat = spacegunscalemat * m_spaceguntrans;

	Math::Matrix rocketscalemat = Math::Matrix::CreateScale(rocketscale.x, rocketscale.y, 1);
	m_rocketmat = rocketscalemat * m_rockettrans;

}

void C_SelectScene::Draw()
{

	SHADER.m_spriteShader.SetMatrix(m_backMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_backMat2);
	SHADER.m_spriteShader.DrawTex(&m_backTex, m_rect);

	SHADER.m_spriteShader.SetMatrix(m_cannonmat);
	SHADER.m_spriteShader.DrawTex(&cannonTex, cannonrect);

	SHADER.m_spriteShader.SetMatrix(m_spacegunmat);
	SHADER.m_spriteShader.DrawTex(&spacegunTex, spacegunrect);

	SHADER.m_spriteShader.SetMatrix(m_rocketmat);
	SHADER.m_spriteShader.DrawTex(&rocketTex, rocketrect);

	SHADER.m_spriteShader.SetMatrix(cannonwindowmat);
	SHADER.m_spriteShader.DrawTex(&cannonwindowTex, cannonwindowrect);

	SHADER.m_spriteShader.SetMatrix(spacegunwindowmat);
	SHADER.m_spriteShader.DrawTex(&spacegunwindowTex, spacegunwindowrect);

	SHADER.m_spriteShader.SetMatrix(rocketwindowmat);
	SHADER.m_spriteShader.DrawTex(&rocketwindowTex, rocketwindowrect);
}

void C_SelectScene::Release()
{
	m_backTex.Release();
	cannonTex.Release();
	spacegunTex.Release();
	rocketTex.Release();
	cannonwindowTex.Release();
	spacegunwindowTex.Release();
	rocketwindowTex.Release();
}
