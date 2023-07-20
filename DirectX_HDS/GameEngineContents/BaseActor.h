#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseLevel.h"

// 이펙트만 사용
enum class EffectState
{
	NORMAL,
	DEATH,
	RECORDING_PROGRESS,
	RECORDING_PROGRESS_FORWARD,
};

class ReverseInfo
{
public:
	TransformData ActorData;
	TransformData RendererData;
	SpriteInfo InfoData;
	bool IsRecording = false;
};

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

	// 인자로 값을 넣어주면, 1부터 인자로 넣어준 값까지의 랜덤한 값 반환 
	const int CreateRandomValue(const int _MAX);

	class BaseLevel* GetReturnCastLevel() const;

	inline void SetInitPos(float4& _Pos)
	{
		m_InitPos = _Pos;
	}

	inline const float4 GetInitPos() const
	{
		return m_InitPos;
	}

	virtual void BulletCollision() {};
	
	void SetDeath()
	{
		m_IsDeath = true;
	}

	// 베이스액터용 데스체크, 액터들의 히트그라운드 state 에서 데스 true로 변경해준다. 
	bool DeathCheck()
	{
		return m_IsDeath;
	}

	const inline bool IsRecording()
	{
		return m_Recording_Complete;
	}

	EffectState GetCurState()
	{
		return m_CurState;
	}
	
	virtual void ForcedReset();

protected:
	void ChangeState(EffectState _State)
	{
		m_CurState = _State;
	}

	EffectState m_CurState = EffectState::NORMAL;

	BaseLevel::LevelState GetLevelState();

	// 재생, 역재생 관련함수 
	void Reverse(class GameEngineSpriteRenderer* _Renderer);
	void InfoSetting(class GameEngineSpriteRenderer* _Renderer);

	void ClearInfo()
	{
		Infos.clear();
	}

	// ---------------------------------------------------- 
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

	bool m_IsDeath = false;

	// 레벨이 녹화진행중 인 상태에서, Infos 의 size가 0이 되면 
	// 내가 true 로 변경되는데, 녹화 진행중인 상태에서 스킵을 하고 싶다면?? 

	bool m_Recording_Complete = false;
	bool m_RecordingFrame = false;
	bool m_IsRecording = true;
	std::vector<ReverseInfo> Infos = std::vector<ReverseInfo>();
	size_t m_CurrentIdx = 0;

	// 정방향재생 state로 진입할때, 해당 변수에 현재 Infos.size - 1 을 저장한다. 
	size_t m_MaxIdx = 0;
	void SetMaxIndex()
	{
		if (0 >= Infos.size())
		{
			MsgAssert("현재 벡터의 사이즈가 0이하 입니다.");
			return;
		}

		const size_t Size = Infos.size();
		m_MaxIdx = Size - 1;
	}

private:

	// BaseActor들은 전부 얘를 오버라이드 
	virtual void Reset() {};
	float4 m_InitPos = {};
};
