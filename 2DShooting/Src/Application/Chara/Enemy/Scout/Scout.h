#pragma once
#include"../../CharaBase/CharaBase.h"

class C_GameScene;

class C_Scout :public C_CharaBase
{
public:
	C_Scout();
	~C_Scout()override;

	void Init()override;
	void Action() override;
	void Update() override;
	void ScoutBulletHit();
	void PlayerBulletHit();
	void Draw() override;
	void Damage(int amount);
	bool GetDestructionFlg() { return destructionFlg; }
	//void SetBulletFlg(int i, bool flg) { Scoutbullet.Flg = flg; }
	int GetMaxHp() { return m_hpMax; }
	//int GetBulletNum() { return Scoutbullet.Num; }
	//Math::Vector2 GetBulletPos(int i) { return Scoutbullet.pos; }
	//bool GetBulletFlg(int i) { return Scoutbullet.Flg; }
	bool C_Scout::HasBullet() const {
		return !scoutbullet.empty();
	}
private:
	
	C_GameScene* m_gameScene;



	float Angle;
	
	int respawnTimer;


	int ShieldTime;
	int frame;
	bool destructionFlg;

	// íeÅivectorÅj
	std::vector<Bullet> scoutbullet;
	int shotwait = 0;

};