#pragma once
#include "State.h"

class C_ClearScene : public C_State
{

public:
	C_ClearScene() {}
	~C_ClearScene() {}

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;



private:

	KdTexture m_tex;
	Math::Matrix m_mat;




};

