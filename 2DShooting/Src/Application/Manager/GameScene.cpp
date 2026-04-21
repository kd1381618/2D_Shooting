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
	m_player->Action();

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
}

void C_GameScene::Init()
{
	//player=================================================================================
	if (m_player == nullptr) m_player = new C_Player;//キャラクラスのインスタンス生成
	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	m_player->SetBaseTex(&playerBaseTex);

	
}

void C_GameScene::Release()
{
	if (m_player != nullptr) delete m_player;

	playerBaseTex.Release();
	
}
