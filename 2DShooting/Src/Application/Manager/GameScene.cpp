#include "GameScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../Chara/Player/Player.h"
#include"../Back/Back.h"

void C_GameScene::Draw()
{
	m_back->Draw();
	m_player->Draw();
	
}




void C_GameScene::Update()
{
	m_back->Update();
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
	if (m_back == nullptr)m_back = new C_Back;
	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	playerEngineEffectTex.Load("Texture/Player/Engine Effect/Engine.png");
	playerWeaponTex.Load("Texture/Player/Weapon/Weapon1.png");
	playerBulletTex.Load("Texture/Player/Bullet/bullet1.png");
	backTex.Load("Texture/Back/back1.png");
	m_player->SetBaseTex(&playerBaseTex);
	m_player->SetEngineEffectTex(&playerEngineEffectTex);
	m_player->SetWeaponTex(&playerWeaponTex);
	m_player->SetBulletTex(&playerBulletTex);

	m_back->SetBackTex(&backTex);
}

void C_GameScene::Release()
{
	if (m_player != nullptr) delete m_player;
	if (m_back != nullptr)delete m_back;

	playerBaseTex.Release();
	playerEngineEffectTex.Release();
	playerWeaponTex.Release();
	playerBulletTex.Release();
	backTex.Release();
}
