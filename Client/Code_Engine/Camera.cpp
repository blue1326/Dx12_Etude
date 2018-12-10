#include "Camera.h"
#include "ComponentHolder.h"
#include "Renderer.h"
#include "MathHelper.h"
CCamera::CCamera(const shared_ptr<DxDevice> _device)
	: m_fFovy(0.f)
	, m_fAspect(0.f)
	, m_fNear(0.f)
	, m_fFar(0.f)
	,m_d3dDevice(_device)
{
	m_CType = COMP_STANDALONE;
}

CCamera::CCamera(const CCamera& rhs)
	:m_vEye(rhs.m_vEye)
	,m_vAt(rhs.m_vAt)
	,m_vUp(rhs.m_vUp)
	,m_fFovy(rhs.m_fFovy)
	,m_fAspect(rhs.m_fAspect)
	,m_fNear(rhs.m_fNear)
	,m_fFar(rhs.m_fFar)
	,m_World(rhs.m_World)
	,m_View(rhs.m_View)
	,m_Proj(rhs.m_Proj)
	,m_d3dDevice(rhs.m_d3dDevice)
{
	m_CType = COMP_STANDALONE;
}

CCamera::~CCamera()
{
	//m_d3dDevice = nullptr;
}

HRESULT CCamera::Init_Component()
{
	XMFLOAT4 initValue = XMFLOAT4(0, 0, 0,0);
	m_vEye = XMLoadFloat4(&initValue);
	m_vAt = XMLoadFloat4(&initValue);
	m_vUp = XMLoadFloat4(&initValue);
	m_World = XMMatrixIdentity();
	m_View = XMMatrixIdentity();
	m_Proj = XMMatrixIdentity();
		
	
	return S_OK;
}

void CCamera::Update_Component(const std::shared_ptr<CTimer> t)
{
	

	XMMATRIX m_View = XMMatrixLookAtLH(m_vEye, m_vAt, m_vUp);
	g_matView = m_View;
	XMMATRIX worldViewProj = m_World * m_View * m_Proj;


	
	///나중에 옮길 코드
	/*ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	((CRenderer*)(CComponentHolder::GetInstance()->Get_Component("Renderer").get()))->SetObjConst(objConstants);*/
}

std::shared_ptr<CComponent> CCamera::Clone()
{
	std::shared_ptr<CComponent> instance = std::shared_ptr<CComponent>(new CCamera(*this));
	//CopyComponentSettings(instance);
	return instance;
}


void CCamera::OnResize()
{
	m_Proj =  XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);

	g_matProj = m_Proj;
	/*XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_Proj, P);*/
}

void CCamera::SetEye(XMVECTOR vEye)
{
	m_vEye = vEye;
}

void CCamera::SetAt(XMVECTOR vAt)
{
	m_vAt = vAt;
}

void CCamera::SetUp(XMVECTOR vUp)
{
	m_vUp = vUp;
}

void CCamera::SetEyeAtUp(XMVECTOR vEye, XMVECTOR vAt, XMVECTOR vUp)
{
	m_vEye = vEye;
	m_vAt = vAt;
	m_vUp = vUp;
}

void CCamera::SetWorld(XMMATRIX matWorld)
{
	//m_World = matWorld;
}

