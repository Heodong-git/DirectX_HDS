#pragma once

// 엔진에서 사용할 enum class 의 집합 

// 쉐이더타입 
enum class ShaderType
{
	None,
	Vertex,
	Pixel,
};

// 카메라타입
enum class CameraType
{
	None,
	Perspective,
	Orthogonal,
};