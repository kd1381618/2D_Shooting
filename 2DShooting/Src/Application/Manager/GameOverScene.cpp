#include "GameOverScene.h"
#include "../Scene.h"
#include "SceneManager.h"




void C_GameOverScene::Draw()
{



}


void C_GameOverScene::Update()
{


	if(GetAsyncKeyState('T') & 0x8000)//enterキーでタイトルへ戻る
	{
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
	if (GetAsyncKeyState('R') & 0x8000)//リトライ
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}




}
void C_GameOverScene::Init()
{


}

void C_GameOverScene::Release()
{

}