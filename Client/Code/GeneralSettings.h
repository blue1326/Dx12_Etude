#ifndef GeneralSettings_h__
#define GeneralSettings_h__
#include "stdHeaders.h"
#include "DxDevice.h"
#include "Component.h"
#include "Renderer.h" //나중에 대체
#include "Scene.h"
class CGeneralSettings 
{
public:
	enum TimerDef { MainTimer, SubTimer,AllTimer };
public:
	CGeneralSettings(const std::shared_ptr<DxDevice> Device ,const std::shared_ptr<CTimer> Timer1, const std::shared_ptr<CTimer> Timer2);
	~CGeneralSettings();
public:
	bool InitGeneralSetting();
	bool InitScene();
	void Update();
	void Late_Update();
	void Render();
	//void SetClientSize(int width, int height);//임시
	void OnResize();
public: //for Timer method
	std::shared_ptr<CTimer> GetTimer(TimerDef td);
	void TimerReset(TimerDef td);
	void TimerStart(TimerDef td);
	void TimerStop(TimerDef td);
	void TimerTick(TimerDef td);

public: //for frame Count
	void CalculateFrameStats(const HWND& mainWnd, std::wstring caption);
public: //for DxDevice method
	std::shared_ptr<DxDevice> GetDevice();
	bool InitDxDevice();
private://for components
	bool InitComponents();
private:
	const std::shared_ptr<CTimer> m_Timer1 = nullptr;
	const std::shared_ptr<CTimer> m_Timer2 = nullptr;
	const std::shared_ptr<DxDevice> m_DxDevice = nullptr;
	

	std::shared_ptr<CScene> m_Scene = nullptr;

};

#endif // GeneralSettings_h__
