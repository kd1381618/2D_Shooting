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

	C_Back* m_back = nullptr;
	KdTexture backTex;

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

	KdTexture medkitTex;
	std::vector<C_ItemBase*>m_items;

	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ
	


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
	//C_Scout* GetScout() { return  m_scout; }
};