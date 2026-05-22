#pragma once
struct Bullet
{
	static const int Num = 100;
	Math::Vector2 pos;
	Math::Vector2 move;
	float scale;
	bool Flg;
	float Angle;
	int shotCnt;
	float moveAngle;
	float shotwait;
	float radius;
	float speed;
	float rad;
	float rotateSpeed;
	float baseAngle;
	float ang;
	float deg;
	float anim;
	float turnSpeed;
	Math::Matrix transmat;
	Math::Matrix scalemat;
	Math::Matrix rotatemat;
	Math::Matrix mat;
	Math::Rectangle rect;
	Math::Color color;
	int timer;
	// Žû‘©’e—p
	bool converge;
	Math::Vector2 target;
	Math::Vector2 origin;
	// •ª—ô’e—p
	bool split;
	int splitTimer;
	void* lasthitEnemy = nullptr;

	enum BulletType {
		Converge,
		Split,
		lockSplit,
		Spiral,
		Mine,
		FrigateBrake,
		SpiralCross,
		ConvergeBurst,
		RotateRing,
	}type;
	Bullet()
		: pos{ 0,0 }
		, move{ 0,0 }
		, scale(1)
		, Flg(false)
		, Angle(0)
		, shotCnt(0)
		, moveAngle(0)
		, shotwait(0)
		, radius(0)
		, speed(0)
		, rad(0)
		, ang(0)
		, deg(0)
		, anim(0)
		, turnSpeed(0.05)
		, transmat(Math::Matrix::Identity)
		, scalemat(Math::Matrix::Identity)
		, rotatemat(Math::Matrix::Identity)
		, mat(Math::Matrix::Identity)
		, rect{ 0,0,0,0 }
	    , color(1, 1, 1, 1)
		, timer(0)
		, converge(false)
		, split(false)
		, splitTimer(0)
		, type(Converge)
	{
	}
	
};
class C_CharaBase
{
public:
	C_CharaBase() {}
	virtual~C_CharaBase(){}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetBaseTex(KdTexture* tex) { m_baseTex = tex; }
	void SetEngineTex(KdTexture* tex) { m_EngineTex = tex; }
	void SetDestructionTex(KdTexture* tex) { m_DestructionTex = tex; }
	void SetBulletTex(KdTexture* tex) { m_bulletTex = tex; }
	void SetShieldTex(KdTexture* tex) { m_ShieldTex = tex; }
	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	float GetRadius() { return m_radius; }
	bool GetAlive() { return m_aliveFlg; }
	Math::Vector2 GetPos() { return m_pos; }

	protected:
	KdTexture* m_tex;
	KdTexture* m_baseTex;
	KdTexture* m_EngineTex;
	KdTexture* m_DestructionTex;
	KdTexture* m_bulletTex;
	KdTexture* m_ShieldTex;
	Math::Matrix m_scale;
	Math::Matrix m_mat;
	Math::Matrix m_transmat;
	Math::Matrix m_scalemat;
	Math::Matrix m_rotatemat;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Rectangle m_rect;
	Math::Rectangle m_Shieldrect;
	Math::Rectangle m_destructionrect;
	Math::Rectangle m_bulletrect;
	Math::Rectangle m_enginerect;
	float Weaponanim;
	float Engineanim;
	float Shieldanim;
	float destructionAnim;
	float bulletAnim;
	int m_hpMax;
	int m_hp;
	bool m_aliveFlg;
	bool destructionFlg;
	const float turnDeg=5.0f;
	float m_radius;
	bool hitflg;
};
