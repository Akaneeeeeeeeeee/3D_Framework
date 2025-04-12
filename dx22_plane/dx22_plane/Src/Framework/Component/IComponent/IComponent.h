#pragma once
#include "../../../Entry/main.h"

/// <summary>
/// 全てのコンポーネントの元となるクラス
/// コンポーネントはそれをアタッチ（取りつけ）するオブジェクトがあるのでメンバ変数としてGameObjcetクラスのポインタを持つ
/// →それによってコンポーネントからアタッチしているオブジェクトにアクセスすることができる
/// </summary>

class Object;

class IComponent
{
public:
	IComponent(Object* _Owner) :m_pOwner(_Owner) {};
	virtual ~IComponent() { m_pOwner = nullptr; }

	virtual void Init(void) = 0;		// 初期化
	virtual void Update(void) = 0;		// 更新
	virtual void Uninit(void) = 0;		// 終了

	void SetOwner(Object& _obj);		// オブジェクトのアタッチ(参照渡し)
	Object* GetOwner(void);					// アタッチ先のオブジェクトの取得
	//void RemoveOwner(void);			// アタッチされているオブジェクトからの取り外し

protected:
	// コンポーネントマネージャがshared_ptrで管理してるので、ここで参照を使うとオブジェクトが消えた場合参照が消えてしまうのでNG→ポインタで管理
	// 参照→nullを使えない→オブジェクトの方が先に削除された場合、未定義動作になるかもなので×
	// unique,shared→コンポーネントがオブジェクトの主有権を持つ必要がないので×
	// →ポインタにする
	Object* m_pOwner;				// アタッチされているオブジェクトのポインタ(単一なのでunique_ptr？)
};



