#ifndef stdHeaders_h__
#define stdHeaders_h__

//windows
#include <windows.h>
#include <wrl.h>

//d3d
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include "d3dx12.h"

//stl
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map> //hashmap
#include <map> //map

//stream
#include <fstream>
#include <sstream>
#include <iostream>

//??
#include <cstdint>

#include <cassert>
#include <ppl.h>


//necessary d3d12 libs
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")



#endif // stdHeaders_h__
