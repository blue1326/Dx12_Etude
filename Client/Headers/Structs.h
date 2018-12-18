#ifndef Structs_h__
#define Structs_h__

#include <DirectXMath.h>
#include "MathHelper.h"
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct ObjectConstants
{
	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};


#endif // Structs_h__
