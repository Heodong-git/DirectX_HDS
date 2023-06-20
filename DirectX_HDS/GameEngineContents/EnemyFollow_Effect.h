#pragma once
#include "BaseActor.h"

// Ό³Έν :
class EnemyFollow_Effect : public BaseActor
{
public:
	// constrcuter destructer
	EnemyFollow_Effect();
	~EnemyFollow_Effect();

	// delete Function
	EnemyFollow_Effect(const EnemyFollow_Effect& _Other) = delete;
	EnemyFollow_Effect(EnemyFollow_Effect&& _Other) noexcept = delete;
	EnemyFollow_Effect& operator=(const EnemyFollow_Effect& _Other) = delete;
	EnemyFollow_Effect& operator=(EnemyFollow_Effect&& _Other) noexcept = delete;

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	bool m_Direction = false;
	std::shared_ptr<GameEngineObject> m_FollowObj = nullptr;

	bool m_IsPivot = false;
	float4 m_Pivot = {};

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};
