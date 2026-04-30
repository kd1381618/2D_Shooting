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
	void BulletHit();
	void Draw() override;
	void Damage(int amount);

	void SetBaseTex(KdTexture* tex) { m_baseTex = tex; }
	void SetEngineEffectTex(KdTexture* tex) { m_EngineEffectTex = tex; }
	void SetWeaponTex(KdTexture* tex) { m_WeaponTex = tex; }
	void SetBulletTex(KdTexture* tex) { m_bulletTex = tex; }
	void SetShieldTex(KdTexture* tex) { m_ShieldTex = tex; }
	void SetHp(int hp) { m_hp = hp; }
	Math::Vector2 GetPos() { return m_pos; }
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_hpMax; }
	std::vector<Bullet>& GetBullets() { return playerbullet; }
	bool GetAliveFlg() { return m_aliveFlg; }
	float GetHitRadius() const { return m_hitRadius; }


private:

	C_GameScene* m_gameScene;

	std::vector<Bullet>playerbullet;
	KdTexture *m_baseTex;
	KdTexture* m_EngineEffectTex;
	KdTexture* m_WeaponTex;
	KdTexture* m_bulletTex;
	KdTexture* m_ShieldTex;
	Math::Rectangle m_enginerect;
	Math::Rectangle m_weaponrect;
	Math::Rectangle m_shieldrect;
	Math::Matrix m_EngineEffectMat;
	float Baseanim;
	float Engineanim;
	float Weaponanim;
	float Shieldanim;
	int ShieldTime;
	float m_alpha;
	float a_alpha;
	int shotwait = 0;
	int shotinterval = 10;
	float m_hitRadius = 20.0f;
};