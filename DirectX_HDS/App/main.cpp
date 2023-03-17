#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>

// �׽�Ʈ
#include <typeinfo>
#include <iostream>

class Parent
{

};

class TPlayer : public Parent
{
public:
	// constrcuter destructer
	TPlayer()
	{

	}
	~TPlayer()
	{

	}

	// delete Function
	TPlayer(const TPlayer& _Other) = delete;
	TPlayer(TPlayer&& _Other) noexcept = delete;
	TPlayer& operator=(const TPlayer& _Other) = delete;
	TPlayer& operator=(TPlayer&& _Other) noexcept = delete;

	std::string TestName = "ZERO";
	int TestAtt = 10;
	int TestDef = 304512;

	void TestSave(GameEngineSerializer& _Ser)
	{
		_Ser.Write(TestName);
		_Ser.Write(TestAtt);
		_Ser.Write(TestDef);
	}

	void TestLoad(GameEngineSerializer& _Ser)
	{
		_Ser.Read(TestName);
		_Ser.Read(TestAtt);
		_Ser.Read(TestDef);
	}

protected:

private:

	
};

class TMonster
{
public:
	// constrcuter destructer
	TMonster()
	{

	}
	~TMonster()
	{

	}

	// delete Function
	TMonster(const TMonster& _Other) = delete;
	TMonster(TMonster&& _Other) noexcept = delete;
	TMonster& operator=(const TMonster& _Other) = delete;
	TMonster& operator=(TMonster&& _Other) noexcept = delete;

	std::string TestName = "MONSTER";
	int TestAtt = 10;
	int TestDef = 3045;

	void TestSave(GameEngineSerializer& _Ser)
	{
		_Ser.Write(TestName);
		_Ser.Write(TestAtt);
		_Ser.Write(TestDef);
	}

	void TestLoad(GameEngineSerializer& _Ser)
	{
		_Ser.Read(TestName);
		_Ser.Read(TestAtt);
		_Ser.Read(TestDef);
	}

protected:

private:


};
// ���̺귯�� ���͸� �������� ���� lib ���� ���ʿ� ����ΰ� ���ԵǾ� �ִ� ���̰�, �Ʒ�ó�� ��밡��
#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)	
{
	{
		// ������ ������ �ʿ��� �༮
		TPlayer Test;

		// �׳༮�� �����͸� ������ �༮
		GameEngineSerializer Ser;
		// �ø���������� ������ ����
		Test.TestSave(Ser);
		// ���ϴ� ��ο� ������ �����ϰ� ����
		GameEngineFile File = GameEngineFile("..\\Test.test");
		File.SaveBin(Ser);

		const type_info& Info = typeid(Test);

		std::cout << Info.name() << std::endl;

		const char* Name = Info.name();

		int a = 0;
	}

	{
		// �����͸� �ҷ��ͼ� �����ҳ༮
		TMonster Test;
		// �����͸� �ε��ؼ� �����ص� �ø��������
		GameEngineSerializer Ser;
		// ���� �ҷ��� �����Ͱ� ����Ǿ� �ִ� ����
		GameEngineFile File = GameEngineFile("..\\Test.test");
		// ���Ͽ� ����Ǿ� �ִ� �����͸� �ø���������� �ε�
		File.LoadBin(Ser);
		// ���� ������ �ø���������� ����Ǿ� �ֱ� ������ 
		// ������ �ʿ��� ���Ϳ� �ε� 
		Test.TestLoad(Ser);

		Test;
	}
}

// 3�� 17�� �ؾ����� ���
// 1. �ڵ� �����鼭 �ּ� �ٽ� �ϳ��ϳ� �޸鼭 üũ 
// 2. ���������, Rtti , �ѹ��� Ȯ���غ��鼭 ����.