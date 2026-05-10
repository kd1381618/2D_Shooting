#pragma once
#include "State.h"

class C_ClearScene : public C_State
{

public:
	C_ClearScene(unsigned long score) : m_finalScore(score) {}
	~C_ClearScene() {}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;



private:

	KdTexture m_tex;
	Math::Matrix m_mat;
	KdTexture m_backTex;
	Math::Vector2 m_pos;
	Math::Rectangle m_rect;
	Math::Matrix m_backMat;
	Math::Matrix m_backMat2;
	unsigned long m_score;
	static const int maxDigits = 6;
	int m_digits[maxDigits] = {};
	KdTexture m_scoreTex;
	Math::Vector2 m_scorepos;
	KdTexture windowTex;
	Math::Matrix windowmat;
	KdTexture homeTex;
	KdTexture returnTex;
	Math::Matrix homemat;
	Math::Matrix returnmat;
	Math::Vector2 homescale;
	Math::Vector2 returnscale;
	Math::Rectangle buttonrect;
	unsigned long m_finalScore = 0;
	bool keyFlg;
	int SelectNum = 0;

	bool m_goGame;
	bool m_goTitle;


};

