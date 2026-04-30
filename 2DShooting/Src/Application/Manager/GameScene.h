#pragma once
#include"State.h"

class C_Player;
class C_PlayerHp;
class C_Back;
class C_Scout;
class C_Medkit;
class C_CharaBase;


class C_GameScene : public C_State
{

private:

	C_Player* m_player = nullptr;
	KdTexture playerBaseTex;
	KdTexture playerEngineEffectTex;
	KdTexture playerWeaponTex;
	KdTexture playerBulletTex;
	KdTexture playerShieldTex;

	C_PlayerHp* m_playerhp = nullptr;
	KdTexture playerHpTex;

	C_Back* m_back = nullptr;
	KdTexture backTex;

	C_Scout* m_scout = nullptr;
	KdTexture scoutBaseTex;
	KdTexture scoutEngineTex;
	KdTexture scoutDestructionTex;
	KdTexture scoutBulletTex;
	KdTexture scoutShieldTex;

	KdTexture medkitTex;
	C_Medkit* m_medkit = nullptr;

	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ
	std::vector<std::shared_ptr<C_CharaBase>>m_chara;
	std::vector<C_Scout*>m_scouts;

public:

	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;



	//setter 
	int GetNowMap() { return nowMap; }
	void SetNowMap(int a_nowMap) { nowMap = a_nowMap; }

	C_Player* GetPlayer() { return m_player; }
	C_Scout* GetScout() { return m_scout; }
	C_Medkit* GetMedkit() { return m_medkit; }
};