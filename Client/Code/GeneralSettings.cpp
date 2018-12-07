//#include "stdHeaders.h"
#include "GeneralSettings.h"
//#include "Renderer.h"
//#include "Transform.h"
//#include "Camera.h"
#include "Component.h"
//#include "StageFirst.h"
//#include "ComponentHolder.h"
#include "testScene.h"

CGeneralSettings::CGeneralSettings(const std::shared_ptr<DxDevice> Device, const std::shared_ptr<CTimer> Timer1, const std::shared_ptr<CTimer> Timer2)
	: m_DxDevice(Device), m_Timer1(move(Timer1)), m_Timer2(move(Timer2))
{
	m_Timer1->Reset();
	m_Timer2->Reset();
	g_DeviceInitState = true;
}

CGeneralSettings::~CGeneralSettings()
{
	
}

bool CGeneralSettings::InitGeneralSetting()
{
	if (FAILED(InitDxDevice()))
		return false;
	if (FAILED(InitComponents()))
		return false;
	if (FAILED(InitScene()))
		return false;
	return true;
}

HRESULT CGeneralSettings::InitScene()
{
	/*m_Scene = std::shared_ptr<CScene>(new CStageFirst);
	if (!m_Scene->Ready_Scene())
		return false;
	m_Scene->SetActiveState(true);*/
	m_Scene = std::shared_ptr<CScene>(new CScene_Test);
	if (FAILED(m_Scene->Ready_Scene()))
		return E_FAIL;
	m_Scene->SetActiveState(true);

	return S_OK;
}

HRESULT CGeneralSettings::InitComponents()
{
	//CComponentHolder::GetInstance()->Reserve_ComponentHolder(20);

	//std::shared_ptr<CComponent> inst = std::shared_ptr<CComponent>(new CRenderer(m_DxDevice));
	//CComponentHolder::GetInstance()->AddOriginComponent("Renderer", inst);
	//inst.reset(new CTransform(m_DxDevice->GetDevice()));
	//CComponentHolder::GetInstance()->AddOriginComponent("Transform", inst);
	////m_DxDevice->GetDevice()
	//inst.reset(new CCamera(m_DxDevice->GetDevice()));
	//CComponentHolder::GetInstance()->AddOriginComponent("Camera", inst);
	//inst.reset(new CLand(m_DxDevice->GetDevice()));
	//CComponentHolder::GetInstance()->AddOriginComponent("Land", inst);
	//inst.reset(new CWave(m_DxDevice->GetDevice(),m_DxDevice->GetDxgiFactory()));
	//CComponentHolder::GetInstance()->AddOriginComponent("Wave", inst);
	//if (!CComponentHolder::GetInstance()->InitComponents())
	//	return false;


	//m_OriginalComponents.insert(OC::value_type("Renderer", inst));
	//m_OriginalRenderer = inst;
	//
	////m_OriginalComponents.insert(OC::value_type("Transform", inst));
	//for (const auto &j : m_OriginalComponents)
	//{
	//	j.second->Init_Component();
	//	//std::shared_ptr<CComponent> tmp1 = j.second->Clone();
	//	//std::shared_ptr<CComponent> tmp2 = j.second->Clone();
	//	//std::shared_ptr<CComponent> tmp3 = j.second->Clone();
	//	//std::shared_ptr<CComponent> tmp4 = j.second->Clone();
	//	//int origin = j.second.use_count();
	//	//int t1 = tmp1.use_count();
	//	//int t2 = tmp2.use_count();
	//	//int t3 = tmp3.use_count();
	//	//int t4 = tmp4.use_count();
	//	//int x = 0;
	//	////testcode
	//}
	return S_OK;
}

///////////////////////////////////////////////////////////for Generic Method
void CGeneralSettings::Update()
{
	m_Scene->Update_Scene(m_Timer1);
	
}

void CGeneralSettings::Last_Update()
{
	m_Scene->LastUpdate_Scene(m_Timer1);
	
}

void CGeneralSettings::Render()
{

	
	//((CRenderer*)(CComponentHolder::GetInstance()->Get_Component("Renderer").get()))->Render_GameObject();
	




	//m_Scene->Render_Scene(m_Timer2);
	//it is test code
	 /*OC::iterator iter = m_OriginalComponents.find("Renderer");
	 ((CRenderer*)(iter->second.get()))->Render_Begin();
	 ((CRenderer*)(iter->second.get()))->Render_End();*/
		// ->Render_Begin();
	 //iter->second)->Render_End();
	/*m_DxDevice->RenderBegin();
	m_DxDevice->RenderEnd();*/
	//((CRenderer*)m_OriginalRenderer.get())->Render_Begin();
	//((CRenderer*)m_OriginalRenderer.get())->Render_End();
	 //m_OriginalRenderer->Render_Begin();
	//m_OriginalRenderer->Render_End();

}
//
//void CGeneralSettings::SetClientSize(int width, int height) {
//	
//	((CRenderer*)CComponentHolder::GetInstance()->Get_Component("Renderer").get())->SetClientSize(width, height);
//}

void CGeneralSettings::OnResize()
{
	//m_Scene->OnResize();
	//((CRenderer*)CComponentHolder::GetInstance()->Get_Component("Renderer").get())->OnResize();
}
//////////////////////////////////////////////////////////for TimerMethod
std::shared_ptr<CTimer> CGeneralSettings::GetTimer(TimerDef td)
{
	switch (td)
	{
	case MainTimer:
		return m_Timer1;
	case SubTimer:
		return m_Timer2;
	case AllTimer:
		if (m_Timer1 != nullptr && m_Timer2 != nullptr)
			return m_Timer1;
		else
			return nullptr;
	}
	return nullptr;
}

void CGeneralSettings::TimerReset(TimerDef td)
{
	switch (td)
	{
	case MainTimer:
		return m_Timer1->Reset();
	case SubTimer:
		return m_Timer2->Reset();
	case AllTimer:
		m_Timer1->Reset();
		m_Timer2->Reset();
	}
	
}

void CGeneralSettings::TimerStart(TimerDef td)
{
	switch (td)
	{
	case MainTimer:
		m_Timer1->Start();
		return;
	case SubTimer:
		m_Timer2->Start();
		return;
	case AllTimer:
		m_Timer1->Start();
		m_Timer2->Start();
		return;
	}
	
}

void CGeneralSettings::TimerStop(TimerDef td)
{
	switch (td)
	{
	case MainTimer:
		m_Timer1->Stop();
		return;
	case SubTimer:
		m_Timer2->Stop();
		return;
	case AllTimer:
		m_Timer1->Stop();
		m_Timer2->Stop();
		return;
	}
	
}

void CGeneralSettings::TimerTick(TimerDef td)
{
	switch (td)
	{
	case MainTimer:
		m_Timer1->Tick();
		return;
	case SubTimer:
		m_Timer2->Tick();
		return; 
	case AllTimer:
		m_Timer1->Tick();
		m_Timer2->Tick();
		return;
	}
	
}

std::shared_ptr<DxDevice> CGeneralSettings::GetDevice()
{
	return m_DxDevice;
}

HRESULT CGeneralSettings::InitDxDevice()
{
	if (FAILED(m_DxDevice->InitDxDevice()))
		return E_FAIL;
	g_DeviceInitState = true;
	return S_OK;
}


void CGeneralSettings::CalculateFrameStats(const HWND& mainWnd, std::wstring caption)
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((m_Timer1->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wstring fpsStr = std::to_wstring(fps);
		std::wstring mspfStr = std::to_wstring(mspf);
		
		std::wstring windowText = caption +
			L"    fps: " + fpsStr +
			L"   mspf: " + mspfStr;

		SetWindowText(mainWnd, windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}