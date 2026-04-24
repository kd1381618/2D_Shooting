#pragma once
#include "State.h"

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

	KdTexture m_tex;
	Math::Matrix m_mat;




};
