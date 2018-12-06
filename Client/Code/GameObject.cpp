#include "GameObject.h"

CGameObject::CGameObject()
{

}

CGameObject::~CGameObject()
{

}
//
//void CGameObject::AddComponent(std::string ComponentTag, std::shared_ptr<CComponent> component)
//{
//	m_Components.insert(COMPONENT::value_type(ComponentTag, component));
//}

//void CGameObject::AddComponent(eCOMPONENTS comptag, std::shared_ptr<CComponent> component)
//{
//	switch (comptag)
//	{
//	case COMPONENT_RENDERER:
//		m_ComponentArr[COMPONENT_RENDERER] = component;
//		break;
//	case COMPONENT_TRANSFORM:
//		m_ComponentArr[COMPONENT_TRANSFORM] = component;
//		break;
//	}
//}

void CGameObject::OnResize()
{
	/*for (const auto &j : m_ComponentArr)
	{
		if (j)
		j->OnResize();
	}*/
}

