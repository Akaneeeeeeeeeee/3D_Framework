#pragma once
#include <SimpleMath.h>

#include "../../../Framework/Buffer/VertexBuffer.h"
#include "../../../Framework/Buffer/IndexBuffer.h"
#include "../../../Framework/Shader/Shader.h"
#include "../../Camera/Camera.h"

class Object {
protected:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);	// Position(Translation)
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// 描画の為の情報（見た目に関わる部分）
	Shader m_Shader; // シェーダー

	// カメラ
	Camera* m_Camera;

public:

	Object(Camera* cam);	//! コンストラクタ
	virtual ~Object();		//! デストラクタ

	virtual void Init()=0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	// positionのセッターゲッター
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetPosition(void) const;
};
