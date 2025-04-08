#include "DebugUI.h"

// デバッグ関数を格納する静的メンバ変数
std::vector<std::function<void(void)>> DebugUI::m_DebugFunction;

// ImGuiの初期化を行う関数
void DebugUI::Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    //! ImGuiの初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // キーボード操作を有効にする
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // ゲームパッド操作を有効にする

    // Dear ImGuiのスタイルを設定
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // プラットフォーム/レンダラーのバインディングを設定
    ImGui_ImplWin32_Init(Application::GetWindow());
    ImGui_ImplDX11_Init(_device, _deviceContext);
}

// デストラクタ：ImGuiの終了処理を行う
DebugUI::~DebugUI() {
    //! 終了
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// デバッグ関数を登録する関数
void DebugUI::RegisterDebugFunction(std::function<void(void)> _func)
{
    m_DebugFunction.push_back(std::move(_func));
}

// ImGuiのレンダリングを行う関数
void DebugUI::Render(void) {
    //! ImGuiの新しいフレームを開始
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //! ウィンドウとデバッグ情報の描画
    ImGui::Begin("Debug Information");
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average % 3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    //! デバッグ関数の実行
    for (auto& func : m_DebugFunction)
    {
        func();
    }

    //! フレームのレンダリングを完了
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
