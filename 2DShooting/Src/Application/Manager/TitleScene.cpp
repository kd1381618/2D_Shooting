#include "TitleScene.h"
#include "../Scene.h"
#include "SceneManager.h"

void C_TitleScene::Init()
{

	m_titleTex.Load("texture/TitleScene/title.png");
	m_titleMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}
void C_TitleScene::ChangeUpdate()
{

}
void C_TitleScene::Update()
{




	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENE.SetNowScene(changeScene::Game);
		SCENEMANAGER.ChangeState(new C_GameScene());
	}

	
	


}
void C_TitleScene::Draw()
{



	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);



}


void C_TitleScene::Release()
{

	m_titleTex.Release();

}
