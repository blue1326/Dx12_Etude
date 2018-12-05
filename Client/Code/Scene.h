#ifndef Scene_h__
#define Scene_h__
#include "stdHeaders.h"
#include "GameObject.h"

class CScene
{
public:
	CScene();
	~CScene();
public :
	void SetActiveState(bool state);
	bool GetActiveState()
	{
		return isActive;
	}
	virtual bool Ready_Scene(void) =0;
	virtual int Update_Scene(const std::shared_ptr<CTimer> t)=0;
	virtual int LastUpdate_Scene(const std::shared_ptr<CTimer> t)=0;
	virtual void Render_Scene(const std::shared_ptr<CTimer> t)=0;
	void AddGameObject(std::shared_ptr<CGameObject> obj);

	void OnResize();

protected:
	
protected:
	std::list<std::shared_ptr<CGameObject>> m_Objects;
	bool isActive = false;
};
 
#endif // Scene_h__
