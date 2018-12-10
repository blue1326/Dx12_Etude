#ifndef Object_h__
#define Object_h__
#include "stdHeaders.h"
#include "Component.h"
class CGameObject
{
protected:
	explicit CGameObject();
	virtual ~CGameObject();
public:
	//CComponent
	float Get_ViewZ(void) { return 0; }
public:
	virtual HRESULT Init_GameObject(void)=0;
	virtual int Update_GameObject(const std::shared_ptr<CTimer> t)=0;
	virtual int LastUpdate_GameObject(const std::shared_ptr<CTimer> t)=0;
	virtual void Render_GameObject()=0;
	//virtual void Render_GameObject_Depth(const CTimer& t)=0;
	//void AddComponent(std::string ComponentTag,std::shared_ptr<CComponent> component);
	//void AddComponent(eCOMPONENTS comptag, std::shared_ptr<CComponent> component);
	virtual void OnResize()PURE;

protected:
	virtual void Free(void);
};


#endif // Object_h__
