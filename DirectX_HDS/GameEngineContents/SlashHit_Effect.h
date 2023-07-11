#pragma once
#include "BaseActor.h"

// 설명 :
class SlashHit_Effect : public BaseActor
{
public:
	// constrcuter destructer
	SlashHit_Effect();
	~SlashHit_Effect();

	// delete Function
	SlashHit_Effect(const SlashHit_Effect& _Other) = delete;
	SlashHit_Effect(SlashHit_Effect&& _Other) noexcept = delete;
	SlashHit_Effect& operator=(const SlashHit_Effect& _Other) = delete;
	SlashHit_Effect& operator=(SlashHit_Effect&& _Other) noexcept = delete;

	void SetObject(std::shared_ptr<GameEngineObject> _Obj);
	inline void SetDir(const bool _Dir)
	{
		m_Direction = _Dir;
	}

	inline void SetPivot(const float4 _Pivot)
	{
		m_IsPivot = true;
		m_Pivot = _Pivot;
	}

	void ChangeState(EffectState _State)
	{
		m_CurState = _State;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	bool m_Direction = false;
	std::shared_ptr<GameEngineObject> m_FollowObj = nullptr;

	bool m_IsPivot = false;
	float4 m_Pivot = {};
	// 렌더러생성 및 세팅
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
};
