#include "GameScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../Player/Player.h"

void C_GameScene::Draw()
{
	m_player->Draw();
	
}




void C_GameScene::Update()
{
	m_player->Update();
	

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
}

void C_GameScene::Init()
{

	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	m_player->SetBaseTex(&playerBaseTex);

	
}

void C_GameScene::Release()
{
	playerBaseTex.Release();
	
}
