#ifndef testScene_h__
#define testScene_h__

#include "stdHeaders.h"
#include "Scene.h"
class CScene_Test : public CScene
{
public:
	explicit CScene_Test();
	virtual ~CScene_Test();

public:
	virtual HRESULT Ready_Scene();
	virtual int Update_Scene(const std::shared_ptr<CTimer> t);
	virtual int LastUpdate_Scene(const std::shared_ptr<CTimer> t);
	virtual void Render_Scene(void);
private:
	HRESULT Ready_LayerTest(const wchar_t* pLayerTag);
};



#endif // testScene_h__
