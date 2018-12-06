#include "DxDevice.h"
#include <windowsx.h>
#include "dxException.h"
DxDevice::DxDevice()
{

}

DxDevice::~DxDevice()
{
}

bool DxDevice::InitDxDevice()
{

	/*if (!InitDirect3D())
		return false;
*/


	return true;
}


bool DxDevice::InitDirect3D()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_dxgiFactory)));

	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_d3dDevice));

	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_d3dDevice)));
	}
	////////////device and factory

	return true;
}


void DxDevice::LogAdapters(DXGI_FORMAT format)
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (m_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		LogAdapterOutputs(adapterList[i], format);
		ReleaseCom(adapterList[i]);
	}
}

void DxDevice::LogAdapterOutputs(IDXGIAdapter* adapter,DXGI_FORMAT format)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		LogOutputDisplayModes(output, format);
		//LogOutputDisplayModes(output, m_BackBufferFormat);

		ReleaseCom(output);

		++i;
	}
}

void DxDevice::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L" " +
			L"Height = " + std::to_wstring(x.Height) + L" " +
			L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) +
			L"\n";

		::OutputDebugString(text.c_str());
	}
}

//
//
//ID3D12Resource* DxDevice::CurrentBackBuffer() const
//{
//	return m_SwapChainBuffer[m_CurrBackBuffer].Get();
//}
//
//D3D12_CPU_DESCRIPTOR_HANDLE DxDevice::CurrentBackBufferView() const
//{
//	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		m_RtvHeap->GetCPUDescriptorHandleForHeapStart(),
//		m_CurrBackBuffer,
//		m_RtvDescriptorSize);
//}
//
//D3D12_CPU_DESCRIPTOR_HANDLE DxDevice::DepthStencilView() const
//{
//	return m_DsvHeap->GetCPUDescriptorHandleForHeapStart();
//}
//
//void DxDevice::FlushCommandQueue()
//{
//	// Advance the fence value to mark commands up to this fence point.
//	m_CurrentFence++;
//
//	// Add an instruction to the command queue to set a new fence point.  Because we 
//	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
//	// processing all the commands prior to this Signal().
//	ThrowIfFailed(m_CommandQueue->Signal(m_Fence.Get(), m_CurrentFence));
//
//	// Wait until the GPU has completed commands up to this fence point.
//	if (m_Fence->GetCompletedValue() < m_CurrentFence)
//	{
//		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
//
//		// Fire event when GPU hits current fence.  
//		ThrowIfFailed(m_Fence->SetEventOnCompletion(m_CurrentFence, eventHandle));
//
//		// Wait until the GPU hits current fence event is fired.
//		WaitForSingleObject(eventHandle, INFINITE);
//		CloseHandle(eventHandle);
//	}
//}

bool DxDevice::DeviceInitState()
{
	return m_Initialized;
}

void DxDevice::SetDeviceInitState(bool isready)
{
	m_Initialized = isready;
}

