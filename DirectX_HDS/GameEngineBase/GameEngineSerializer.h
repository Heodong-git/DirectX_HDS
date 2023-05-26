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

	std::string GetString();

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};



// ------------------ 파일 저장 ----------------------------- 
// 1. 저장할 데이터 준비    
// TPlayer TestPlayer;
// 2. 데이터를 저장할 시리얼라이저 준비
// GameEngineSerializer Ser;
// 3. 데이터를 시리얼라이저에 저장 (이때 객체 내부에서 시리얼라이저의 write 함수사용)
// TestPlayer.TestSave(Ser);
// 4. 저장할 경로에 파일 생성, 생성자에서 경로입력
// GameEngineFile File = GameEngineFile("..\\PlayerData.Data");
// 5. 생성한 파일에 어떠한 형태로 저장할 것인지 정해서 저장함수 사용
// File.SaveBin(Ser);

// 아래처럼 클래스내부에 Save, Load 함수를 자체적으로 만들어두고 사용할 수 있음
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


// ------------------- 파일 로드 ------------------------------
// 1. 파일을 로드하여 저장할 객체 준비
// TPlayer TestPlayer;
// 2. 파일을 로드할 시리얼라이저 준비
// GameEngineSerializer Ser;
// 3. 원하는 경로에 있는 파일을 받아온다. 
// ex) GameEngineFile File = GameEngineFile("C:\\DirectX_HDS\\DirectX_HDS\\PlayerData.Data");
// 4. 준비된 Serializer 에 로드
// File.LoadBin(Ser);
// 5. Serializer 에 저장되어 있는 데이터를 저장할 객체에 로드 
// TestPlayer.TestLoad(Ser); 

// typeinfo 사용법
// const type_info& Info = typeid(Test); 타입아이디의 인자에 변수, 데이터 타입을 넣어주면
// Info.name(); 함수를 사용하여 어떤 클래스인지 확인할 수 있음.