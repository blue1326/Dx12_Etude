#include "TestObject2.h"
#include "ComponentHolder.h"
#include "box.h"
#include "Transform.h"
#include "Renderer.h"
#include "BasicMesh_Crate.h"
#include "Material.h"

//test
//#include "dxException.h"
CTestObject2::CTestObject2(shared_ptr<DxDevice> _device)
	: CGameObject::CGameObject(_device)
	,pBox(nullptr)
	, pTransform(nullptr)
	, pRenderer(nullptr)
	, pCrate(nullptr)
	, pMaterial(nullptr)
{

}

CTestObject2::~CTestObject2()
{

}

HRESULT CTestObject2::Init_GameObject(void)
{
	m_DescriptorSize = m_DxDevice->GetDevice().Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	pTransform = CComponentHolder::GetInstance()->Clone_Component("Transform");
	((CTransform*)pTransform.get())->Init_Component();
	((CTransform*)pTransform.get())->SetPosition(0, 0, 0);
	((CTransform*)pTransform.get())->SetScale(2);
	pBox = CComponentHolder::GetInstance()->Clone_Component("Box");
	((CBox*)pBox.get())->Init_Component();
	pRenderer = CComponentHolder::GetInstance()->Clone_Component("Renderer");
	
	pCrate = CComponentHolder::GetInstance()->Clone_Component("Basic_Crate");

	pMaterial = CComponentHolder::GetInstance()->Clone_Component("Tex_Crate");
	static_cast<CMaterial*>(pMaterial.get())->Ready_Component();

	//Init_Start();
	BuildDescriptorHeaps();
	static_cast<CMaterial*>(pMaterial.get())->SetUpDescripterHeap(m_CbvHeap);
	BuildConstantBuffers();
	//Init_End();

	return S_OK;
}

int CTestObject2::Update_GameObject(const std::shared_ptr<CTimer> t)
{
	((CTransform*)pTransform.get())->Update_Component(t);

	UpdateOjbectConstant();
	UpdatePassConstant(t);

	dynamic_cast<CMaterial*>(pMaterial.get())->Update_Component(t);
	


	//dynamic_cast<CBox*>(pBox.get())->Update_Component(t);
	dynamic_cast<CRenderer*>(pRenderer.get())->Add_RenderList(CRenderer::RENDER_NONEALPHA, this->shared_from_this());
	//((CRenderer*)pRenderer.get())->Add_RenderList(CRenderer::RENDER_NONEALPHA, this->shared_from_this());
	
	return 0;
}


void CTestObject2::UpdatePassConstant(const std::shared_ptr<CTimer> t)
{
	

	XMMATRIX view = g_matView;//XMLoadFloat4x4(&mView);
	XMMATRIX proj = g_matProj;// XMLoadFloat4x4(&mProj);

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);


	PassConstants PassCB;


	XMStoreFloat4x4(&PassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&PassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&PassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&PassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&PassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&PassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	PassCB.EyePosW = XMFLOAT3(4, -3, 3);// XMVectorSet(4, -3, 3);
		//mEyePos;
	PassCB.RenderTargetSize = XMFLOAT2((float)g_ClientWidth, (float)g_ClientHeight);
	PassCB.InvRenderTargetSize = XMFLOAT2(1.0f / g_ClientWidth, 1.0f / g_ClientHeight);
	PassCB.NearZ = 1.0f;
	PassCB.FarZ = 1000.0f;
	
	PassCB.TotalTime = t->TotalTime();
	PassCB.DeltaTime = t->DeltaTime();
	PassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	PassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	PassCB.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	PassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	PassCB.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
	PassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	PassCB.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };

	//copydata update obj constant buffer
	memcpy(&m_MappedData_pass[m_ElementByteSize], &PassCB, sizeof(PassCB));

}

void CTestObject2::UpdateOjbectConstant()
{
	XMMATRIX world, WVP;
	world = ((CTransform*)pTransform.get())->GetWorld();
	WVP = world * g_matView * g_matProj;

	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(WVP));

	XMMATRIX texTransform = XMMatrixIdentity();
	XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

	//copydata update obj constant buffer
	memcpy(&m_MappedData[m_ElementByteSize], &objConstants, sizeof(objConstants));
}

int CTestObject2::LastUpdate_GameObject(const std::shared_ptr<CTimer> t)
{
	return 0;
}

void CTestObject2::Render_GameObject()
{
	ComPtr<ID3D12Device> device = m_DxDevice->GetDevice();
	ComPtr<ID3D12GraphicsCommandList> cmdList = m_DxDevice->GetCommandList();

	

	ID3D12DescriptorHeap* descriptorHeaps[] = {m_CbvHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	cmdList->SetGraphicsRootSignature(dynamic_cast<CRenderer*>(pRenderer.get())->GetRootSignature().Get());
	

	auto passCB = m_UploadBuffer_pass.Get();
	

	cmdList->IASetVertexBuffers(0, 1, &(dynamic_cast<CBasicMesh_Crate*>(pCrate.get())->GetGeometry()->VertexBufferView()));
	cmdList->IASetIndexBuffer(&(dynamic_cast<CBasicMesh_Crate*>(pCrate.get())->GetGeometry()->IndexBufferView()));
	cmdList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(m_CbvHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(0, m_DescriptorSize);
		//tex.Offset(ri->Mat->DiffuseSrvHeapIndex, mCbvSrvDescriptorSize);
	//tex.Offset(dynamic_cast<CMaterial*>(pMaterial.get())->GetMaterial()->DiffuseSrvHeapIndex,)

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = m_UploadBuffer.Get()->GetGPUVirtualAddress();
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = dynamic_cast<CMaterial*>(pMaterial.get())->GetConstantBuffer()->GetGPUVirtualAddress();
		
	cmdList->SetGraphicsRootDescriptorTable(0, tex);
	cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	cmdList->SetGraphicsRootConstantBufferView(2, passCB->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	//cmdList->DrawIndexedInstanced
	//cmdList->SetGraphicsRootDescriptorTable(0, m_CbvHeap->GetGPUDescriptorHandleForHeapStart());
	/*cmdList->DrawIndexedInstanced(dynamic_cast<CBasicMesh_Crate*>(pCrate.get())->GetGeometry()->DrawArgs["box"].IndexCount,
		1, 0, 0, 0);*/
	cmdList->DrawIndexedInstanced(dynamic_cast<CBasicMesh_Crate*>(pCrate.get())->GetGeometry()->DrawArg.IndexCount,
		1, 0, 0, 0);

}

void CTestObject2::OnResize()
{

}

