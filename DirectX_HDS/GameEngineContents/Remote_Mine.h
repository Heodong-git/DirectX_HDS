#pragma once
#include "BaseActor.h"

enum class MineState
{
	GROUND,
	EXPLOSION,
};

// 설명 :
class Remote_Mine : public BaseActor
{
public:
	// constrcuter destructer
	Remote_Mine();
	~Remote_Mine();

	// delete Function
	Remote_Mine(const Remote_Mine& _Other) = delete;
	Remote_Mine(Remote_Mine&& _Other) noexcept = delete;
	Remote_Mine& operator=(const Remote_Mine& _Other) = delete;
	Remote_Mine& operator=(Remote_Mine&& _Other) noexcept = delete;

	void AddTimeLimit(const float _Limit)
	{
		m_TimeLimit = m_TimeLimit + _Limit;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 세팅하지 않으면 1.0f, 세팅하면 기존 1.0f 에 추가 
	float m_TimeLimit = 1.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;

	MineState m_CurState = MineState::GROUND;

	// 내위치를 기준으로 한 폭발 이펙트 생성지점 push
	std::vector<float4> m_ExplosionPos = std::vector<float4>();
	size_t m_ExplosionPosCount = 12;
};
