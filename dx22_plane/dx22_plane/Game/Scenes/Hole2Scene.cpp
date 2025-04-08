#include "Hole2Scene.h"
#include "Game.h"
#include "GolfBall.h"
#include "Ground.h"
#include "Texture2D.h"
#include "Arrow.h"
#include "Pole.h"
#include "Sphere.h"

using namespace DirectX::SimpleMath;

// コンストラクタ
Hole2Scene::Hole2Scene()
{
	Init();
}

// デストラクタ
Hole2Scene::~Hole2Scene()
{
	Uninit();
}

// 初期化
void Hole2Scene::Init()
{

	m_Par = 4;			// パー（標準打数）を設定
	m_StrokeCount = 0;	// 現在打数を初期化

	// オブジェクトを作成
	Ground* ground = Game::GetInstance()->AddObject<Ground>();
	ground->SetImage("assets/texture/Hole2.jpg");	// 地形を設定
	m_MySceneObjects.emplace_back(ground);					// 地面


	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<GolfBall>());	// ゴルフボール
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Arrow>());		// 矢印
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Pole>());		// ポール

	// UI（背景）
	Texture2D* pt1 = Game::GetInstance()->AddObject<Texture2D>();
	pt1->SetTexture("assets/texture/ui_back.png");		// 画像を指定
	pt1->SetPosition(-475.0f, -300.0f, 0.0f);			// 位置を指定
	pt1->SetScale(270.0f, 75.0f, 0.0f);					// 大きさを指定
	m_MySceneObjects.emplace_back(pt1);

	// UI（パー）
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/ui_string.png");	// 画像を指定
	pt2->SetPosition(-575.0f, -245.0f, 0.0f);			// 位置を指定
	pt2->SetScale(60.0f, 45.0f, 0.0f);					// 大きさを指定
	pt2->SetUV(1, 1, 2, 1);								// UVを指定
	m_MySceneObjects.emplace_back(pt2);

	// UI（打目）
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/ui_string.png");	// 画像を指定
	pt3->SetPosition(-400.0f, -305.0f, 0.0f);			// 位置を指定
	pt3->SetScale(105.0f, 63.0f, 0.0f);					// 大きさを指定
	pt3->SetUV(2, 1, 2, 1);								// UVを指定
	m_MySceneObjects.emplace_back(pt3);

	// UI（パーの数値）
	Texture2D* pt4 = Game::GetInstance()->AddObject<Texture2D>();
	pt4->SetTexture("assets/texture/number.png");		// 画像を指定
	pt4->SetPosition(-510.0f, -245.0f, 0.0f);			// 位置を指定
	pt4->SetScale(65.0f, 45.0f, 0.0f);					// 大きさを指定
	pt4->SetUV(m_Par + 1, 1, 10, 1);					// UVを指定
	m_MySceneObjects.emplace_back(pt4);

	// UI（現在打数：一の位）
	Texture2D* pt5 = Game::GetInstance()->AddObject<Texture2D>();
	pt5->SetTexture("assets/texture/number.png");		// 画像を指定
	pt5->SetPosition(-490.0f, -300.0f, 0.0f);			// 位置を指定
	pt5->SetScale(95.0f, 72.0f, 0.0f);					// 大きさを指定
	pt5->SetUV(2, 1, 10, 1);							// UVを指定
	m_MySceneObjects.emplace_back(pt5);

	// UI（現在打数：十の位）
	Texture2D* pt6 = Game::GetInstance()->AddObject<Texture2D>();
	pt6->SetTexture("assets/texture/number.png");		// 画像を指定
	pt6->SetPosition(-565.0f, -300.0f, 0.0f);			// 位置を指定
	pt6->SetScale(95.0f, 72.0f, 0.0f);					// 大きさを指定
	pt6->SetUV(1, 1, 10, 1);							// UVを指定
	m_MySceneObjects.emplace_back(pt6);

	// UI（背景）
	Texture2D* pt7 = Game::GetInstance()->AddObject<Texture2D>();
	pt7->SetTexture("assets/texture/ui_back.png");		// 画像を指定
	pt7->SetPosition(-735.0f, 490.0f, 0.0f);			// 位置を指定
	pt7->SetScale(430.0f, 100.0f, 0.0f);					// 大きさを指定
	m_MySceneObjects.emplace_back(pt7);

	// 第〇ホール
	Texture2D* pt8 = Game::GetInstance()->AddObject<Texture2D>();
	pt8->SetTexture("assets/texture/HoleNumber.png");	// 画像を指定
	pt8->SetPosition(-735.0f, 490.0f, 0.0f);			// 位置を指定
	pt8->SetScale(430.0f, 100.0f, 0.0f);					// 大きさを指定
	pt8->SetUV(1, 1, 1, 1);								// UVを指定
	m_MySceneObjects.emplace_back(pt8);

	// ホール数
	Texture2D* pt9 = Game::GetInstance()->AddObject<Texture2D>();
	pt9->SetTexture("assets/texture/number.png");	// 画像を指定
	pt9->SetPosition(-815.0f, 495.0f, 0.0f);			// 位置を指定
	pt9->SetScale(50.0f, 100.0f, 0.0f);					// 大きさを指定
	pt9->SetUV(3, 1, 10, 1);							// UVを指定
	m_MySceneObjects.emplace_back(pt9);

	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Sphere>());	// スカイドーム



	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[1]);		// ゴルフボール
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);			// 矢印
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);				// ポール

	ball->SetState(0);		// ボールを物理挙動させる
	arrow->SetState(0);		// 矢印を非表示
	pole->SetPosition(20.0f, 0.0f, -40.0f);		// ポールの場所を設定


}

//更新
void Hole2Scene::Update()
{
	//// シーン遷移処理中ではない場合、シーンの更新
	//if (!Game::GetInstance()->GetChange() && !Game::GetInstance()->GetChanging())
	//{
	//	
	//}
	//// シーン遷移処理中の場合
	//else if (Game::GetInstance()->GetChanging()&& Game::GetInstance()->GetChange())
	//{
	//	//Game::GetInstance()->
	//}
	//else
	//{
	//	// フェードアウト処理
	//}


	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[1]);	// ゴルフボール
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);		// 矢印

	// 状態ごとに処理
	switch (m_State)
	{
		// ボール移動中
	case 0:
		// ボールが静止したら
		if (ball->GetState() == 1)
		{
			m_State = 1;
			arrow->SetState(m_State);

			// 打数を更新
			Texture2D* count[2];
			count[0] = dynamic_cast<Texture2D*>(m_MySceneObjects[8]);
			count[1] = dynamic_cast<Texture2D*>(m_MySceneObjects[9]);

			m_StrokeCount++;	// 現在打数をカウントアップ

			// 各桁を後ろから取得していく
			for (int i = 0; i < 2; i++)
			{
				// 一桁取り出す
				int cnt = m_StrokeCount % (int)pow(10, i + 1) / (int)pow(10, i);

				// UVを設定
				count[i]->SetUV(cnt + 1, 1, 10, 1);
			}
		}
		// ボールがカップインしたらリザルトへ
		if (ball->GetState() == 2)
		{
			Game::GetInstance()->ChangeScene(HOLE3);
		}
		break;
		// 方向選択中
	case 1:
		// スペースキーでパワー選択へ
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 2;
			arrow->SetState(m_State);
		}
		break;
		// 角度選択中
	case 2:
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 3;
			//ball->SetState(m_State);
			arrow->SetState(m_State);


		}
		break;
		// パワー選択中
	case 3:
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 0;
			ball->SetState(m_State);
			arrow->SetState(m_State);

			// 強さを設定
			Vector3 v = arrow->GetVector();
			v *= 1.25f;
			ball->Shot(v);
		}
		break;
	default:
		break;
	}

	// エンターキーを押してタイトルへ
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(HOLE3);
	}

}

// 終了処理
void Hole2Scene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

// スコアを取得
int Hole2Scene::GetScore(void)
{
	// 現在打数から標準打数を引いた値を返す
	return (m_StrokeCount - m_Par);
}

int Hole2Scene::GetTargetScore(void)
{
	return m_Par;
}
