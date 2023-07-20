#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseLevel.h"

// ����Ʈ�� ���
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
	// �������� �ʱ���·� �����ϰ� �� ���
	// ���͵��� �ʱ���·� �����ϱ� ���� 
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

	// ���ڷ� ���� �־��ָ�, 1���� ���ڷ� �־��� �������� ������ �� ��ȯ 
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

	// ���̽����Ϳ� ����üũ, ���͵��� ��Ʈ�׶��� state ���� ���� true�� �������ش�. 
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

	// ���, ����� �����Լ� 
	void Reverse(class GameEngineSpriteRenderer* _Renderer);
	void InfoSetting(class GameEngineSpriteRenderer* _Renderer);

	void ClearInfo()
	{
		Infos.clear();
	}

	// ---------------------------------------------------- 
	void Update(float _DeltaTime) override;

	// ����� ����ġ
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

	// ������ ��ȭ������ �� ���¿���, Infos �� size�� 0�� �Ǹ� 
	// ���� true �� ����Ǵµ�, ��ȭ �������� ���¿��� ��ŵ�� �ϰ� �ʹٸ�?? 

	bool m_Recording_Complete = false;
	bool m_RecordingFrame = false;
	bool m_IsRecording = true;
	std::vector<ReverseInfo> Infos = std::vector<ReverseInfo>();
	size_t m_CurrentIdx = 0;

	// ��������� state�� �����Ҷ�, �ش� ������ ���� Infos.size - 1 �� �����Ѵ�. 
	size_t m_MaxIdx = 0;
	void SetMaxIndex()
	{
		if (0 >= Infos.size())
		{
			MsgAssert("���� ������ ����� 0���� �Դϴ�.");
			return;
		}

		const size_t Size = Infos.size();
		m_MaxIdx = Size - 1;
	}

private:

	// BaseActor���� ���� �긦 �������̵� 
	virtual void Reset() {};
	float4 m_InitPos = {};
};
