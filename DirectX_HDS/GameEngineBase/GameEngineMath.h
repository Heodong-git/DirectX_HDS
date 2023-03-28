#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>




// final 키워드 : 더이상 상속을 내리지 못하고 무언가 더 연장하지 못함

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
	static const float4 Zero;
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

	// 외적의 결과는 두개의 백터가 겹칠때 주의해서 처리해줘야 한다.
	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn()).NormalizeReturn();
	}

	// 벡터 외적
	// x y z x
	//  x x x     <-- 곱셈부호 , 이러한 형태로 벡터를 교차시켜 곱한다.  
	// x y z x
	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		float4 ReturnValue;
		ReturnValue.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		ReturnValue.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		ReturnValue.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);
		return ReturnValue;
	}

public:
	// 유니온
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float Arr1D[4];
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

	float GetAnagleDeg() 
	{
		return GetAnagleRad() * GameEngineMath::RadToDeg;
	}

	// 각축으로 회전시키고, 그 회전시킨 값을 반환한다. 
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

	void RotationXRad(float _Rad)
	{
		float4 Copy = *this;
		float Z = Copy.z;
		float Y = Copy.y;
		z = Z * cosf(_Rad) - Y * sinf(_Rad);
		y = Z * sinf(_Rad) + Y * cosf(_Rad);
	}

	void RotationYRad(float _Rad)
	{
		float4 Copy = *this;
		float X = Copy.x;
		float Z = Copy.z;
		x = X * cosf(_Rad) - Z * sinf(_Rad);
		z = X * sinf(_Rad) + Z * cosf(_Rad);
	}

	void RotationZRad(float _Rad)
	{
		float4 Copy = *this;
		float X = Copy.x;
		float Y = Copy.y;
		x = X * cosf(_Rad) - Y * sinf(_Rad);
		y = X * sinf(_Rad) + Y * cosf(_Rad);
	}

	float GetAnagleRad()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();
		// functon(1) == 50; 1을 50으로 바꾸는 함수
		// afuncton(50) == 1; 50이 1로 바꿔주는 함수라고도 할수 있지만 functon에 들어갔던 인자값을 알아내는 함수라고도 할수 있죠? <= 역함수
		
		// cosf(각도);

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
		return {x * 0.5f,y * 0.5f,z * 0.5f,w};
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	// 2, 0
	// 0, 2
	void Normalize() 
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}

	// 자기가 길이 1로 줄어든 애를 리턴해주는것.
	float4 NormalizeReturn() const
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		// 1.5 + 0.5 * 2.5;
		return Start * (1.0f - Ratio) + (End * Ratio);
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

	bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}



	float4 operator +(const float4& _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4& _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float4& _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	float4 operator /(const float4& _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return {-x, -y, -z, 1.0f};
	}

	float4& operator +=(const float4& _Other) 
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}


	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	float4 operator*(const class float4x4& _Other);

	std::string ToString() 
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}

};

class CollisionData
{
public:
	float4 Position;
	float4 Scale; // x만 원의 반지름으로 본다.

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
		return float4{Left(), Top()};
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

// 유니온으로 구성
// float 1차원배열
// float 2차원배열
// float4 로 구성된 배열 세가지로 볼 수 있음 
class float4x4
{
	static const float4x4 Zero;

	static const int YCount = 4;
	static const int XCount = 4;

private:
	float4x4(bool)
	{
		memset(Arr1D, 0, sizeof(float4x4));
	}

public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrVector[4];

		// 
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

	float4x4()
	{
		Identity();
	}

	// 행렬은 기본적으로 항등행렬을 기본으로 한다. 
	// 항등행렬 : 모든 대각 원소들이 1이며, 나머지 원소들이 0인 정방행렬을 말한다.
	void Identity()
	{
		memset(Arr1D, 0, sizeof(float) * 16);
		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;
	}

	// 크기행렬 
	void Scale(const float4& _Value)
	{
		//100, 0 , 0 , 0
		// 0 ,100, 0 , 0
		// 0 , 0 ,100, 0
		// 0 , 0 , 0 , 1

		Identity();
		Arr2D[0][0] = _Value.x;
		Arr2D[1][1] = _Value.y;
		Arr2D[2][2] = _Value.z;
	}

	// 위치행렬 
	void Pos(const float4& _Value)
	{
		//  0   1   2   3
		//0 0,  0 , 0 , 0
		//1 0 , 0,  0 , 0
		//2 0 , 0 , 0 , 0
		//3 200, 200 , 200 , 1

		Identity();
		Arr2D[3][0] = _Value.x;
		Arr2D[3][1] = _Value.y;
		Arr2D[3][2] = _Value.z;
	}

	float4x4 operator*(const float4x4& _Other)
	{
		//  0   0   0   0			   		  0   0   0   0	    0   0   0   0
		//  0,  0 , 0 , 0			   		  0,  0 , 0 , 0	    0,  0 , 0 , 0
		//  0 , 0,  0 , 0          *   		  0 , 0,  0 , 0  =  0 , 0,  0 , 0
		//  0 , 0 , 0 , 0			   		  0 , 0 , 0 , 0	    0 , 0 , 0 , 0

		this->Arr2D;
		_Other.Arr2D;

		float4x4 Return = Zero;
		for (size_t y = 0; y < YCount; y++)
		{
			for (size_t x = 0; x < XCount; x++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					Return.Arr2D[y][x] += Arr2D[y][j] * _Other.Arr2D[j][x];
				}
			}
		}

		return Return;
	}
};


// 행렬간의 곱셈은 순서에 따라서 결과값이 달라질 수 있기 때문에 순서에 유의해서 사용해야 한다. 
// 