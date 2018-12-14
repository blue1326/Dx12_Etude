#ifndef box_h__
#define box_h__

#include "Component.h"
#include "DxDevice.h"
#include "MeshGeometry.h"
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

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
	virtual std::shared_ptr<CComponent> Clone()override;
private:

};



#endif // box_h__
