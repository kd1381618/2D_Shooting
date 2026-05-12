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
class C_Frigate;
class C_Explosion;

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
	Math::Vector2 scorepos;
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

	std::vector<C_Frigate*> m_frigate;
	KdTexture frigateBaseTex;
	KdTexture frigateBulletTex;
	KdTexture frigateEngineTex;
	KdTexture frigateDestructionTex;


	C_Battlecruiser* m_midBoss = nullptr;
	KdTexture midBossBaseTex;
	KdTexture midBossDestructionTex;
	KdTexture midBossBulletTex;
	KdTexture midBossEngineTex;
	KdTexture midBossShieldTex;
	KdTexture midBossHpBarTex;
	KdTexture midBossHpframeTex;
	bool m_midBossAppeared = false;
	bool m_midBossDefeated = false;

	KdTexture medkitTex;
	std::vector<C_ItemBase*>m_items;

	std::vector<C_Explosion*>m_explosion;
	KdTexture explosionTex;

	KdTexture sousaTex;

	C_EnemySpawner* m_spawner=nullptr;
	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ
	
	float frame;
	float time;

	bool stopFlg = false;
	bool feadoutFlg = false;
	float feadoutAlpha = 0;
	Math::Vector2 m_feadoutPos = { 0,0 };
	Math::Matrix m_feadoutMat;
	KdTexture feadoutTex;
	bool clearFlg=false;
	bool debugKeyFlg = true;

public:

	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void SpawnMedkit(const Math::Vector2& pos);
	void AddExplosion(Math::Vector2 pos);
	

	//setter 
	int GetNowMap() { return nowMap; }
	void SetNowMap(int a_nowMap) { nowMap = a_nowMap; }
	void SetclearFlg(bool flg) { clearFlg = flg; }

	C_Player* GetPlayer() { return m_player; }
	C_Score* GetScore() { return m_score; }
	//C_Scout* GetScout() { return  m_scout; }
};