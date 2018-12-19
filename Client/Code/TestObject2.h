#ifndef TestObject2_h__
#define TestObject2_h__
#include "stdHeaders.h"
#include "GameObject.h"
#include "Component.h"
#include "DxDevice.h"

class CTestObject2 : public CGameObject
{
public:
	CTestObject2(shared_ptr<DxDevice> _device);
	~CTestObject2();
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
	shared_ptr<CComponent> pRenderer;
<<<<<<< HEAD
	shared_ptr<CComponent> pCrate;
	shared_ptr<CComponent> pMaterial;

private:
	void UpdatePassConstant(const std::shared_ptr<CTimer> t);
	void UpdateOjbectConstant();
=======
>>>>>>> parent of 2683f7f... minorupdate
private:
	CTestObject2();
};
 

#endif // TestObject2_h__
