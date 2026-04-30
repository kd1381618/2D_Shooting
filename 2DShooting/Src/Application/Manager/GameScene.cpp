#include "GameScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../Chara/Player/Player.h"
#include"../Chara/Player/PlayerHp.h"
#include"../Back/Back.h"
#include"../Chara/Enemy/Scout/Scout.h"
#include"../Item/Medkit.h"

void C_GameScene::Draw()
{
	m_back->Draw();
	m_player->Draw();
	m_playerhp->Draw();
	for (auto* s : m_scouts) s->Draw();
	m_medkit->Draw();
}




void C_GameScene::Update()
{
	m_back->Update();
	m_player->Update();
	//m_player->BulletHit();
	m_playerhp->Update();
	for (auto* s : m_scouts) {
		s->Update();
		s->PlayerBulletHit();
		s->ScoutBulletHit();
	}
	m_medkit->Update();

}

void C_GameScene::ChangeUpdate()
{

}

void C_GameScene::Init()
{
	//player=================================================================================
	//std::shared_ptr<C_Player>player;
	//player = std::make_shared<C_Player>();//インスタンス生成
	//player->Init();						//初期化
	//m_chara.push_back(player);		//リストへ追加
	if (m_player == nullptr)m_player = new C_Player;
	if (m_playerhp == nullptr)m_playerhp = new C_PlayerHp;
	if (m_back == nullptr)m_back = new C_Back;//背景
	if (m_medkit == nullptr)m_medkit = new C_Medkit;
	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	playerEngineEffectTex.Load("Texture/Player/Engine Effect/Engine.png");
	playerWeaponTex.Load("Texture/Player/Weapon/Weapon1.png");
	playerBulletTex.Load("Texture/Player/Bullet/bullet1.png");
	playerHpTex.Load("Texture/UI/playerHp.png");
	playerShieldTex.Load("Texture/Player/Shield/Shield.png");
	backTex.Load("Texture/Back/back1.png");
	scoutBaseTex.Load("Texture/Enemy/Base/ScoutBase.png");
	scoutEngineTex.Load("Texture/Enemy/Engine/ScoutEngine.png");
	scoutBulletTex.Load("Texture/Enemy/Bullet/Bullet1_transparent.png");
	scoutDestructionTex.Load("Texture/Enemy/Destruction/ScoutDestruction.png");
	scoutShieldTex.Load("Texture/Enemy/Shield/ScoutShield.png");
	medkitTex.Load("Texture/Item/medkit_item.png");
	m_player->SetBaseTex(&playerBaseTex);
	m_player->SetEngineEffectTex(&playerEngineEffectTex);
	m_player->SetWeaponTex(&playerWeaponTex);
	m_player->SetBulletTex(&playerBulletTex);
	m_playerhp->SetTex(&playerHpTex);
	m_player->SetShieldTex(&playerShieldTex);

	m_back->SetBackTex(&backTex);
	for (int i = 0; i < 5; i++)
	{
		C_Scout* s = new C_Scout();

		// ★ テクスチャを全員にセット
		s->SetBaseTex(&scoutBaseTex);
		s->SetEngineTex(&scoutEngineTex);
		s->SetBulletTex(&scoutBulletTex);
		s->SetDestructionTex(&scoutDestructionTex);
		s->SetShieldTex(&scoutShieldTex);

		s->Init();
		m_scouts.push_back(s);
	}
	/*m_scout->SetBaseTex(&scoutBaseTex);
	m_scout->SetEngineTex(&scoutEngineTex);
	m_scout->SetBulletTex(&scoutBulletTex);
	m_scout->SetDestructionTex(&scoutDestructionTex);
	m_scout->SetShieldTex(&scoutShieldTex);*/

	m_medkit->SetTex(&medkitTex);

}

void C_GameScene::Release()
{
	if (m_player != nullptr) delete m_player;
	if (m_playerhp != nullptr) delete m_playerhp;
	if (m_back != nullptr)delete m_back;
	if (m_scout != nullptr)delete m_scout;
	if (m_medkit != nullptr)delete m_medkit;

	playerBaseTex.Release();
	playerEngineEffectTex.Release();
	playerWeaponTex.Release();
	playerBulletTex.Release();
	playerHpTex.Release();
	playerShieldTex.Release();
	backTex.Release();
	scoutBaseTex.Release();
	scoutEngineTex.Release();
	scoutBulletTex.Release();
	scoutDestructionTex.Release();
	scoutShieldTex.Release();
	medkitTex.Release();
}
