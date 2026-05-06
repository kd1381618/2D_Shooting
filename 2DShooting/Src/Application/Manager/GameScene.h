#pragma once
#include"State.h"

class C_Player;
class C_PlayerHp;
class C_Back;
class C_Scout;
class C_Medkit;
class C_CharaBase;
class C_ItemBase;
class C_Fighter;
class C_Score;
class C_EnemySpawner;
class C_Battlecruiser;

class C_GameScene : public C_State
{

private:

	C_Player* m_player = nullptr;
	KdTexture playerBaseTex;
	KdTexture playerEngineTex;
	KdTexture playerWeaponTex;
	KdTexture playerBulletTex;
	KdTexture playerShieldTex;

	C_PlayerHp* m_playerhp = nullptr;
	KdTexture playerHpTex;
	KdTexture tableTex;

	C_Back* m_back = nullptr;
	KdTexture backTex;

	C_Score* m_score = nullptr;
	KdTexture scoreTex;
	KdTexture numTex;

	std::vector<C_Scout*>m_scout;
	KdTexture scoutBaseTex;
	KdTexture scoutEngineTex;
	KdTexture scoutDestructionTex;
	KdTexture scoutBulletTex;
	KdTexture scoutShieldTex;

	std::vector<C_Fighter*> m_fighter;
	KdTexture fighterBaseTex;
	KdTexture fighterEngineTex;
	KdTexture fighterDestructionTex;
	KdTexture fighterBulletTex;
	KdTexture fighterShieldTex;

	C_Battlecruiser* m_midBoss = nullptr;
	KdTexture midBossBaseTex;
	bool m_midBossAppeared = false;
	bool m_midBossDefeated = false;

	KdTexture medkitTex;
	std::vector<C_ItemBase*>m_items;

	C_EnemySpawner* m_spawner=nullptr;
	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ
	
	float frame;
	float time;


public:

	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void SpawnMedkit(const Math::Vector2& pos);


	//setter 
	int GetNowMap() { return nowMap; }
	void SetNowMap(int a_nowMap) { nowMap = a_nowMap; }

	C_Player* GetPlayer() { return m_player; }
	C_Score* GetScore() { return m_score; }
	//C_Scout* GetScout() { return  m_scout; }
};