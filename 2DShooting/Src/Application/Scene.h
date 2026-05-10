#pragma once

enum changeScene//シーン変更用
{
	Title,
	Game,
	Clear,
	GameOver
};


class Scene
{
private:

	// 現在のシーン
	int m_nowScene;
	bool m_enterFlg;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();


	void SetNowScene(int nowScene) { m_nowScene = nowScene; }

	bool GetKeyFlg() { return m_enterFlg; }
	void SetKeyFlg(bool flg) { m_enterFlg = flg; }

private:

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
