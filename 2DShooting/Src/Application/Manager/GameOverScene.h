#pragma once
#include "State.h"

class C_GameScene;

class C_GameOverScene : public C_State
{

public:
	C_GameOverScene() {}
	~C_GameOverScene() {}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;



private:
	C_GameScene* m_gameScene;
	KdTexture m_tex;
	Math::Matrix m_mat;
	KdTexture m_backTex;
	Math::Vector2 m_pos;
	Math::Rectangle m_rect;
	Math::Matrix m_backMat;
	Math::Matrix m_backMat2;
	unsigned long m_score;
	static const int maxDigits = 10;
	int m_digits[maxDigits] = {};
	KdTexture m_scoreTex;
	Math::Vector2 m_scorepos;
	KdTexture windowTex;
	Math::Matrix windowmat;


};
