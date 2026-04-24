#pragma once
#include"State.h"

class C_Player;
class C_Back;
class C_Fighter;


class C_GameScene : public C_State
{

private:

	C_Player* m_player = nullptr;
	KdTexture playerBaseTex;
	KdTexture playerEngineEffectTex;
	KdTexture playerWeaponTex;
	KdTexture playerBulletTex;

	C_Back* m_back = nullptr;
	KdTexture backTex;

	C_Fighter* m_fighter = nullptr;
	KdTexture fighterBaseTex;
	KdTexture fighterEngineTex;
	KdTexture fighterDestructionTex;
	KdTexture fighterBulletTex;
	KdTexture fighterShieldTex;

	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ


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
};