#pragma once
#include <iostream>
#include "FadeAnimation.h"
#include "Camera.h"
#include "Input.h"
#include "TitleScene.h"
#include "Hole1Scene.h"
#include "Hole2Scene.h"
#include "Hole3Scene.h"
#include "ResultScene.h"

enum SceneName {
	TITLE,
	HOLE1,
	HOLE2,
	HOLE3,
	/*HOLE4,
	HOLE5,
	HOLE6,
	HOLE7,
	HOLE8,
	HOLE9,*/
	BONUS,
	RESULT
};

class Game
{
public:



private:
	//! ゲームクラスからオブジェクトにアクセスしやすくするためにゲームクラスのインスタンスをゲームクラス自身に持たせる
	//! →そうするとゲッター関数でどこからでもObjectsにアクセスすることができる（？）
	static Game* m_Instance; // ゲームインスタンス

	Scene* m_Scene; // シーン

	std::vector<std::unique_ptr<Object>> m_Objects; // オブジェクト
	std::unique_ptr<Input> m_Input;  // 入力処理
	std::unique_ptr<Camera> m_Camera; // カメラ

	bool Change = false;		// シーン切り替えフラグ
	bool Changing = false;		// シーン遷移中管理フラグ
	//std::unique_ptr<FadeAnimation> m_FadeAnimation;
	SceneName m_NextSceneName;	// 次シーンの名前

public:
	Game(); // コンストラクタ
	~Game(); // デストラクタ

	static void Init(); // 初期化
	static void Update(); // 更新
	static void Draw(); // 描画
	static void Uninit(); // 終了処理
	
	static Game* GetInstance();
	void SetChange(bool _flg);		// 後から追加
	bool GetChange(void);			// 後から追加
	void SetChanging(bool _flg);	// 後から追加
	bool GetChanging(void);			// 後から追加

	void ChangeScene(SceneName sName);	// シーンを変更
	Camera& GetCamera();				// カメラ取得
	void DeleteObject(Object* pt);		// オブジェクトを削除する
	void DeleteAllObject();				// オブジェクトをすべて削除する

	// オブジェクトを追加する(※テンプレート関数なのでここに直接記述)
	template<class T> T* AddObject()
	{
		T* pt = new T(m_Camera.get());
		m_Instance->m_Objects.emplace_back(pt);
		pt->Init(); // 初期化
		return pt;
	}

	// オブジェクトを取得する(※テンプレート関数なのでここに直接記述)
	template<class T> std::vector<T*> GetObjects()
	{
		std::vector<T*> res;
		for (auto& o : m_Instance->m_Objects) {
			// dynamic_castで型をチェック
			if (T* derivedObj = dynamic_cast<T*>(o.get())) {
				res.emplace_back(derivedObj);
			}
		}
		return res;
	}

};
