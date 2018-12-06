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
	virtual bool Init_Component()override;
	virtual void Update_Component(const std::shared_ptr<CTimer> t)override;
	// render to gameobject
	virtual void Render_GameObject(void);

	void RenderNoneAlpha(void);

	HRESULT Add_RenderList(RENDER eType, shared_ptr<CGameObject> object);

	void Render(const std::shared_ptr<CTimer> t);
	void Render_Begin();
	void Render_End();
	//void SetClientSize(int width, int height);
	bool Get4xMsaaState()const;//to renderer?
	void Set4xMsaaState(bool value);//to renderer?
	virtual void OnResize()override;//to renderer?
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	//float AspectRatio()const;
public:
	virtual std::shared_ptr<CComponent> Clone()override;
private:
	bool Init_Dx3D();
	
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateRtvAndDsvDescriptorHeaps();

	bool BuildNecessaryModules();
	//void BuildDescriptorHeaps();///?
	//void BuildConstantBuffers();///????maybe box
	void BuildRootSignature(); // box land wave
	
	//void BuildBoxGeometry();////???? box
	//void BuildPSO();
public:	
	void FlushCommandQueue();

	
private://render list
private:
	list<shared_ptr<CGameObject>>				m_RenderList[RENDER_END];
	typedef list<shared_ptr<CGameObject>>		RENDERLIST;
public:
	void Add_RenderList(shared_ptr<CGameObject> obj);
	void Clear_RenderList();

private://shaders
	void BuildShadersAndInputLayout();
	/*void BuildShader_Box();
	void BuildInputLayOut_Box();*/
	//void BuildShadersAndInputLayout();
	void BuildShader_LandWave();
	void BuildInputLayout_LandWave();
	void BuildPSOs();
	
	unordered_map<string,vector<D3D12_INPUT_ELEMENT_DESC>> m_InputLayout;
	std::unordered_map<std::string, ComPtr<ID3DBlob>> m_Shaders;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> m_PSOs;
private:
	ID3D12Resource * CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
private:
	const std::shared_ptr<DxDevice> m_DxDevice;

	const Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	const Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;
	// Set true to use 4X MSAA (?.1.8).  The default is false.
	bool      m4xMsaaState = false;    // 4X MSAA enabled
	UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_CurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

public://getter
	inline ComPtr<ID3D12CommandAllocator> GetDirectCmdListAlloc() { return m_DirectCmdListAlloc; }
	inline ComPtr<ID3D12CommandQueue> GetCommandQueue() { return m_CommandQueue; }
	//inline ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return m_CommandList; }

public:
	
	static const int SwapChainBufferCount = 2;
	int m_CurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

	ComPtr<ID3D12RootSignature> m_RootSignature = nullptr;
	

	///
	UINT m_RtvDescriptorSize = 0;
	UINT m_DsvDescriptorSize = 0;
	UINT m_CbvSrvUavDescriptorSize = 0;

	// Derived class should set these in derived constructor to customize starting values.
	D3D_DRIVER_TYPE m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;



	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;

	/*int m_ClientWidth = 800;
	int m_ClientHeight = 600;*/
	//bool m_ClientResize = false;
	

	///maybe camera
	/*XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f*XM_PI;
	float mPhi = XM_PIDIV4;
	float mRadius = 5.0f;*/

	/*public:
		void SetWorld(XMFLOAT4X4 world)
		{
			mWorld = world;
		}

		void SetView(XMFLOAT4X4 view)
		{
			mView = view;
		}
		void SetProj(XMFLOAT4X4 proj)
		{
			mProj = proj;
		}
		void SetObjConst(ObjectConstants oc)
		{
			m_ObjectCB->CopyData(0, oc);
		}*/
};
#endif // Renderer_h__
