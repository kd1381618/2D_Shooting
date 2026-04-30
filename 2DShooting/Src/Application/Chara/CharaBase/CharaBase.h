#pragma once
struct Bullet
{
	static const int Num = 100;
	Math::Vector2 pos;
	Math::Vector2 move;
	bool Flg;
	float Angle;
	int shotCnt;
	float moveAngle;
	float shotwait;
	float radius;
	float speed;
	float rad;
	float ang;
	float deg;
	float anim;
	Math::Matrix transmat;
	Math::Matrix scalemat;
	Math::Matrix rotatemat;
	Math::Matrix mat;
	Math::Rectangle rect;
	Math::Color color;
	Bullet()
		: pos{ 0,0 }
		, move{ 0,0 }
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
		, transmat(Math::Matrix::Identity)
		, scalemat(Math::Matrix::Identity)
		, rotatemat(Math::Matrix::Identity)
		, mat(Math::Matrix::Identity)
		, rect{ 0,0,0,0 }
	    , color(1, 1, 1, 1)
	{
	}
};
class C_CharaBase
{
public:
	C_CharaBase() {}
	~C_CharaBase(){}

	virtual void Action() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	protected:
	KdTexture* m_tex;
	Math::Vector2 m_scale;
	Math::Matrix m_mat;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Rectangle m_rect;
	int m_hpMax;
	int m_hp;
	bool m_aliveFlg;
	const float turnDeg=5.0f;
};
