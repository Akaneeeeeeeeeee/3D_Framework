#pragma once

#include <d3d11.h>
#include <vector>
#include <functional>
#include "../../Application.h"

#include "../imgui.h"
#include "../imgui_impl_dx11.h"
#include "../imgui_impl_win32.h"

class DebugUI
{
	static std::vector<std::function<void(void)>> m_DebugFunction;
public:
	static void Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);
	
	//! デバッグ表示関数の登録
	static void RegisterDebugFunction(std::function<void()> _func);

	static void Render(void);

	DebugUI();

	virtual ~DebugUI();

private:

};

