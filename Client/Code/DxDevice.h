#ifndef DxDevice_h__
#define DxDevice_h__

#include "stdHeaders.h"


class DxDevice
{
public:
	DxDevice();
	~DxDevice();
public:
	bool InitDxDevice();
	bool DeviceInitState();
	void SetDeviceInitState(bool isready);
	//void SetClientSize(int width, int height);
	//bool Get4xMsaaState()const;//to renderer?
	//void Set4xMsaaState(bool value);//to renderer?
	
	//void RenderBegin();
	//void RenderEnd();



	//void OnResize();//to renderer?
	//void SetMainWnd(const HWND& mainWnd);
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
	bool InitDirect3D();

	//void CreateCommandObjects();
	//void CreateSwapChain();
	//void CreateRtvAndDsvDescriptorHeaps();



	//ID3D12Resource* CurrentBackBuffer()const;
	//D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	//D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	//void FlushCommandQueue();

	
private:
	bool m_Initialized = false;
	//HWND      m_hMainWnd = nullptr;

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;

	/*Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_CurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	static const int SwapChainBufferCount = 2;
	int m_CurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;*/

	//D3D12_VIEWPORT m_ScreenViewport;
	//D3D12_RECT m_ScissorRect;
/*
	UINT m_RtvDescriptorSize = 0;
	UINT m_DsvDescriptorSize = 0;
	UINT m_CbvSrvUavDescriptorSize = 0;*/

	//// Derived class should set these in derived constructor to customize starting values.
	//D3D_DRIVER_TYPE m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	//DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	//DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//// Set true to use 4X MSAA (?.1.8).  The default is false.
	//bool      m4xMsaaState = false;    // 4X MSAA enabled
	//UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	//int m_ClientWidth = 800;
	//int m_ClientHeight = 600;
	//bool m_ClientResize = false;
};

#endif // DxDevice_h__
