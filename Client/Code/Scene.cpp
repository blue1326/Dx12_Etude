#include "Scene.h"
CScene::CScene()
{

}

CScene::~CScene()
{

}

void CScene::SetActiveState(bool state)
{
	isActive = state;
}

void CScene::AddGameObject(std::shared_ptr<CGameObject> obj)
{
	m_Objects.push_back(obj);
}

void CScene::OnResize()
{
	
	for (const auto &j : m_Objects)
	{
			j->OnResize();
	}
}

