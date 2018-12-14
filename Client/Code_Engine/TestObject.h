#ifndef TestObject_h__
#define TestObject_h__
#include "stdHeaders.h"
#include "GameObject.h"
#include "Component.h"

class CTestObject : public CGameObject
{
public:
	CTestObject();
	~CTestObject();
public:
	virtual HRESULT Init_GameObject(void)override;
	virtual int Update_GameObject(const std::shared_ptr<CTimer> t)override;
	virtual int LastUpdate_GameObject(const std::shared_ptr<CTimer> t)override;
	virtual void Render_GameObject()override;

	virtual void OnResize()override;
protected:
	
private:
	shared_ptr<CComponent> pBox;
	shared_ptr<CComponent> pTransform;
};
 

#endif // TestObject_h__
