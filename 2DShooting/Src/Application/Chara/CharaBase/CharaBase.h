#pragma once
struct bullet
{
	static const int Num = 2000;
	Math::Vector2 pos[Num];
	Math::Vector2 move[Num];
	bool Flg[Num];
	float Angle;
	int shotCnt;
	float moveAngle;
	float shotwait;
	float radius;
	float speed;
	float rad[Num];
	float ang[Num];
	float anim[Num];
	Math::Matrix transmat[Num];
	Math::Matrix scalemat[Num];
	Math::Matrix rotatemat[Num];
	Math::Matrix mat[Num];
	Math::Rectangle rect[Num];
	Math::Color color;
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

};
