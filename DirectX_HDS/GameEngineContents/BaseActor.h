#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BaseActor : public GameEngineActor
{
	// 레벨에서 초기상태로 리셋하게 될 경우
	// 액터들을 초기상태로 설정하기 위함 
	friend class BaseLevel;
public:
	// constrcuter destructer
	BaseActor();
	~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	// 필요한가..? ㅇㅇ 필요함 
	class BaseLevel* GetReturnCastLevel() const;

protected:
	void Update(float _DeltaTime) override;

	// 디버그 스위치
	virtual void DebugSwitch()
	{
		if (true == IsDebug())
		{
			DebugOff();
		}

		else if (false == IsDebug())
		{
			DebugOn();
		}
	}

private:

	
	// -------------------------recording info-------------------------------
	// 역재생에 필요한 녹화될 정보들을 아래 부분에 작성하고, 함수를 그 정보들을 저장하고, 로드하는 함수를 구현? 
};
