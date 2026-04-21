#pragma once

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
	static const int enemyNum;
	bool enemyFlg;
	bool bulletFlg;
	Math::Vector2 bulletMove;

};
