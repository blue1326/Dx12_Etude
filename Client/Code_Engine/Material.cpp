#include "Material.h"
#include "dxException.h"
#include "DDSTextureLoader.h"
#include "BufferUtility.h"
CMaterial::CMaterial(const shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
	,m_Material(nullptr)
	,m_Texture(nullptr)
	//,m_SrvDescriptorHeap(nullptr)
	,m_MappedData(nullptr)
	,m_ElementByteSize(0)
{

}

CMaterial::CMaterial(const CMaterial& rhs)
	:m_DxDevice(rhs.m_DxDevice)
	,m_Material(rhs.m_Material)
	,m_Texture(rhs.m_Texture)
	//,m_SrvDescriptorHeap(nullptr)
	, m_MappedData(nullptr)
	, m_ElementByteSize(0)
{
	int i = 0;
}

CMaterial::~CMaterial()
{
	
}

HRESULT CMaterial::Init_Component()
{
	if (m_Material != nullptr && m_Texture != nullptr)
	{
		Init_Start();


		LoadTexture();




		Init_End();
	}
	else
		return E_FAIL;
	return S_OK;
}

void CMaterial::Update_Component(const std::shared_ptr<CTimer> t)
{
	XMMATRIX matTransform = XMLoadFloat4x4(&m_Material->MatTransform);

	MaterialConstants matConstants;
	matConstants.DiffuseAlbedo = m_Material->DiffuseAlbedo;
	matConstants.FresnelR0 = m_Material->FresnelR0;
	matConstants.Roughness = m_Material->Roughness;
	XMStoreFloat4x4(&matConstants.MatTransform, XMMatrixTranspose(matTransform));

	//currMaterialCB->CopyData(mat->MatCBIndex, matConstants);

	int emementidx = 0; //it is samplecode
	//copydata update obj constant buffer
	memcpy(&m_MappedData[emementidx * m_ElementByteSize], &matConstants, sizeof(matConstants));


	// Next FrameResource need to be updated too.
}

void CMaterial::Ready_Component()
{
	//Init_Start();
	//BuildDescripterHeap();
	BuildConstantBuffers();
	//Init_End();
}

void CMaterial::BuildConstantBuffers()
{
	CreateUplaodBuffer();
	//D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_UploadBuffer.Get()->GetGPUVirtualAddress();
	//int matCBufIndex = 0;
	//cbAddress += matCBufIndex * m_ElementByteSize; //extend size

	//D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	//cbvDesc.BufferLocation = cbAddress;
	//cbvDesc.SizeInBytes = m_ElementByteSize;

	//m_DxDevice->GetDevice().Get()->CreateConstantBufferView(&cbvDesc, m_SrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}

void CMaterial::CreateUplaodBuffer()
{
	m_ElementByteSize = BufferUtility::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	ThrowIfFailed(m_DxDevice->GetDevice().Get()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(m_ElementByteSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_UploadBuffer)));

	ThrowIfFailed(m_UploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_MappedData)));
}

std::shared_ptr<CComponent> CMaterial::Clone()
{
	return shared_ptr<CComponent>(new CMaterial(*this));
}

void CMaterial::SetUpMaterialState(const shared_ptr<Material> _Material)
{
	m_Material = _Material;
}

void CMaterial::SetUpTextureLocation(const wstring& _str)
{
	auto tex = make_shared<Texture>();
	tex->Name = "Tex";
	tex->Filename = _str;
	m_Texture = tex;
}

void CMaterial::Init_Start()
{
	ThrowIfFailed(m_DxDevice->GetCommandList()->Reset(m_DxDevice->GetCommandAllocator().Get(), nullptr));
}

void CMaterial::Init_End()
{
	// Execute the initialization commands.
	ThrowIfFailed(m_DxDevice->GetCommandList()->Close());
	ID3D12CommandList* cmdsLists[] = { m_DxDevice->GetCommandList().Get() };
	m_DxDevice->GetCommandQueue()->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	m_DxDevice->FlushCommandQueue();
}

void CMaterial::LoadTexture()
{
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(m_DxDevice->GetDevice().Get(),
		m_DxDevice->GetCommandList().Get(), m_Texture->Filename.c_str(),
		m_Texture->Resource, m_Texture->UploadHeap));
}

void CMaterial::SetUpDescripterHeap(ComPtr<ID3D12DescriptorHeap> _heap)
{
	//create srv heap
	//D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	//srvHeapDesc.NumDescriptors = 1;
	//srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//ThrowIfFailed(m_DxDevice->GetDevice().Get()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_SrvDescriptorHeap)));

	////descriptor heap for texture


	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(_heap->GetCPUDescriptorHandleForHeapStart());

	auto tex = m_Texture->Resource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = tex->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = tex->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	m_DxDevice->GetDevice()->CreateShaderResourceView(tex.Get(), &srvDesc, hDescriptor);


}

