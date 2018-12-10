#include "TestObject.h"
#include "ComponentHolder.h"
CTestObject::CTestObject()
{

}

CTestObject::~CTestObject()
{

}

HRESULT CTestObject::Init_GameObject(void)
{

	return S_OK;
}

int CTestObject::Update_GameObject(const std::shared_ptr<CTimer> t)
{
	
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

