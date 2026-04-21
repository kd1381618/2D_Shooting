#pragma once
#include"State.h"

class C_Player;



class C_GameScene : public C_State
{

private:

	C_Player* m_player = nullptr;
	KdTexture playerBaseTex;

	int nowMap;//åªç›ÇÃÉ}ÉbÉvî‘çÜ


public:

	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;



	//setter 
	int GetNowMap() { return nowMap; }
	void SetNowMap(int a_nowMap) { nowMap = a_nowMap; }

};