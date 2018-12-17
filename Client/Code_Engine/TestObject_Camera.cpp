#include "TestObject_Camera.h"
#include "ComponentHolder.h"

#include "Transform.h"
#include "Camera.h"



CTestObject_Camera::CTestObject_Camera(shared_ptr<DxDevice> _device)
	:CGameObject::CGameObject(_device)
{

}

CTestObject_Camera::~CTestObject_Camera()
{

}

HRESULT CTestObject_Camera::Init_GameObject(void)
{
	pTransform = CComponentHolder::GetInstance()->Clone_Component("Transform");
	((CTransform*)pTransform.get())->Init_Component();
	((CTransform*)pTransform.get())->SetPosition(1, 1, 1);
	pCamera = CComponentHolder::GetInstance()->Clone_Component("Camera");
	((CCamera*)pCamera.get())->Init_Component();
	return S_OK;
}

int CTestObject_Camera::Update_GameObject(const std::shared_ptr<CTimer> t)
{
	XMVECTOR tmp = ((CTransform*)pTransform.get())->GetPosition();
	//it is debug code
	//cout << "is camera transform" << endl;
	//cout << "x :" << XMVectorGetX(tmp) <<endl;
	//cout << "y :" << XMVectorGetY(tmp) << endl;
	//cout << "z :" << XMVectorGetZ(tmp) << endl;
	//cout << "x :" << XMVectorGetW(tmp) << endl;
	//
	return 0;
}

int CTestObject_Camera::LastUpdate_GameObject(const std::shared_ptr<CTimer> t)
{
	
	return 0;
}

void CTestObject_Camera::Render_GameObject()
{
	
	
}

void CTestObject_Camera::OnResize()
{

}

