#ifndef TestObject_Camera_h__
#define TestObject_Camera_h__
#include "stdHeaders.h"
#include "GameObject.h"
#include "Component.h"



class CTestObject_Camera : public CGameObject
{
public:
	CTestObject_Camera();
	~CTestObject_Camera();
public:
	virtual HRESULT Init_GameObject(void)override;
	virtual int Update_GameObject(const std::shared_ptr<CTimer> t)override;
	virtual int LastUpdate_GameObject(const std::shared_ptr<CTimer> t)override;
	virtual void Render_GameObject()override;
	virtual void OnResize()override;
protected:
	
private:
	shared_ptr<CComponent> pTransform;
	shared_ptr<CComponent> pCamera;
};
 

#endif // TestObject_Camera_h__
