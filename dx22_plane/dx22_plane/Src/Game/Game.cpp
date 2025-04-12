#include "Game.h"
#include "../Framework/Renderer/Renderer.h"
#include "../Framework/Texture/Texture2D.h"
#include "../Framework/Texture/FadeAnimation.h"
#include "../Framework/ImGui/DebugUI/DebugUI.h"
#include "Scenes/TitleScene.h"
#include "Scenes/Hole1Scene.h"
#include "Scenes/Hole2Scene.h"
#include "Scenes/Hole3Scene.h"
#include "Scenes/ResultScene.h"

Game* Game::m_Instance;

// コンストラクタ
Game::Game()
{
	m_Input = std::make_unique<Input>(); //入力処理を作成
	m_Camera = std::make_unique<Camera>(); //カメラを作成
}

// デストラクタ
Game::~Game()
{
	delete m_Scene;
}

// 初期化
void Game::Init()
{
	// オブジェクト作成
	m_Instance = new Game;

	// 描画初期化
	Renderer::Init();
	//! デバッグUI初期化
	//DebugUI::Init(Renderer::GetDevice(), Renderer::GetDeviceContext());


	// オブジェクト配列作成
	//m_Instance->m_Objects.emplace_back(new GolfBall);
	
	// カメラ初期化
	m_Instance->m_Camera->Init();

	m_Instance->m_Scene = new TitleScene; //メモリを確保

	/*m_Instance->m_FadeAnimation = std::make_unique<FadeAnimation>(m_Instance->m_Camera.get());
	m_Instance->m_FadeAnimation->SetTexture("assets/texture/ui_back.png");
	m_Instance->m_FadeAnimation->SetPosition(0.0f, 0.0f, 0.0f);
	m_Instance->m_FadeAnimation->SetScale(1920.0f, 1080.0f, 0.0f);*/

			
	// オブジェクト初期化
	// (※AddObject関数で実行するように変更）
	//for (auto& o : m_Instance->m_Objects)
	//{
	//	o->Init();
	//}
}

// 更新
// シーンが始まると同時に始まったシーンがフェードイン、終わったシーンがフェードアウトを担当する
void Game::Update()
{
	//// フェードアニメーションの更新
	//if (m_Instance->m_FadeAnimation->GetIsPlaying())
	//{
	//	m_Instance->m_FadeAnimation->Update();

	//	// フェードアウトが完了したらシーン変更
	//	if (!m_Instance->m_FadeAnimation->GetIsPlaying() && m_Instance->Changing)
	//	{
	//		// シーン遷移処理
	//		if (m_Instance->m_NextSceneName == TITLE)
	//		{
	//			m_Instance->ChangeScene(HOLE1);
	//		}
	//		else if (m_Instance->m_NextSceneName == HOLE2)
	//		{
	//			m_Instance->ChangeScene(HOLE3);
	//		}

	//		m_Instance->m_FadeAnimation->StartFadeIn(); // フェードイン開始
	//		m_Instance->Changing = false; // フラグリセット
	//	}

	//	return; // フェード中は他の更新を行わない
	//}
	//else
	//{
	//	
	//}
	

	// シーン更新
	m_Instance->m_Scene->Update();

	// カメラ更新
	m_Instance->m_Camera->Update();

	// 入力処理更新
	m_Instance->m_Input->Update();

	// オブジェクト更新
	for (auto& o : m_Instance->m_Objects)
	{
		o->Update();
	}
	
}



// 描画
void Game::Draw()
{
	// 描画前処理
	Renderer::Begin();

	/*DirectX::SimpleMath::Vector4 col;
	if (m_Instance->Changing)
	{
		m_Instance->m_FadeAnimation->Update();
	}
	else
	{
		
	}*/
	
	//! デバッグUIの描画
	//DebugUI::Render();

	// カメラ描画
	m_Instance->m_Camera->Draw();

	// オブジェクト描画
	for (auto& o : m_Instance->m_Objects)
	{
		o->Draw();
	}

	// 描画後処理
	Renderer::End();
}

// 終了処理
void Game::Uninit()
{
	//オブジェクトを全て削除
	m_Instance->DeleteAllObject();

	// オブジェクト終了処理
 	// (※DeleteObject関数で実行するように変更）
	//for (auto& o : m_Instance->m_Objects)
	//{
	//	o->Uninit();
	//}

	// カメラ終了処理
	m_Instance->m_Camera->Uninit();

	// 描画終了処理
	Renderer::Uninit();
}

// インスタンスを取得
Game* Game::GetInstance()
{
	return m_Instance;
}

// カメラを取得する
Camera& Game::GetCamera()
{
	return *(m_Instance->m_Camera);
}

// シーン切り替えフラグ設定
void Game::SetChange(bool _flg)
{
	Change = _flg;
}

bool Game::GetChange(void)
{
	return Change;
}

void Game::SetChanging(bool _flg)
{
	Changing = _flg;
}

bool Game::GetChanging(void)
{
	return Changing;
}


// シーンを切り替える
void Game::ChangeScene(SceneName sName)
{
	// 読み込み済みのシーンがあれば削除
	static int score = 0;
	if (m_Instance->m_Scene != nullptr)
	{
		int temp = 0;
		// 消そうとしているシーンがStage1ならスコアを保存しておく
		if (m_NextSceneName == HOLE2)
		{
			Hole1Scene* sObj = dynamic_cast<Hole1Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// 目標スコア-実際のスコアが得点

			// スコアが0を超えた→打数オーバーの場合
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// 目標スコア-実際のスコアが得点
			}

			score += temp;
		}
		else if (m_NextSceneName == HOLE3)
		{
			Hole2Scene* sObj = dynamic_cast<Hole2Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// 目標スコア-実際のスコアが得点

			// スコアが0を超えた→打数オーバーの場合
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// 目標スコア-実際のスコアが得点
			}

			score += temp;
		}
		else if (m_NextSceneName == RESULT)
		{
			Hole3Scene* sObj = dynamic_cast<Hole3Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// 目標スコア-実際のスコアが得点

			// スコアが0を超えた→打数オーバーの場合
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// 目標スコア-実際のスコアが得点
			}

			score += temp;
		}

		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLE:
		// スコアをリセット
		score = 0;
		m_Instance->m_Scene = new TitleScene; // メモリを確保
		m_Instance->m_NextSceneName = HOLE1;
		break;
	case HOLE1:
		m_Instance->m_Scene = new Hole1Scene; // メモリを確保
		m_Instance->m_NextSceneName = HOLE2;
		break;
	case HOLE2:
		m_Instance->m_Scene = new Hole2Scene; // メモリを確保
		m_Instance->m_NextSceneName = HOLE3;
		break;
	case HOLE3:
		m_Instance->m_Scene = new Hole3Scene; // メモリを確保
		m_Instance->m_NextSceneName = RESULT;
		break;
	case RESULT:
		m_Instance->m_Scene = new ResultScene; // メモリを確保
		dynamic_cast<ResultScene*>(m_Instance->m_Scene)->SetScore(score);	// スコアを設定
		m_Instance->m_NextSceneName = TITLE;
		break;
	}
}

// オブジェクトを削除する
void Game::DeleteObject(Object* pt)
{
	if (pt == NULL) return;

	pt->Uninit(); // 終了処理

	// 要素を削除
	m_Instance->m_Objects.erase(
		std::remove_if(
			m_Instance->m_Objects.begin(),
			m_Instance->m_Objects.end(),
			[pt](const std::unique_ptr<Object>& element) {return element.get() == pt; }),
		m_Instance->m_Objects.end());
	m_Instance->m_Objects.shrink_to_fit();
}

// オブジェクトをすべて削除する
void Game::DeleteAllObject()
{
	// オブジェクト終了処理
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	m_Instance->m_Objects.clear(); //全て削除
	m_Instance->m_Objects.shrink_to_fit();
}

