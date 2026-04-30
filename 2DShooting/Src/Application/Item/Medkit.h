#pragma once

class C_GameScene;

class C_Medkit
{
public:
	C_Medkit();
	~C_Medkit() {}

	void Init();
	void Update();
	void Draw();
	void SetTex(KdTexture* tex) { m_tex = tex; }
	void SetPos(int i, Math::Vector2 pos) { m_pos[i] = pos; }
	void SetFlg(int i, bool flg) { Flg[i] = flg; }
	bool GetFlg(int i) { return Flg[i]; }
	int GetNum() { return MedkitNum; }

private:

	C_GameScene* m_gameScene;

	static const int MedkitNum = 3;
	bool Flg[MedkitNum];
	Math::Vector2 m_pos[MedkitNum];
	KdTexture* m_tex;
	Math::Matrix m_trans[MedkitNum];
	Math::Matrix m_scale[MedkitNum];
	Math::Matrix m_mat[MedkitNum];
	Math::Rectangle m_rect[MedkitNum];
	float anim[MedkitNum];
};
