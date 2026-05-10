#include "GameScene.h"
#include "../Scene.h"
#include "SceneManager.h"
#include"../Chara/Player/Player.h"
#include"../Chara/Player/PlayerHp.h"
#include"../Back/Back.h"
#include"../Chara/Enemy/Scout/Scout.h"
#include"../Chara/Enemy/Fighter/Fighter.h"
#include"../Item/Medkit.h"
#include"../UI/Score/Score.h"
#include"../Chara/Enemy/EnemySpawner/EnemySpawner.h"
#include"../Chara/Enemy/Battlecruiser/Battlecruiser.h"
#include"../Chara/Enemy/Frigate/Frigate.h"

void C_GameScene::Draw()
{
	m_back->Draw();
	m_player->Draw();
	if (m_midBossAppeared && !m_midBossDefeated)
	{
		m_midBoss->Draw();
	}
	for (auto* s : m_scout)
	{
		s->Draw();
	}
	for (auto* f : m_fighter)
	{
		f->Draw();
	}
	for (auto* e : m_frigate)
	{
		e->Draw();
	}
	for (auto& item : m_items)
	{
		item->Draw();
	}
	m_playerhp->Draw();
	m_score->Draw();

	SHADER.m_spriteShader.SetMatrix(m_feadoutMat);
	SHADER.m_spriteShader.DrawTex(&feadoutTex, Math::Rectangle{ 0,0,1280,720 }, feadoutAlpha);
}




void C_GameScene::Update()
{
	m_back->Update();
	m_player->Update();
	if (!m_midBossAppeared && time > 80.0f)
	{
		m_midBoss = new C_Battlecruiser();
		m_midBoss->Init();
		m_midBossAppeared = true;
		m_midBoss->SetBaseTex(&midBossBaseTex);
		m_midBoss->SetDestructionTex(&midBossDestructionTex);
		m_midBoss->SetBulletTex(&midBossBulletTex);
		m_midBoss->SetHpBarTex(&midBossHpBarTex);
		m_midBoss->SetHpFrameTex(&midBossHpframeTex);

		// 中ボス出現中は雑魚スポーン停止
		m_spawner->StopSpawn(true);
	}
	if (m_midBossAppeared && !m_midBossDefeated)
	{
		m_midBoss->Update();
		m_midBoss->PlayerBulletHit();
		m_midBoss->BossBulletHit();

		if (m_midBoss->IsDead()&&!m_midBoss->GetDestructionFlg())
		{
			m_midBossDefeated = true;
			// 雑魚スポーン再開
			m_spawner->StopSpawn(false);
		}
	}
	if (!m_midBossAppeared || m_midBossDefeated)
	{
		m_spawner->Update();
	}

	for (auto* s : m_scout) {
		s->Update();
		s->PlayerBulletHit();
		s->ScoutBulletHit();
		
	}
	m_scout.erase(
		std::remove_if(m_scout.begin(), m_scout.end(),
			[](C_Scout* s) {
				return (!s->GetAlive() && !s->GetDestructionFlg()&&!s->HasBullet());
			}),
		m_scout.end()
	);
	for (auto* f : m_fighter) {
		f->Update();
		f->PlayerBulletHit();
		f->FighterBulletHit();
		
	} 
	m_fighter.erase(
		std::remove_if(m_fighter.begin(), m_fighter.end(),
			[](C_Fighter* f) {
				return (!f->GetAlive() && !f->GetDestructionFlg()&&!f->HasBullet());
			}),
		m_fighter.end()
	);
	for (auto* e : m_frigate) {
		e->Update();
		e->PlayerBulletHit();
		e->FrigateBulletHit();
	}
	m_frigate.erase(
		std::remove_if(m_frigate.begin(), m_frigate.end(),
			[](C_Frigate* e) {
				return (!e->GetAlive() && !e->GetDestructionFlg() && !e->HasBullet());
			}),
		m_frigate.end()
	);
	for (auto& item : m_items) {
		item->Update();
	}
	m_items.erase(
		std::remove_if(m_items.begin(), m_items.end(),
			[](C_ItemBase* item) { return !item->IsAlive(); }),
		m_items.end()
	);

	m_playerhp->Update();
	m_score->Update();

	if (frame >= 60) {
		frame = 0;
		time += 1.0f;
	}
	else {
		frame++;
	}
	if (feadoutFlg)
	{
		feadoutAlpha += 0.01;
	}
	if (!m_player->GetAlive())
	{
		feadoutFlg = true;
		stopFlg = true;
	}
	if (clearFlg)
	{
		feadoutFlg = true;
	}
	if (feadoutAlpha >= 1.3&&stopFlg==true)
	{
		stopFlg = false;
		feadoutFlg = false;
		feadoutAlpha = 0;
		unsigned long score = m_score->GetScore();
		SCENEMANAGER.ChangeState(new C_GameOverScene(score));
		return;
	}
	if (feadoutAlpha >= 1.3 && clearFlg == true)
	{
		feadoutFlg = false;
		feadoutAlpha = 0;
		unsigned long score = m_score->GetScore();
		SCENEMANAGER.ChangeState(new C_ClearScene(score));
		return;
	}
	m_feadoutMat = Math::Matrix::CreateTranslation(m_feadoutPos.x, m_feadoutPos.y, 0);
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
	if (m_score == nullptr)m_score = new C_Score;
	if (m_spawner == nullptr)m_spawner = new C_EnemySpawner();
	//if (m_medkit == nullptr)m_medkit = new C_Medkit;
	playerBaseTex.Load("Texture/Player/Base/playerBase.png");
	playerEngineTex.Load("Texture/Player/Engine Effect/Engine.png");
	playerWeaponTex.Load("Texture/Player/Weapon/Weapon1.png");
	playerBulletTex.Load("Texture/Player/Bullet/bullet1.png");
	playerHpTex.Load("Texture/UI/GameScene/PlayerHpBar.png");
	tableTex.Load("Texture/UI/GameScene/Table.png");
	playerShieldTex.Load("Texture/Player/Shield/Shield.png");
	backTex.Load("Texture/Back/back1.png");
	scoutBaseTex.Load("Texture/Enemy/Base/ScoutBase.png");
	scoutEngineTex.Load("Texture/Enemy/Engine/ScoutEngine.png");
	scoutBulletTex.Load("Texture/Enemy/Bullet/Bullet1_transparent.png");
	scoutDestructionTex.Load("Texture/Enemy/Destruction/ScoutDestruction.png");
	scoutShieldTex.Load("Texture/Enemy/Shield/ScoutShield.png");
	fighterBaseTex.Load("Texture/Enemy/Base/FighterBase.png");
	fighterBulletTex.Load("Texture/Enemy/Bullet/BigBullet.png");
	fighterEngineTex.Load("Texture/Enemy/Engine/FighterEngine.png");
	fighterDestructionTex.Load("Texture/Enemy/Destruction/FighterDestruction.png");
	fighterShieldTex.Load("Texture/Enemy/Shield/FighterShield.png");
	medkitTex.Load("Texture/Item/medkit_item.png");
	scoreTex.Load("Texture/UI/GameScene/Score.png");
	numTex.Load("Texture/UI/GameScene/num.png");
	midBossBaseTex.Load("Texture/Enemy/Base/BattlecruiserBase.png");
	midBossDestructionTex.Load("Texture/Enemy/Destruction/BattlecruiserDestruction.png");
	midBossBulletTex.Load("Texture/Enemy/Bullet/SpinningBullet.png");
	midBossHpBarTex.Load("Texture/UI/GameScene/hpbar1.png");
	midBossHpframeTex.Load("Texture/UI/GameScene/hpframe1.png");
	feadoutTex.Load("Texture/Back/feadout.png");
	frigateBaseTex.Load("Texture/Enemy/Base/FrigateBase.png");
	frigateBulletTex.Load("Texture/Enemy/Bullet/BigSpaceGun.png");
	frigateEngineTex.Load("Texture/Enemy/Engine/FrigateEngine.png");
	frigateDestructionTex.Load("Texture/Enemy/Destruction/FrigateDestruction.png");
	sousaTex.Load("Texture/UI/GameScene/sousa.png");

	m_spawner->SetScoutBaseTex(&scoutBaseTex);
	m_spawner->SetScoutEngineTex(&scoutEngineTex);
	m_spawner->SetScoutBulletTex(&scoutBulletTex);
	m_spawner->SetScoutDestructionTex(&scoutDestructionTex);
	m_spawner->SetScoutShieldTex(&scoutShieldTex);

	
	m_spawner->SetFighterBaseTex(&fighterBaseTex);
	m_spawner->SetFighterEngineTex(&fighterEngineTex);
	m_spawner->SetFighterBulletTex(&fighterBulletTex);
	m_spawner->SetFighterDestructionTex(&fighterDestructionTex);
	m_spawner->SetFighterShieldTex(&fighterShieldTex);

	m_spawner->SetFrigateBaseTex(&frigateBaseTex);
	m_spawner->SetFrigateBulletTex(&frigateBulletTex);
	m_spawner->SetFrigateEngineTex(&frigateEngineTex);
	m_spawner->SetFrigateDestructionTex(&frigateDestructionTex);

	m_spawner->SetScoutList(&m_scout);
	m_spawner->SetFighterList(&m_fighter);
	m_spawner->SetFrigateList(&m_frigate);

	m_player->SetBaseTex(&playerBaseTex);
	m_player->SetEngineTex(&playerEngineTex);
	m_player->SetWeaponTex(&playerWeaponTex);
	m_player->SetBulletTex(&playerBulletTex);
	m_playerhp->SetTex(&playerHpTex);
	m_playerhp->SetTableTex(&tableTex);
	m_playerhp->SetGuideTex(&sousaTex);
	m_player->SetShieldTex(&playerShieldTex);

	m_score->SetTex(&numTex);
	m_score->SetScoreTex(&scoreTex);
	m_score->Init();

	m_back->SetBackTex(&backTex);

	feadoutFlg = false;
	stopFlg = false;
	clearFlg = false;
	//for (int i = 0; i < 5; i++)
	//{
	//	C_Scout* s = new C_Scout();

	//	//テクスチャを全員にセット
	//	s->SetBaseTex(&scoutBaseTex);
	//	s->SetEngineTex(&scoutEngineTex);
	//	s->SetBulletTex(&scoutBulletTex);
	//	s->SetDestructionTex(&scoutDestructionTex);
	//	s->SetShieldTex(&scoutShieldTex);
	//	s->Init();
	//	m_scout.push_back(s);
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	C_Fighter* f = new C_Fighter();
	//	f->SetBaseTex(&fighterBaseTex);
	//	f->SetBulletTex(&fighterBulletTex);
	//	f->SetEngineTex(&fighterEngineTex);
	//	f->SetDestructionTex(&fighterDestructionTex);
	//	f->SetShieldTex(&fighterShieldTex);
	//	f->Init();
	//	m_fighter.push_back(f);
	//}
	
	
	/*m_scout->SetBaseTex(&scoutBaseTex);
	m_scout->SetEngineTex(&scoutEngineTex);
	m_scout->SetBulletTex(&scoutBulletTex);
	m_scout->SetDestructionTex(&scoutDestructionTex);
	m_scout->SetShieldTex(&scoutShieldTex);*/

	//m_medkit->SetTex(&medkitTex);
	frame = 0;
	time = 0;
}

void C_GameScene::Release()
{
	if (m_player != nullptr) delete m_player;
	if (m_playerhp != nullptr) delete m_playerhp;
	if (m_back != nullptr)delete m_back;
	if (m_score != nullptr)delete m_score;
	if (m_spawner != nullptr)delete m_spawner;
	if (m_midBoss != nullptr)delete m_midBoss;
	for (auto* f : m_fighter) delete f;
	for (auto* s : m_scout) delete s;
	for (auto* item : m_items) delete item;
	playerBaseTex.Release();
	playerEngineTex.Release();
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
	fighterBaseTex.Release();
	fighterBulletTex.Release();
	fighterDestructionTex.Release();
	fighterEngineTex.Release();
	fighterShieldTex.Release();
	medkitTex.Release();
	scoreTex.Release();
	numTex.Release();
	midBossBaseTex.Release();
	midBossDestructionTex.Release();
	midBossBulletTex.Release();
	midBossHpBarTex.Release();
	midBossHpframeTex.Release();
	feadoutTex.Release();
	frigateBaseTex.Release();
	frigateBulletTex.Release();
}

void C_GameScene::SpawnMedkit(const Math::Vector2& pos)
{
	C_Medkit* m = new C_Medkit();
	m->SetPos(pos);
	m->SetTex(&medkitTex);   
	m->SetAlive(true);
	m_items.push_back(m);
}
