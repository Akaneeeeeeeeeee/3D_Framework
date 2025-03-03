#include "Object.h"

using namespace DirectX::SimpleMath;

/**
 * @brief コンストラクタ
 * @param cam カメラのポインタ
*/
Object::Object(Camera* cam) :m_Camera(cam) {

}

/**
 * @brief デストラクタ
*/
Object::~Object() {

}

// Positionセッター
void Object::SetPosition(const Vector3& _pos) {
	m_Position.x = _pos.x;
	m_Position.y = _pos.y;
	m_Position.z = _pos.z;
}

/*
* 関数の後ろにconstがつく場合→その関数内でメンバ変数を書き換える（編集する）権限を無くすことができる
* →保守性が上がり、その部分でメンバ変数が書き換えられていないことの証明ができる
*/
// Positionゲッター
Vector3 Object::GetPosition(void) const {
	return m_Position;
}

//今のところ記述内容は無し



