#pragma once
#include "../../../Entry/main.h"


using namespace DirectX::SimpleMath;

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
	Transform() :Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(75.0f, 75.0f, 0.0f) {};
	Transform(const Vector3& _pos, const Vector3& _rot, const Vector3& _scale) : Position(_pos), Rotation(_rot), Scale(_scale) {};
	~Transform() {};
	
	// 更新するべきなのはコンポーネントなのでここに更新はいらない？
	// →conioのvectorとかと同じノリ？
	Vector3 Position;	// 座標
	Vector3 Rotation;	// 角度
	Vector3 Scale;	// 大きさ
};

