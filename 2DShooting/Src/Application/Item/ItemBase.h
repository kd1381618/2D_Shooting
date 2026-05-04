#pragma once

class C_ItemBase
{
public:
	C_ItemBase(){}
	virtual~C_ItemBase(){}

	virtual void Init()=0;
	virtual void Update()=0;
	virtual void Draw()=0;

	bool IsAlive() const { return m_alive; }
	void SetAlive(bool alive) { m_alive = alive; }
	void SetPos(Math::Vector2& p) { m_pos = p; }
protected:
	bool m_alive;
	Math::Vector2 m_pos;
	KdTexture* m_tex;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	Math::Matrix m_mat;
	Math::Rectangle m_rect;
	float anim;
};

