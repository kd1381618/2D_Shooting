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
	void SetTableTex(KdTexture* tex) { m_tableTex = tex; }

private:

	C_GameScene* m_gameScene;

	KdTexture* m_tex;
	KdTexture* m_tableTex;
	Math::Matrix m_tablemat;
	Math::Matrix m_transmat;
	Math::Matrix m_scalemat;
	Math::Matrix m_mat;
	Math::Rectangle m_rect;
	Math::Rectangle m_tablerect;
	float hpanim;
};

