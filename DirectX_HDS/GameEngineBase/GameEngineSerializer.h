#pragma once
#include <vector>
#include <string>
#include <string_view>

// 데이터를 바이트 단위 char 배열로 만들어주는 녀석
// 직렬화란 클래스를 만들면 c++로 예를 들면 가상함수포인터나 
// 포인터같은 저장해봐야 쓸모없는 데이터들을 다 제외하고 필요한 데이터만
// 바이트 단위로 변경하는것을 의미한다.

class GameEngineSerializer
{
public:
	// constrcuter destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	// delete Function
	GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	// 배열 resize 
	void BufferResize(size_t _Size);
	
	// write
	void Write(const int& _Value);
	void Write(const std::string_view& _Value);
	void Write(const void* _Ptr, size_t _Size);


	// read
	void Read(int& _Value);
	void Read(std::string& _Value);
	void Read(void* _Ptr, size_t _Size);

	// 저장된 데이터 반환 
	inline void* GetData()
	{
		return &Datas[0];
	}

	inline const void* GetConstData() const
	{
		return &Datas[0];
	}

	// 오프셋값 반환
	inline size_t GetOffset() const
	{
		return Offset;
	}

	// 현재 저장된 데이터의 크기 반환
	inline size_t GetBufferSize() const
	{
		return Datas.size();
	}

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};

