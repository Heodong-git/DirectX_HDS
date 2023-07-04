#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "BaseLevel.h"

class ReverseInfo
{
public:
	TransformData ActorData;
	TransformData RendererData;
	SpriteInfo InfoData;
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

protected:
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
	bool m_Recording_Complete = false;
	bool m_RecordingFrame = false;
	
private:
	std::list<ReverseInfo> Infos = std::list<ReverseInfo>();

	// BaseActor���� ���� �긦 �������̵� 
	virtual void Reset() {};
	float4 m_InitPos = {};
};
