#pragma once

class C_Back
{
public:
	C_Back();
	~C_Back();

	void Init();
	void Update();
	void Draw();

	void SetBackTex(KdTexture* tex) { m_backTex = tex; }

private:
	KdTexture *m_backTex;
	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	Math::Matrix m_mat2;
	Math::Rectangle m_rect;
	float anim;
};

