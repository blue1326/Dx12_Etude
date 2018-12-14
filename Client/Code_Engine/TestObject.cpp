#include "TestObject.h"
#include "ComponentHolder.h"
#include "box.h"
#include "Transform.h"
CTestObject::CTestObject()
	:pBox(nullptr)
	,pTransform(nullptr)
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
	
	return S_OK;
}

int CTestObject::Update_GameObject(const std::shared_ptr<CTimer> t)
{
	((CTransform*)pTransform.get())->Update_Component(t);
	
	return 0;
}

int CTestObject::LastUpdate_GameObject(const std::shared_ptr<CTimer> t)
{
	return 0;
}

void CTestObject::Render_GameObject()
{
	
	

}

void CTestObject::OnResize()
{

}

