#pragma once

class C_GameScene;

class C_PlayerHp
{
public:
	C_PlayerHp();
	~C_PlayerHp() {}

	void Init();
	void Update();
	void Draw();

	void SetTex(KdTexture* tex) { m_tex = tex; }

private:

	C_GameScene* m_gameScene;

	KdTexture* m_tex;
	Math::Matrix m_transmat;
	Math::Matrix m_scalemat;
	Math::Matrix m_mat;
	Math::Rectangle m_rect;
	float hpanim;
};

