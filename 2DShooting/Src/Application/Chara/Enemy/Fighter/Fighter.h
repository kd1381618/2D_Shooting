#pragma once
#include"../../CharaBase/CharaBase.h"

class C_GameScene;

class C_Fighter :public C_CharaBase
{
public:
	C_Fighter();
	~C_Fighter();

	void Init();
	void Action() override;
	void Update() override;
	void Draw() override;

	void SetBaseTex(KdTexture* tex) { m_baseTex = tex; }
	void SetEngineTex(KdTexture* tex) { m_EngineTex = tex; }
	void SetDestructionTex(KdTexture* tex) { m_DestructionTex = tex; }
	void SetBulletTex(KdTexture* tex) { m_bulletTex = tex; }
	void SetShieldTex(KdTexture* tex) { m_ShieldTex = tex; }


private:
	
	C_GameScene* m_gameScene;

	static const int FighterNum = 5;
	Math::Vector2 m_pos[FighterNum];
	Math::Vector2 m_move[FighterNum];
	Math::Matrix m_mat[FighterNum];
	Math::Matrix m_transmat[FighterNum];
	Math::Matrix m_scalemat[FighterNum];
	Math::Matrix m_rotatemat[FighterNum];
	bool aliveFlg[FighterNum];
	float Angle[FighterNum];
	struct bullet Fighterbullet;
	int shotwait[FighterNum];
	KdTexture* m_baseTex;
	KdTexture* m_EngineTex;
	KdTexture* m_DestructionTex;
	KdTexture* m_bulletTex;
	KdTexture* m_ShieldTex;
	Math::Rectangle m_enginerect;
	Math::Rectangle m_rect[FighterNum];
	Math::Rectangle m_bulletrect[FighterNum];
	Math::Matrix m_EngineEffectMat;
	float Engineanim;
	float Weaponanim[FighterNum];
	int m_hp[FighterNum];
};