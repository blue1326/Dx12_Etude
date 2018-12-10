#include "Renderer.h"
#include "dxException.h"
CRenderer::CRenderer(const std::shared_ptr<DxDevice> Device)
	:m_DxDevice(Device)
{
	m_CType = COMP_SHARED;
}

CRenderer::~CRenderer()
{

}

HRESULT CRenderer::Init_Component()
{
	

	return S_OK;
}

void CRenderer::Update_Component(const std::shared_ptr<CTimer> t)
{

}

void CRenderer::Render_GameObject(void)
{
	RenderNoneAlpha();
	Clear_RenderList();
}

void CRenderer::RenderNoneAlpha(void)
{
	for (const auto &j : m_RenderList[RENDER_NONEALPHA])
	{
		j->Render_GameObject();
	}
}
std::shared_ptr<CComponent> CRenderer::Clone()
{
	return this->shared_from_this();
}

HRESULT CRenderer::Add_RenderList(RENDER eType, shared_ptr<CGameObject> object)
{
	if (nullptr == object)
		return E_FAIL;
	m_RenderList[eType].push_back(object);
	return S_OK;
}

void CRenderer::Clear_RenderList()
{
	for (unsigned long i = 0; i < RENDER_END; ++i)
	{
		RENDERLIST::iterator erBegin = m_RenderList[i].begin();
		RENDERLIST::iterator erEnd = m_RenderList[i].end();
		m_RenderList[i].erase(erBegin, erEnd);
		m_RenderList[i].clear();
	}
}