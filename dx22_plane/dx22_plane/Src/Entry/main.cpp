#include    "main.h"
#include    "../Application/Application.h"
#include    "../Framework/DetectMemoryLeak/mydebugnew.h"

//=======================================
//エントリーポイント
//=======================================

#ifdef _DEBUG
//
#define new MYDEBUG_NEW
#endif

int main(void)
{
#if defined(DEBUG) || defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif//defined(DEBUG) || defined(_DEBUG)

    // アプリケーション実行
    Application app(SCREEN_WIDTH,SCREEN_HEIGHT);
    app.Run();

    return 0;
}