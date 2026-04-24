#include "GameScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../Chara/Player/Player.h"
#include"../Back/Back.h"]
#include"../Chara/Enemy/Fighter/Fighter.h"

void C_GameScene::Draw()
{
	m_back->Draw();
	m_player->Draw();
	m_fighter->Draw();
}




void C_GameScene::Update()
{
	m_back->Update();
	m_player->Update();
	m_player->Action();
	m_fighter->Action();
	m_fighter->Update();

}

void C_GameScene::ChangeUpdate()
{

}

void C_GameScene::Init()
{
	//player=================================================================================
	if (m_player == nullptr) m_player = new C_Player;//キャラクラスのインスタンス生成
	if (m_back == nullptr)m_back = new C_Back;//背景
	if (m_fighter == nullptr)m_fighter = new C_Fighter;
	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	playerEngineEffectTex.Load("Texture/Player/Engine Effect/Engine.png");
	playerWeaponTex.Load("Texture/Player/Weapon/Weapon1.png");
	playerBulletTex.Load("Texture/Player/Bullet/bullet1.png");
	backTex.Load("Texture/Back/back1.png");
	fighterBaseTex.Load("Texture/Enemy/Base/FighterWeapons.png");
	fighterEngineTex.Load("Texture/Enemy/Engine/FighterEngine.png");
	fighterBulletTex.Load("Texture/Enemy/Bullet/Bullet.png");
	fighterDestructionTex.Load("Texture/Enemy/Destruction/FighterDestruction.png");
	fighterShieldTex.Load("Texture/Enemy/Shield/FighterShield.png");
	m_player->SetBaseTex(&playerBaseTex);
	m_player->SetEngineEffectTex(&playerEngineEffectTex);
	m_player->SetWeaponTex(&playerWeaponTex);
	m_player->SetBulletTex(&playerBulletTex);

	m_back->SetBackTex(&backTex);

	m_fighter->SetBaseTex(&fighterBaseTex);
	m_fighter->SetEngineTex(&fighterEngineTex);
	m_fighter->SetBulletTex(&fighterBulletTex);
	m_fighter->SetDestructionTex(&fighterDestructionTex);
	m_fighter->SetShieldTex(&fighterShieldTex);
}

void C_GameScene::Release()
{
	if (m_player != nullptr) delete m_player;
	if (m_back != nullptr)delete m_back;
	if (m_fighter != nullptr)delete m_fighter;

	playerBaseTex.Release();
	playerEngineEffectTex.Release();
	playerWeaponTex.Release();
	playerBulletTex.Release();
	backTex.Release();
	fighterBaseTex.Release();
	fighterEngineTex.Release();
	fighterBulletTex.Release();
	fighterDestructionTex.Release();
	fighterShieldTex.Release();
}
