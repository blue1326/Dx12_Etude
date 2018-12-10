#ifndef Renderer_h__
#define Renderer_h__
#include "Component.h"
#include "stdHeaders.h"
//#include "DefinedHeaders.h"
#include "DxDevice.h"
//#include "UploadBuffer.h"
#include "GameObject.h"
#include "Timer.h"



class CRenderer : public CComponent
{
public:
	enum RENDER { RENDER_PRIORITY, RENDER_NONEALPHA, RENDER_ALPHA, RENDER_UI, RENDER_DUAL, RENDER_END };
public:
	explicit CRenderer(const std::shared_ptr<DxDevice> Device);
	virtual ~CRenderer();
public:
	virtual HRESULT Init_Component()override;
	virtual void Update_Component(const std::shared_ptr<CTimer> t)override;
	// render to gameobject
	virtual void Render_GameObject(void);

	void RenderNoneAlpha(void);

	HRESULT Add_RenderList(RENDER eType, shared_ptr<CGameObject> object);

public:
	virtual std::shared_ptr<CComponent> Clone()override;

	
private://render list
private:
	list<shared_ptr<CGameObject>>				m_RenderList[RENDER_END];
	typedef list<shared_ptr<CGameObject>>		RENDERLIST;
public:
	void Clear_RenderList();

private:
	const std::shared_ptr<DxDevice> m_DxDevice;

};
#endif // Renderer_h__
