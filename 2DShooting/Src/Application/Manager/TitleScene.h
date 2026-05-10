#pragma once
#include"State.h"

class C_TitleScene : public C_State
{
public:

	C_TitleScene(){}
	~C_TitleScene() {}


	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:


	float m_alpha;
	float m_gradation;

	KdTexture m_titleTex;
	Math::Vector2 m_pos;
	Math::Rectangle m_rect;
	Math::Matrix m_titleMat;
	Math::Matrix m_titleMat2;

	KdTexture m_startTex;
	Math::Matrix m_startMat;
	Math::Vector2 m_startscale;
	Math::Rectangle m_startrect;

	KdTexture m_exitTex;
	Math::Matrix m_exitMat;
	Math::Vector2 m_exitscale;
	Math::Rectangle m_exitrect;

	bool keyFlg;
	int SelectNum=0;
	bool m_goGame;
	bool m_goExit;
};