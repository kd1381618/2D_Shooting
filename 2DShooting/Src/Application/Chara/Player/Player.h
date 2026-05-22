#pragma once
#include"../CharaBase/CharaBase.h"

class C_GameScene;

enum PlayerType
{
	cannon,
	spacegun,
	rocket,
};

class C_Player :public C_CharaBase
{
public:
	C_Player();
	~C_Player()override;

	void Init()override;
	void Action() override;
	void Update() override;
	void BulletUpdate();
	void Draw() override;
	void Damage(int amount);
	void Heal(int heal);
	void Exp(int exp);

	void SetWeaponTex(KdTexture* tex) { m_WeaponTex = tex; }


	Math::Vector2 GetPos() { return m_pos; }
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_hpMax; }
	int GetShieldTime() { return ShieldTime; }
	std::vector<Bullet>& GetBullets() { return playerbullet; }
	bool GetAliveFlg() { return m_aliveFlg; }
	float GetHitRadius() const { return m_hitRadius; }
	float GetRadius()const { return 36.0f; }
	int GetType() { return m_playertype; }
	float GetBulletSize() { return BulletSize; }
	

	void SetHp(int hp) { m_hp = hp; }
	void SetShieldTime(int i) { ShieldTime = i; }
	void SetInvincible(bool flg) { Invincible = flg; }
	void SetType(int type) { m_playertype = type; }
	void SetSpaceGunTex(KdTexture* tex) { m_spacegunTex = tex; }
	void SetSpaceGunBaseTex(KdTexture* tex) { m_spacegunBaseTex = tex; }
	void SetSpaceGunEffectTex(KdTexture* tex) { m_spacegunEffectTex = tex; }
	void SetSpaceGunWeaponTex(KdTexture* tex) { m_spacegunWeaponTex = tex; }
	void SetRocketTex(KdTexture* tex) { m_rocketTex = tex; }
	void SetRocketBaseTex(KdTexture* tex) { m_rocketBaseTex = tex; }
	void SetRocketEffectTex(KdTexture* tex) { m_rocketEffectTex = tex; }
	void SetRocketWeaponTex(KdTexture* tex) { m_rocketWeaponTex = tex; }
	void SetHealTex(KdTexture* tex) { m_HealTex = tex; }

private:

	C_GameScene* m_gameScene;

	std::vector<Bullet>playerbullet;
	KdTexture* m_WeaponTex;
	Math::Rectangle m_enginerect;
	Math::Rectangle m_weaponrect;
	Math::Rectangle m_shieldrect;
	Math::Matrix m_EngineEffectMat;
	Math::Matrix m_scaleMat;
	Math::Matrix m_EnginescaleMat;
	Math::Matrix m_WeaponMat;
	Math::Matrix m_WeaponscaleMat;
	float Baseanim;
	float Engineanim;
	float Weaponanim;
	float Shieldanim;
	int ShieldTime;
	float m_alpha;
	float a_alpha;
	bool Invincible;
	int shotwait = 0;
	static const int cannonshotinterval = 20;
	static const int spacegunshotinterval = 60;
	static const int rocketshotinterval = 20;
	float m_hitRadius = 15.0f;
	int m_playertype;
	KdTexture* m_spacegunTex;
	KdTexture* m_spacegunBaseTex;
	KdTexture* m_spacegunEffectTex;
	KdTexture* m_spacegunWeaponTex;
	KdTexture* m_rocketTex;
	KdTexture* m_rocketBaseTex;
	KdTexture* m_rocketEffectTex;
	KdTexture* m_rocketWeaponTex;
	KdTexture* m_HealTex;
	float BulletSize;
	int m_Lv;
	static const int m_LvMax = 5;
	int m_exp;
	int m_expMax;
	bool HealFlg;
	Math::Rectangle Healrect;
	float Healanim;
};