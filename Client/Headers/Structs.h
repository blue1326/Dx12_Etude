#ifndef Structs_h__
#define Structs_h__
//
//struct ObjectConstants //maybebox
//{
//	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
//};
using namespace DirectX;
struct ObjectConstants
{
	//DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
};

struct Vertex //maybebox
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


//
//struct PassConstants
//{
//	DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 InvView = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 InvProj = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 ViewProj = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 InvViewProj = MathHelper::Identity4x4();
//	DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
//	float cbPerObjectPad1 = 0.0f;
//	DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
//	DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };
//	float NearZ = 0.0f;
//	float FarZ = 0.0f;
//	float TotalTime = 0.0f;
//	float DeltaTime = 0.0f;
//};

using uint16 = std::uint16_t;
using uint32 = std::uint32_t;

namespace Geometry {


	struct Vertex
	{
		Vertex() {}
		Vertex(
			const DirectX::XMFLOAT3& p,
			const DirectX::XMFLOAT3& n,
			const DirectX::XMFLOAT3& t,
			const DirectX::XMFLOAT2& uv) :
			Position(p),
			Normal(n),
			TangentU(t),
			TexC(uv) {}
		Vertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v) :
			Position(px, py, pz),
			Normal(nx, ny, nz),
			TangentU(tx, ty, tz),
			TexC(u, v) {}

		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 TangentU;
		DirectX::XMFLOAT2 TexC;
	};


	struct MeshData
	{
		std::vector<Vertex> Vertices;
		std::vector<uint32> Indices32;

		std::vector<uint16>& GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices32.size());
				for (size_t i = 0; i < Indices32.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices32[i]);
			}

			return mIndices16;
		}

	private:
		std::vector<uint16> mIndices16;
	};
}

//
//
//using uint16 = std::uint16_t;
//using uint32 = std::uint32_t;
//
//struct Vertex
//{
//	Vertex() {}
//	Vertex(
//		const DirectX::XMFLOAT3& p,
//		const DirectX::XMFLOAT3& n,
//		const DirectX::XMFLOAT3& t,
//		const DirectX::XMFLOAT2& uv) :
//		Position(p),
//		Normal(n),
//		TangentU(t),
//		TexC(uv) {}
//	Vertex(
//		float px, float py, float pz,
//		float nx, float ny, float nz,
//		float tx, float ty, float tz,
//		float u, float v) :
//		Position(px, py, pz),
//		Normal(nx, ny, nz),
//		TangentU(tx, ty, tz),
//		TexC(u, v) {}
//
//	DirectX::XMFLOAT3 Position;
//	DirectX::XMFLOAT3 Normal;
//	DirectX::XMFLOAT3 TangentU;
//	DirectX::XMFLOAT2 TexC;
//};
//
//struct MeshData
//{
//	std::vector<Vertex> Vertices;
//	std::vector<uint32> Indices32;
//
//	std::vector<uint16>& GetIndices16()
//	{
//		if (mIndices16.empty())
//		{
//			mIndices16.resize(Indices32.size());
//			for (size_t i = 0; i < Indices32.size(); ++i)
//				mIndices16[i] = static_cast<uint16>(Indices32[i]);
//		}
//
//		return mIndices16;
//	}
//
//private:
//	std::vector<uint16> mIndices16;
//};
//


#endif // Structs_h__
