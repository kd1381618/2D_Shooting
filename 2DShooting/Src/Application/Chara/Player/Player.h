#pragma once
#include"../CharaBase/CharaBase.h"

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
	void SetEngineEffectTex(KdTexture* tex) { m_EngineEffectTex = tex; }
	void SetWeaponTex(KdTexture* tex) { m_WeaponTex = tex; }
	void SetBulletTex(KdTexture* tex) { m_bulletTex = tex; }
	void SetBulletFlg(int i, bool flg) { playerbullet.Flg[i] = flg; }
	Math::Vector2 GetPos() { return m_pos; }
	int GetBulletNum() { return playerbullet.Num; }
	Math::Vector2 GetBulletPos(int i) { return playerbullet.pos[i]; }
	bool GetBulletFlg(int i) { return playerbullet.Flg[i]; }


private:
	struct bullet playerbullet;
	KdTexture *m_baseTex;
	KdTexture* m_EngineEffectTex;
	KdTexture* m_WeaponTex;
	KdTexture* m_bulletTex;
	Math::Rectangle m_enginerect;
	Math::Rectangle m_weaponrect;
	Math::Matrix m_EngineEffectMat;
	float Engineanim;
	float Weaponanim;
};