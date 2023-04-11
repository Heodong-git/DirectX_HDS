#include "PrecompileHeader.h"
#include "GameEngineSerializer.h"
#include "GameEngineDebug.h"

GameEngineSerializer::GameEngineSerializer() 
{
}

GameEngineSerializer::~GameEngineSerializer() 
{
}

void GameEngineSerializer::BufferResize(size_t _Size)
{
	Datas.resize(_Size);
}

void GameEngineSerializer::Write(const int& _Value)
{
	Write(&_Value, sizeof(int));
}

void GameEngineSerializer::Write(const std::string_view& _Value)
{
	int Size = static_cast<int>(_Value.size());
	Write(&Size, sizeof(int));
	Write(_Value.data(), Size);
}


void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	// 현재 배열의 크기 체크, 배열이 꽉찼다면
	// 배열 resize 
	if (Datas.size() <= Offset + _Size)
	{
		Datas.resize(Datas.size() + 1024);
	}

	// 배열에 메모리를 복사한다. 
	memcpy_s(&Datas[Offset], Datas.size() - Offset, _Ptr, _Size);

	// 현재 size <-- 크기의 메모리가 저장됐기 때문에 offset 의 값을 그만큼 더해준다.
	Offset += _Size;
}

// 값을 읽어온다.
void GameEngineSerializer::Read(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameEngineSerializer::Read(std::string& _Value)
{
	int Size = 0;
	Read(&Size, sizeof(int));
	_Value.clear();
	_Value.resize(Size);
	Read(_Value.data(), Size);
}

void GameEngineSerializer::Read(void* _Ptr, size_t _Size)
{
	//  1024             1023   + 4
	if (Datas.size() <= Offset + _Size)
	{
		MsgAssert("데이터의 한도이상으로 읽으려고 했습니다.");
	}

	memcpy_s(_Ptr, _Size, &Datas[Offset], _Size);

	Offset += _Size;
}