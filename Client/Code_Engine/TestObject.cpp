#include "TestObject.h"
#include "ComponentHolder.h"
#include "box.h"
#include "Transform.h"
#include "Renderer.h"


CTestObject::CTestObject(shared_ptr<DxDevice> _device)
	: CGameObject::CGameObject(_device)
	,pBox(nullptr)
	, pTransform(nullptr)
	, pRenderer(nullptr)
{

}

CTestObject::~CTestObject()
{

}

HRESULT CTestObject::Init_GameObject(void)
{
	pTransform = CComponentHolder::GetInstance()->Clone_Component("Transform");
	((CTransform*)pTransform.get())->Init_Component();
	((CTransform*)pTransform.get())->SetPosition(0, 0, 0);
	pBox = CComponentHolder::GetInstance()->Clone_Component("Box");
	((CBox*)pBox.get())->Init_Component();
	pRenderer = CComponentHolder::GetInstance()->Clone_Component("Renderer");
	return S_OK;
}

int CTestObject::Update_GameObject(const std::shared_ptr<CTimer> t)
{
	((CTransform*)pTransform.get())->Update_Component(t);
	dynamic_cast<CRenderer*>(pRenderer.get())->Add_RenderList(CRenderer::RENDER_NONEALPHA, this->shared_from_this());
	//((CRenderer*)pRenderer.get())->Add_RenderList(CRenderer::RENDER_NONEALPHA, this->shared_from_this());
	
	return 0;
}

int CTestObject::LastUpdate_GameObject(const std::shared_ptr<CTimer> t)
{
	return 0;
}

void CTestObject::Render_GameObject()
{
	ComPtr<ID3D12Device> device = m_DxDevice->GetDevice();
	ComPtr<ID3D12GraphicsCommandList> cmdList = m_DxDevice->GetCommandList();
	cmdList->SetPipelineState(dynamic_cast<CBox*>(pBox.get())->GetPSO().Get());
	
	

}

void CTestObject::OnResize()
{

}

