#pragma once
#include "BaseActor.h"
// Ό³Έν :
class Platform : public BaseActor
{
public:
	// constrcuter destructer
	Platform();
	~Platform();

	// delete Function
	Platform(const Platform& _Other) = delete;
	Platform(Platform&& _Other) noexcept = delete;
	Platform& operator=(const Platform& _Other) = delete;
	Platform& operator=(Platform&& _Other) noexcept = delete;

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
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
};
