#ifndef Object_h__
#define Object_h__
#include "stdHeaders.h"
#include "Component.h"
class CGameObject :public enable_shared_from_this<CGameObject>
{
public:
	enum OBJECTTYPE{OBJ_LOGIC,OBJ_GENERIC};
protected:
	explicit CGameObject();
	virtual ~CGameObject();
public:
	//CComponent
	float Get_ViewZ(void) { return 0; }
public:
	virtual bool Init_GameObject(void)=0;
	virtual int Update_GameObject(const std::shared_ptr<CTimer> t)=0;
	virtual int LastUpdate_GameObject(const std::shared_ptr<CTimer> t)=0;
	virtual void Render_GameObject()=0;
	//virtual void Render_GameObject_Depth(const CTimer& t)=0;
	//void AddComponent(std::string ComponentTag,std::shared_ptr<CComponent> component);
	void AddComponent(eCOMPONENTS comptag, std::shared_ptr<CComponent> component);
	void OnResize();
protected:
	inline shared_ptr<CGameObject> SetRenderer()
	{
		return this->shared_from_this();
	}
protected:
	OBJECTTYPE eType;
	//Components
protected:
	//typedef std::map<std::string, std::shared_ptr<CComponent>> COMPONENT;//아마도 삭제
	//COMPONENT m_Components;
	std::array<std::shared_ptr<CComponent>, COMPCNT> m_ComponentArr;
};


#endif // Object_h__
