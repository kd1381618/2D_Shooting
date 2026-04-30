#pragma once
#include"../../CharaBase/CharaBase.h"

class C_GameScene;

class C_Scout :public C_CharaBase
{
public:
	C_Scout();
	~C_Scout();

	void Init();
	void Action() override;
	void Update() override;
	void ScoutBulletHit();
	void PlayerBulletHit();
	void Draw() override;
	void Damage(int amount);

	void SetBaseTex(KdTexture* tex) { m_baseTex = tex; }
	void SetEngineTex(KdTexture* tex) { m_EngineTex = tex; }
	void SetDestructionTex(KdTexture* tex) { m_DestructionTex = tex; }
	void SetBulletTex(KdTexture* tex) { m_bulletTex = tex; }
	void SetShieldTex(KdTexture* tex) { m_ShieldTex = tex; }
	//void SetBulletFlg(int i, bool flg) { Scoutbullet.Flg = flg; }
	int GetMaxHp() { return m_hpMax; }
	//int GetBulletNum() { return Scoutbullet.Num; }
	//Math::Vector2 GetBulletPos(int i) { return Scoutbullet.pos; }
	//bool GetBulletFlg(int i) { return Scoutbullet.Flg; }

private:
	
	C_GameScene* m_gameScene;



	float Angle;
	

	


	// 敵本体（単体）
	Math::Vector2 m_pos;
	Math::Vector2 m_move;

	Math::Matrix m_mat;
	Math::Matrix m_transmat;
	Math::Matrix m_scalemat;
	Math::Matrix m_rotatemat;
	Math::Matrix m_EngineEffectMat;
	bool m_aliveFlg;
	int m_hp;
	int m_hpMax;
	int respawnTimer;
	bool justRespawned = false;

	// アニメーション
	float Weaponanim;
	float Engineanim;
	float Shieldanim;
	float destructionAnim;

	int ShieldTime;
	int frame;
	bool destructionFlg;

	Math::Rectangle m_rect;
	Math::Rectangle m_Shieldrect;
	Math::Rectangle m_destructionrect;
	Math::Rectangle m_bulletrect;
	Math::Rectangle m_enginerect;
	// 弾（vector）
	std::vector<Bullet> scoutbullet;
	int shotwait = 0;
	// テクスチャ
	KdTexture* m_baseTex = nullptr;
	KdTexture* m_EngineTex = nullptr;
	KdTexture* m_DestructionTex = nullptr;
	KdTexture* m_bulletTex = nullptr;
	KdTexture* m_ShieldTex = nullptr;
};