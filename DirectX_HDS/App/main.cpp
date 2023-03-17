#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>

// 테스트
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
// 라이브러리 디렉터리 설정으로 인해 lib 파일 앞쪽에 상대경로가 포함되어 있는 것이고, 아래처럼 사용가능
#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)	
{
	{
		// 데이터 저장이 필요한 녀석
		TPlayer Test;

		// 그녀석의 데이터를 저장할 녀석
		GameEngineSerializer Ser;
		// 시리얼라이저에 데이터 저장
		Test.TestSave(Ser);
		// 원하는 경로에 파일을 생성하고 저장
		GameEngineFile File = GameEngineFile("..\\Test.test");
		File.SaveBin(Ser);

		const type_info& Info = typeid(Test);

		std::cout << Info.name() << std::endl;

		const char* Name = Info.name();

		int a = 0;
	}

	{
		// 데이터를 불러와서 저장할녀석
		TMonster Test;
		// 데이터를 로드해서 저장해둘 시리얼라이저
		GameEngineSerializer Ser;
		// 현재 불러올 데이터가 저장되어 있는 파일
		GameEngineFile File = GameEngineFile("..\\Test.test");
		// 파일에 저장되어 있는 데이터를 시리얼라이저에 로드
		File.LoadBin(Ser);
		// 현재 파일이 시리얼라이저에 저장되어 있기 때문에 
		// 적용이 필요한 몬스터에 로드 
		Test.TestLoad(Ser);

		Test;
	}
}

// 3월 17일 해야할일 목록
// 1. 코드 읽으면서 주석 다시 하나하나 달면서 체크 
// 2. 파일입출력, Rtti , 한번씩 확인해보면서 공부.