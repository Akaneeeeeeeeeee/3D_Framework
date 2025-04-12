#include "../../../Entry/main.h"
#include "IComponent.h"


// そのコンポーネントを持つオブジェクトの割り当て(引数：オブジェクト(参照))
void IComponent::SetOwner(Object& _obj) {
	// 参照したオブジェクトのアドレスを&で代入
	m_pOwner = &_obj;
}

// アタッチ先のオブジェクトの取得
Object* IComponent::GetOwner(void) {
	return m_pOwner;
}

