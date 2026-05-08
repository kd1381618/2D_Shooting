#pragma once
#include"../CharaBase/CharaBase.h"

class C_GameScene;

class C_Player :public C_CharaBase
{
public:
	C_Player();
	~C_Player()override;

	void Init()override;
	void Action() override;
	void Update() override;
	void BulletHit();
	void Draw() override;
	void Damage(int amount);
	void Heal(int heal);

	void SetWeaponTex(KdTexture* tex) { m_WeaponTex = tex; }

	void SetHp(int hp) { m_hp = hp; }
	void SetShieldTime(int i) { ShieldTime = i; }
	Math::Vector2 GetPos() { return m_pos; }
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_hpMax; }
	int GetShieldTime() { return ShieldTime; }
	std::vector<Bullet>& GetBullets() { return playerbullet; }
	bool GetAliveFlg() { return m_aliveFlg; }
	float GetHitRadius() const { return m_hitRadius; }
	float GetRadius()const { return 36.0f; }

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
	float Baseanim;
	float Engineanim;
	float Weaponanim;
	float Shieldanim;
	int ShieldTime;
	float m_alpha;
	float a_alpha;
	int shotwait = 0;
	static const int shotinterval = 20;
	float m_hitRadius = 15.0f;
};