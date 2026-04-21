#pragma once
#include"../Chara/CharaBase/CharaBase.h"

class C_GameScene;

class C_Player :public C_CharaBase
{
public:
	C_Player();
	~C_Player();

	void Init();
	void Action() override;
	void Update() override;
	void Draw() override;

	void SetBaseTex(KdTexture* tex) { m_baseTex = tex; }


private:
	bool m_charaFlg;
	KdTexture *m_baseTex;
};