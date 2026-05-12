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

	KdTexture m_backTex;
	Math::Vector2 m_pos;
	Math::Rectangle m_rect;
	Math::Matrix m_backMat;
	Math::Matrix m_backMat2;

	KdTexture m_titleTex;
	Math::Rectangle m_titlerect;
	Math::Matrix m_titlemat;

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