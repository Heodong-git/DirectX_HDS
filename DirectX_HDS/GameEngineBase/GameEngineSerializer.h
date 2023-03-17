#pragma once
#include <vector>
#include <string>
#include <string_view>

// �����͸� ����Ʈ ���� char �迭�� ������ִ� �༮
// ����ȭ�� Ŭ������ ����� c++�� ���� ��� �����Լ������ͳ� 
// �����Ͱ��� �����غ��� ������� �����͵��� �� �����ϰ� �ʿ��� �����͸�
// ����Ʈ ������ �����ϴ°��� �ǹ��Ѵ�.

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

	// �迭 resize 
	void BufferResize(size_t _Size);
	
	// write
	void Write(const int& _Value);
	void Write(const std::string_view& _Value);
	void Write(const void* _Ptr, size_t _Size);


	// read
	void Read(int& _Value);
	void Read(std::string& _Value);
	void Read(void* _Ptr, size_t _Size);

	// ����� ������ ��ȯ 
	inline void* GetData()
	{
		return &Datas[0];
	}

	inline const void* GetConstData() const
	{
		return &Datas[0];
	}

	// �����°� ��ȯ
	inline size_t GetOffset() const
	{
		return Offset;
	}

	// ���� ����� �������� ũ�� ��ȯ
	inline size_t GetBufferSize() const
	{
		return Datas.size();
	}

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};

