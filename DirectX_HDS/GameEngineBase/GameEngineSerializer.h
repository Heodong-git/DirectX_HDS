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

	std::string GetString();

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};



// ------------------ ���� ���� ----------------------------- 
// 1. ������ ������ �غ�    
// TPlayer TestPlayer;
// 2. �����͸� ������ �ø�������� �غ�
// GameEngineSerializer Ser;
// 3. �����͸� �ø���������� ���� (�̶� ��ü ���ο��� �ø���������� write �Լ����)
// TestPlayer.TestSave(Ser);
// 4. ������ ��ο� ���� ����, �����ڿ��� ����Է�
// GameEngineFile File = GameEngineFile("..\\PlayerData.Data");
// 5. ������ ���Ͽ� ��� ���·� ������ ������ ���ؼ� �����Լ� ���
// File.SaveBin(Ser);

// �Ʒ�ó�� Ŭ�������ο� Save, Load �Լ��� ��ü������ �����ΰ� ����� �� ����
/*void TestSave(GameEngineSerializer _Ser)
	{
		_Ser.Write(TestName);
		_Ser.Write(TestAtt);
		_Ser.Write(TestDef);
	}

	void TestLoad(GameEngineSerializer _Ser)
	{
		_Ser.Read(TestName);
		_Ser.Read(TestAtt);
		_Ser.Read(TestDef);
	}*/


// ------------------- ���� �ε� ------------------------------
// 1. ������ �ε��Ͽ� ������ ��ü �غ�
// TPlayer TestPlayer;
// 2. ������ �ε��� �ø�������� �غ�
// GameEngineSerializer Ser;
// 3. ���ϴ� ��ο� �ִ� ������ �޾ƿ´�. 
// ex) GameEngineFile File = GameEngineFile("C:\\DirectX_HDS\\DirectX_HDS\\PlayerData.Data");
// 4. �غ�� Serializer �� �ε�
// File.LoadBin(Ser);
// 5. Serializer �� ����Ǿ� �ִ� �����͸� ������ ��ü�� �ε� 
// TestPlayer.TestLoad(Ser); 

// typeinfo ����
// const type_info& Info = typeid(Test); Ÿ�Ծ��̵��� ���ڿ� ����, ������ Ÿ���� �־��ָ�
// Info.name(); �Լ��� ����Ͽ� � Ŭ�������� Ȯ���� �� ����.