#pragma once
#include"../Item/ItemBase.h"
class C_GameScene;

class C_Medkit :public C_ItemBase
{
public:
	C_Medkit();
	~C_Medkit()override {}

	void Init()override;
	void Update()override;
	void Draw()override;
	void SetTex(KdTexture* tex) { m_tex = tex; }
	void SetPos( Math::Vector2 pos) { m_pos = pos; }
	float GetRadius()const { return 32.0f; }

private:

	C_GameScene* m_gameScene;
	

};
