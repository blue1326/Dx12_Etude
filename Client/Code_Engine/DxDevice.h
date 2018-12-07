#ifndef DxDevice_h__
#define DxDevice_h__

#include "stdHeaders.h"


class DxDevice
{
public:
	DxDevice();
	~DxDevice();
public:
	HRESULT InitDxDevice();
	bool DeviceInitState();
	void SetDeviceInitState(bool isready);

public : //public getter and setter
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice() {
		return m_d3dDevice;
	}
	Microsoft::WRL::ComPtr<IDXGIFactory4> GetDxgiFactory()
	{
		return m_dxgiFactory;
	}
public:
	void LogAdapters(DXGI_FORMAT format);
	void LogAdapterOutputs(IDXGIAdapter* adapter, DXGI_FORMAT format);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

private:
	HRESULT InitDirect3D();

	
	
private:
	bool m_Initialized = false;
	//HWND      m_hMainWnd = nullptr;

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;

};

#endif // DxDevice_h__
