#ifndef box_h__
#define box_h__

#include "Component.h"
#include "DxDevice.h"
#include "MeshGeometry.h"
<<<<<<< HEAD
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct ObjectConstants
{
	//XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};
=======
#include "Structs.h"
#include "MathHelper.h"

//struct Vertex
//{
//	XMFLOAT3 Pos;
//	XMFLOAT4 Color;
//};
//
//struct ObjectConstants
//{
//	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
//};
>>>>>>> parent of e7d7f92... Revert "minorupdate"

class CBox : public CComponent
{
public:
	explicit CBox(const shared_ptr<DxDevice> _device);
	explicit CBox(const CBox& rhs);
	virtual ~CBox();

public:
	virtual HRESULT Init_Component()override;
	virtual void Update_Component(const std::shared_ptr<CTimer> t)override;

private:
<<<<<<< HEAD
	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();

private:
	const shared_ptr<DxDevice> m_DxDevice;
	ComPtr<ID3D12DescriptorHeap> m_CbvHeap;
	ComPtr<ID3D12RootSignature> m_RootSignature;
	ComPtr<ID3DBlob> m_vsByteCode;
	ComPtr<ID3DBlob> m_psByteCode;
	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

	std::shared_ptr<MeshGeometry> m_BoxGeo;
	ComPtr<ID3D12PipelineState> m_PSO;
public:
	ComPtr<ID3D12PipelineState> GetPSO()
	{
		return m_PSO;
=======
	void BuildBoxGeometry();

private:
	const shared_ptr<DxDevice> m_DxDevice;

	std::shared_ptr<MeshGeometry> m_BoxGeo;

public:
	shared_ptr<MeshGeometry> GetGeometry()
	{
		return m_BoxGeo;
>>>>>>> parent of e7d7f92... Revert "minorupdate"
	}
private://for uploadbuffer
	Microsoft::WRL::ComPtr<ID3D12Resource> m_UploadBuffer;
	BYTE* m_MappedData = nullptr;

	UINT m_ElementByteSize = 0;
	bool m_IsConstantBuffer = false;
	void CreateUplaodBuffer();
public:
	virtual std::shared_ptr<CComponent> Clone()override;
private:

};



#endif // box_h__
