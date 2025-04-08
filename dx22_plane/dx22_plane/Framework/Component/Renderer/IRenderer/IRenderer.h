#pragma once
#include "../../IComponent/IComponent.h"


/**
 * @brief レンダラー系コンポーネントを識別するためのインターフェースクラス
*/
class IRenderer:public IComponent
{
public:
	IRenderer();
	IRenderer(Object* _Owner) :IComponent(_Owner) {};

	~IRenderer() {};

	virtual void Render(void) = 0;

private:

};

