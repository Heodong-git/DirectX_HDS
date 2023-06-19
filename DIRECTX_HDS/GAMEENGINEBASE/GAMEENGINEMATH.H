#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// dx함수들
// 다이렉트용 벡터
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// 상속불가
class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);
	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 One;
	static const float4 Zero;
	static const float4 Null;

	static const float4 Red;
	static const float4 Blue;
	static const float4 Green;
	static const float4 White;
	static const float4 Black;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

	static float GetAngleVectorToVectorDeg(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	// 외적의 결과는 두개의 백터가 겹칠때 주의해서 처리해줘야 한다.
	static float GetAngleVectorToVectorRad(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right);

		float Angle = acosf(CosSeta);

		return Angle;
	}

	// 벡터외적 후 Normalize 리턴 
	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn()).NormalizeReturn();
	}

	// 외적
	// 면의 앞뒤구분, 무언가를 바라봐야할때 ( 더빠르게 회전할 수 있는 방향 )
	// 외적의 핵심은 수직인 벡터가 나온다는 것.
	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		//float4 ReturnValue;
		//ReturnValue.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		//ReturnValue.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		//ReturnValue.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);
		float4 ReturnValue = DirectX::XMVector3Cross(_Left, _Right);
		return ReturnValue;
	}

	// 내적
	// 내가 돌아야할 각도가 나온다. 
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		//            1         1          1          0          0          0
		// float Value = _Left.x * _Right.x + _Left.y * _Right.y + _Left.z * _Right.z;

		float4 ReturnValue = DirectX::XMVector3Dot(_Left, _Right);
		return ReturnValue.x;
	}

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float Arr1D[4];


		// 윈도우 지원 수학연산 가속(SIMD연산)을 사용하기 위한 다이렉트가 제공해주는 벡터 
		// 32비트에선 사용불가능
		DirectX::XMFLOAT3 DirectFloat3;
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;


		// 텍스쳐용
		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	float4(DirectX::FXMVECTOR _Vector)
		: DirectVector(_Vector)
	{

	}

	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}


	// 반환타입 unsigned int ??? 
	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	int uiw() const
	{
		return static_cast<unsigned int>(w);
	}

	int uhix() const
	{
		return static_cast<unsigned int>(x * 0.5f);
	}

	int uhiy() const
	{
		return static_cast<unsigned int>(y * 0.5f);
	}

	int uhiz() const
	{
		return static_cast<unsigned int>(z * 0.5f);
	}

	int uhiw() const
	{
		return static_cast<unsigned int>(w * 0.5f);
	}

	float GetAnagleDegZ()
	{
		return GetAnagleRadZ() * GameEngineMath::RadToDeg;
	}

	float MaxFloat() const
	{
		return (x < y) ? (y < z ? z : y) : (x < z ? z : x);
	}

	UINT ColorToUint() const
	{
		UINT Return;

		char* Ptr = reinterpret_cast<char*>(&Return);

		// 0~1
		Ptr[0] = static_cast<int>(r * 255.0f);
		Ptr[1] = static_cast<int>(g * 255.0f);
		Ptr[2] = static_cast<int>(b * 255.0f);
		Ptr[3] = static_cast<int>(a * 255.0f);

		return Return;
	}

	float4 RotationXDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationXRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotationYDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationYRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotationZDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationZRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	void RotationXRad(float _Rad);
	void RotationYRad(float _Rad);
	void RotationZRad(float _Rad);

	float4 EulerDegToQuaternion();
	class float4x4 QuaternionToRotationMatrix();
	float4 QuaternionToEulerDeg();
	float4 QuaternionToEulerRad();

	// 점과 점사이의 거리계산 
	float XYDistance(float4 _Value);
	float XYZDistance(float4 _Value);

	void RotationXDeg(float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationYDeg(float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZDeg(float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	float GetAnagleRadZ()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		float Result = acosf(AngleCheck.x);

		if (AngleCheck.y > 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}
		return Result;

	}

	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	// 노말라이즈
	void Normalize()
	{
		DirectVector = DirectX::XMVector3Normalize(*this);
	}

	float4 NormalizeReturn() const
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		// 1.5 + 0.5 * 2.5;
		return DirectX::XMVectorLerp(Start, End, Ratio);
	}

	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	operator DirectX::FXMVECTOR() const
	{
		return DirectVector;
	}

	bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}

	float4 operator *(const float _Value) const
	{
		return DirectX::XMVectorMultiply(*this, float4{ _Value , _Value , _Value , 1.0f });
	}


	float4 operator +(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	float4 operator -(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, -_Value);
		Return.w = PrevW;
		return Return;
	}

	float4 operator *(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorMultiply(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	float4 operator /(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, _Value);
		Return.w = PrevW;
		return Return;
	}


	float4 operator /(const float _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, { _Value , _Value , _Value , _Value });
		Return.w = PrevW;
		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, w };
	}

	float4& operator +=(const float4& _Other)
	{
		*this = *this + _Other;
		return *this;
	}

	float4& operator *=(const float _Value)
	{
		//x *= _Value;
		//y *= _Value;
		//z *= _Value;
		*this = *this * _Value;
		return *this;
	}

	float4& operator /=(const float _Value)
	{
		//x /= _Value;
		//y /= _Value;
		//z /= _Value;
		*this = *this / _Value;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		//x *= _Other.x;
		//y *= _Other.y;
		//z *= _Other.z;
		*this = *this * _Other;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		//x -= _Other.x;
		//y -= _Other.y;
		//z -= _Other.z;
		*this = *this - _Other;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		//x /= _Other.x;
		//y /= _Other.y;
		//z /= _Other.z;
		*this = *this / _Other;
		return *this;
	}

	float4 operator*(const class float4x4& _Other);
	float4& operator*=(const class float4x4& _Other);

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}
};

class CollisionDataAPI
{
public:
	float4 Position;
	float4 Scale; 

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}
	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}
	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}
	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};

typedef float4 Quaternion;

class float4x4
{
public:
	static const float4x4 Zero;

	static const int YCount = 4;
	static const int XCount = 4;

public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrVector[4];
		DirectX::XMMATRIX DirectMatrix;

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
	};

	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();

		/*memset(Arr1D, 0, sizeof(float) * 16);
		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;*/
	}

	//                                           1280 / 720
	//                         수직시야각        화면의 종횡비   근평면      원평면
	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle * GameEngineMath::DegToRad, _AspectRatio, _NearZ, _FarZ);

		//// 수직시야각이라면
		//float FOV = _FovAngle * GameEngineMath::DegToRad;
		////  _FovAngle * _AspectRatio;// 수평시야각 구하는법

		//// [0] [] [] []
		//// [] [0] [] []
		//// [] [] [0][1]
		//// [] [] [] [0]
		//Arr2D[2][3] = 1.0f;
		//Arr2D[3][3] = 0.0f;

		//Arr2D[0][0] = 1 / (tanf(FOV / 2.0f) * _AspectRatio);

		//// y 300
		//// z 5000
		//Arr2D[1][1] = 1 / tanf(FOV / 2.0f); // y / z

		//Arr2D[2][2] = _FarZ / (_FarZ - _NearZ);

		//Arr2D[3][2] = -( _NearZ * _FarZ) / (_FarZ - _NearZ);
	}

	// 직교투영
	void OrthographicLH(float _ScreenWidth, float _ScreenHeight, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixOrthographicLH(_ScreenWidth, _ScreenHeight, _NearZ, _FarZ);
	}

	//            화면의 너비
	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.0f, float _ZMax = 1.0f)
	{
		Identity();

		// 모니터의 공간으로 변환시키는 행렬
		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f;
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = _Height * 0.5f + _Right;
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
		Arr2D[3][3] = 1.0f;
	}

	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &_RotQuaternion.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	void DecomposeRotQuaternion(float4& _RotQuaternion)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &_RotQuaternion.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}

	void DecomposePos(float4& _Pos)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &Temp1.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	void DecomposeScale(float4& _Scale)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &Temp0.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}


	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);


		//float4 EyePos = _EyePos;

		//// 합쳐져서 회전행렬이 된다.
		//float4 EyeDir = _EyeDir.NormalizeReturn();
		//float4 EyeUp = _EyeUp;
		//float4 Right = float4::Cross3DReturn(EyeUp, EyeDir);
		//Right.Normalize();

		//float4 UpVector = float4::Cross3DReturn(_EyeDir, Right);
		//Right.Normalize();

		//float4 NegEyePos = -_EyePos;

		//float D0Value = float4::DotProduct3D(Right, NegEyePos);
		//float D1Value = float4::DotProduct3D(UpVector, NegEyePos);
		//float D2Value = float4::DotProduct3D(EyeDir, NegEyePos);

		//// 여기서 내적을 사용합니다.
		//// x + 1;
		//// 역함수 혹은 역행렬이라고 부릅니다.
		//// x - 1;

		//ArrVector[0] = Right;
		//ArrVector[1] = UpVector;
		//ArrVector[2] = EyeDir;

		//Transpose();

		//ArrVector[3] = { D0Value, D1Value, D2Value, 0 };
	}

	// 전치행렬이라고도 한다. 
	// 항등행렬을 기준으로 1인 부분을 반으로 갈라서 서로 반전시켜주는 거라고 보면 된다.
	void Transpose()
	{
		// 0   , 0, -1
		// 100 , 1,  0
		// 1   , 0,  0

		// 0 , 100,  1
		// 0,    1,  0
		// -1 ,  0,  0
		DirectMatrix = DirectX::XMMatrixTranspose(*this);

		//float4x4 This = *this;
		//Identity();
		//for (size_t y = 0; y < YCount; y++)
		//{
		//	for (size_t x = 0; x < XCount; x++)
		//	{
		//		Arr2D[x][y] = This.Arr2D[y][x];
		//	}
		//}

	}

	// 역행렬 
	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, *this);
	}

	float4x4 InverseReturn() const
	{
		float4x4 Return = *this;
		Return.Inverse();
		return Return;
	}


	void Scale(const float4& _Value)
	{
		//100, 0 , 0 , 0
		// 0 ,100, 0 , 0
		// 0 , 0 ,100, 0
		// 0 , 0 , 0 , 1
		Identity();
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value);
	}

	// 위치변환 = w, w를 신경써주어야함 
	void Pos(const float4& _Value)
	{
		//  0   1   2   3
		//0 0,  0 , 0 , 0
		//1 0 , 0,  0 , 0
		//2 0 , 0 , 0 , 0
		//3 200, 200 , 200 , 1
		Identity();
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value);

		//Arr2D[3][0] = _Value.x;
		//Arr2D[3][1] = _Value.y;
		//Arr2D[3][2] = _Value.z;
	}

	void RotationDeg(const float4& _Deg)
	{
		// 짐벌락 현상이라는 것이 있습니다.
		// 축이 겹치는 이상한 현상이 있는데 그 현상을 해결하려면
		// 곱하는 순서를 바꿔야 해결이 된다.
		// Rot = RotX * RotY * RotZ;

		// 기본적으로 쿼터니온 회전이라는걸 사용하는데 
		// 짐벌락 해결함.
		//float4x4 RotX = float4x4::Zero;
		//float4x4 RotY = float4x4::Zero;
		//float4x4 RotZ = float4x4::Zero;
		//RotX.RotationXDeg(_Deg.x);
		//RotY.RotationYDeg(_Deg.y);
		//RotZ.RotationZDeg(_Deg.z);

		// *this = RotX * RotY * RotZ;
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationX(_Rad);
		//Arr2D[1][1] = cosf(_Rad);
		//Arr2D[1][2] = sinf(_Rad);
		//Arr2D[2][1] = -sinf(_Rad);
		//Arr2D[2][2] = cosf(_Rad);
	}

	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationYRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationY(_Rad);

		//Arr2D[0][0] = cosf(_Rad);
		//Arr2D[0][2] = -sinf(_Rad);
		//Arr2D[2][0] = sinf(_Rad);
		//Arr2D[2][2] = cosf(_Rad);
	}

	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZRad(const float _Rad)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixRotationZ(_Rad);

		//Arr2D[0][0] = cosf(_Rad);
		//Arr2D[0][1] = sinf(_Rad);
		//Arr2D[1][0] = -sinf(_Rad);
		//Arr2D[1][1] = cosf(_Rad);
	}

	float4x4 operator*(const float4x4& _Other)
	{
		//  0   0   0   0			   		  0   0   0   0	    0   0   0   0
		//  0,  0 , 0 , 0			   		  0,  0 , 0 , 0	    0,  0 , 0 , 0
		//  0 , 0,  0 , 0          *   		  0 , 0,  0 , 0  =  0 , 0,  0 , 0
		//  0 , 0 , 0 , 0			   		  0 , 0 , 0 , 0	    0 , 0 , 0 , 0

		//this->Arr2D;
		//_Other.Arr2D;

		//float4x4 Return = Zero;
		//for (size_t y = 0; y < YCount; y++)
		//{
		//	for (size_t x = 0; x < XCount; x++)
		//	{
		//		for (size_t j = 0; j < 4; j++)
		//		{
		//			Return.Arr2D[y][x] += Arr2D[y][j] * _Other.Arr2D[j][x];
		//		}
		//	}
		//}

		float4x4 Return = DirectX::XMMatrixMultiply(*this, _Other);
		return Return;
	}

	float4x4& operator*=(const float4x4& _Other)
	{
		// *this = *this * _Other;
		DirectMatrix = DirectX::XMMatrixMultiply(*this, _Other);
		return *this;
	}

	// w 가 0인 곱하기
	float4 TransformNormal(const float4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}

	// w 가 1인 곱하기
	// 보통 coord를 사용하는 것이 일반적이지만 일단 w 에 1.0f 을 입력해주는 방식으로 진행할거임
	float4 TransformCoord(const float4& _Value)
	{
		return DirectX::XMVector3TransformCoord(_Value, *this);
	}

	operator DirectX::FXMMATRIX() const
	{
		return DirectMatrix;
	}

	float4x4()
	{
		Identity();
	}

	float4x4(DirectX::FXMMATRIX _DirectMatrix)
		: DirectMatrix(_DirectMatrix)
	{

	}

	float4x4(float4 _x, float4 _y, float4 _z, float4 _w)
	{
		ArrVector[0] = _x;
		ArrVector[1] = _y;
		ArrVector[2] = _z;
		ArrVector[3] = _w;
	}

};

