#pragma once
#include"TitleScene.h"
#include"GameScene.h"
#include"ClearScene.h"
#include"GameOverScene.h"

class C_SceneManager
{
public:

	~C_SceneManager(){}

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

	void ChangeState(C_State* newState)
	{

		if(m_currentState != nullptr) m_currentState->Release();

		delete m_currentState;
		m_currentState = newState;

		m_currentState->Init();

	}

	void Init()
	{
		m_currentState->Init();

	}
	void ChangeUpdate()
	{
		m_currentState->ChangeUpdate();
	}

	void Update()
	{
		m_currentState->Update();
	}

	void Draw()
	{
		m_currentState->Draw();
	}


	void Release()
	{
		m_currentState->Release();
	}

	C_State* GetCurrentState() { return m_currentState; }
	bool m_exit = false;

	void ExitApp() { m_exit = true; }
private:

	C_SceneManager() {}

	C_State* m_currentState = nullptr;


};

#define SCENEMANAGER C_SceneManager::GetInstance()