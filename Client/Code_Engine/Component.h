#ifndef Component_h__
#define Component_h__
#include "stdHeaders.h"
class CTimer;
class CComponent : public std::enable_shared_from_this<CComponent>
{
public:
	enum COMPONENT_TYPE { COMP_STANDALONE, COMP_SHARED };
public:
	explicit CComponent();
	explicit CComponent(const CComponent& rhs) = delete;
	virtual ~CComponent();
	
public:
	virtual bool Init_Component();
	virtual void Update_Component(const std::shared_ptr<CTimer> t);
	virtual std::shared_ptr<CComponent> Clone()=0;
	virtual void OnResize();

protected:
	COMPONENT_TYPE m_CType;


	
		
};

#endif // Component_h__
