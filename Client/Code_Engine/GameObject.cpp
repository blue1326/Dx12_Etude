#include "GameObject.h"

CGameObject::CGameObject(shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
<<<<<<< HEAD
=======
	,m_ElementByteSize(0)
	,m_MappedData(nullptr)
	,m_CbvHeap(nullptr)
>>>>>>> parent of e7d7f92... Revert "minorupdate"
{

}

CGameObject::~CGameObject()
{

}

void CGameObject::Free(void)
{

}


