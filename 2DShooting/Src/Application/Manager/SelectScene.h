#pragma once
#include"State.h"

class C_SelectScene : public C_State
{
public:

	C_SelectScene() { Init(); }
	~C_SelectScene(){}

	void Init() override;
	void ChangeUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	KdTexture m_backTex;
	Math::Vector2 m_pos;
	Math::Rectangle m_rect;
	Math::Matrix m_backMat;
	Math::Matrix m_backMat2;

	KdTexture cannonTex;
	Math::Rectangle cannonrect;
	Math::Matrix m_cannontrans;
	Math::Vector2 cannonscale;
	Math::Matrix m_cannonmat;
	KdTexture cannonwindowTex;
	Math::Rectangle cannonwindowrect;
	Math::Matrix cannonwindowmat;

	KdTexture spacegunTex;
	Math::Rectangle spacegunrect;
	Math::Matrix m_spaceguntrans;
	Math::Vector2 spacegunscale;
	Math::Matrix m_spacegunmat;
	KdTexture spacegunwindowTex;
	Math::Rectangle spacegunwindowrect;
	Math::Matrix spacegunwindowmat;

	KdTexture rocketTex;
	Math::Rectangle rocketrect;
	Math::Matrix m_rockettrans;
	Math::Vector2 rocketscale;
	Math::Matrix m_rocketmat;
	KdTexture rocketwindowTex;
	Math::Rectangle rocketwindowrect;
	Math::Matrix rocketwindowmat;
	bool keyFlg;
	int SelectNum = 0;
	bool m_selectcannon;
	bool m_selectspacegun;
	bool m_selectrocket;
};
