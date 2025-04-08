#pragma once
#include "Transform.h"
#include "../../../Game/EntryPoint/main.h"

using namespace SimpleMath;

// TODO:2024/11/27 これ構造体でいい説！！！！！！！
// →Transformはあくまでデータの取りまとめ→わざわざクラスにして継承させてしまうと親子関係が深くなりすぎて絶対ややこしくなるからこれはやめるべき
// クラステンプレートとか標準ライブラリ、スマートポインタの勉強も必要かも std::vectorとかでコンポーネントを好きなだけつけれるとかできそう

/// <summary>
/// Transformクラス：全てのオブジェクトが持っている情報（ここでは数値のみを扱う）
/// ・座標
/// ・回転
/// ・大きさ
/// の情報を持つ
/// 
/// 各数値の行列変換は毎フレーム行う→更新は不要
/// ワールド行列への変換はTransform内で行う
/// </summary>

struct Transform
{
public:
	Transform() :m_Position(0.0f, 0.0f, 0.0f), m_Rotation(0.0f, 0.0f, 0.0f), m_Scale(75.0f, 75.0f, 0.0f) {};
	~Transform() {};
	
	// 更新するべきなのはコンポーネントなのでここに更新はいらない？
	// →conioのvectorとかと同じノリ？
	Vector3 m_Position;	// 座標
	Vector3 m_Rotation;	// 角度
	Vector3 m_Scale;	// 大きさ
};

