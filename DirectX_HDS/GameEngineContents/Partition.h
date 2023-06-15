#pragma once
#include "BaseActor.h"
// Ό³Έν :
class Partition : public BaseActor
{
public:
	// constrcuter destructer
	Partition();
	~Partition();

	// delete Function
	Partition(const Partition& _Other) = delete;
	Partition(Partition&& _Other) noexcept = delete;
	Partition& operator=(const Partition& _Other) = delete;
	Partition& operator=(Partition&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCollision> GetCollision()
	{
		return m_Collision;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();
	void ComponentSetting();
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	float4 m_Scale = float4{ 5.0f , 200.0f };
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
};
