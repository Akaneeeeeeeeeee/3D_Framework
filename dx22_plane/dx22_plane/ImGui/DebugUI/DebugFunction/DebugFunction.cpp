#include "DebugFunction.h"
#include "../DebugUI.h"
#include "../../../GolfBall.h"


namespace DebugFunction {
	//! プレイヤー情報表示
	void DebugPlayer(void) {
		ImGui::Begin("Debug Player");
		ImGui::Text("Position: %f %f %f",GolfBall::Object::GetPosition().x)
	}

	//! プレイヤー制御用スライダー
	void DebugPlayerSlider(void);
}
