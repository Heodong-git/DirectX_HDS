#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 게임액터들의 정보 
class CRecordingInfo
{
public:
	float4 LocalScale = {};
	float4 LocalPos = {};
	float  MoveSpeed = 0.0f;
};



class CKatanaZero_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	CKatanaZero_Actor();
	~CKatanaZero_Actor();

	// delete Function
	CKatanaZero_Actor(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor(CKatanaZero_Actor&& _Other) noexcept = delete;
	CKatanaZero_Actor& operator=(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor& operator=(CKatanaZero_Actor&& _Other) noexcept = delete;

	// 자신의 정보를 세이브,로드하는 기능.. 인데 
	// 각자 가지고 있는 변수가 다르다... 흠 
	// 액터레코딩인포 클래스를 만들어서 가지고 있게 하고 그 클래스 내부의 변수를 사용?
	inline std::shared_ptr<CRecordingInfo> GetRecordingInfo()
	{
		return m_RecordingInfo;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	// -------------------------recording info-------------------------------
	// 역재생에 필요한 녹화될 정보들을 아래 부분에 작성하고, 함수를 그 정보들을 저장하고, 로드하는 함수를 구현? 
	std::shared_ptr<CRecordingInfo> m_RecordingInfo = nullptr;
};
