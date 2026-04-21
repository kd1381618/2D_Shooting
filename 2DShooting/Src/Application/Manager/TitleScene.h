#pragma once
#include"State.h"

class C_TitleScene : public C_State
{
public:

	C_TitleScene(){}
	~C_TitleScene() {}


	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	float m_alpha;
	float m_gradation;

	KdTexture m_titleTex;
	Math::Matrix m_titleMat;

	KdTexture m_pressEnterTex;
	Math::Matrix m_pressEnterMat;

};