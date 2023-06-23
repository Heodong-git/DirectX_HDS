#pragma once
#include "BaseActor.h"

// Ό³Έν :
class TeleportEffect : public BaseActor
{
public:
	// constrcuter destructer
	TeleportEffect();
	~TeleportEffect();

	// delete Function
	TeleportEffect(const TeleportEffect& _Other) = delete;
	TeleportEffect(TeleportEffect&& _Other) noexcept = delete;
	TeleportEffect& operator=(const TeleportEffect& _Other) = delete;
	TeleportEffect& operator=(TeleportEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	size_t m_DeathCount = 0;
	size_t m_RenderCount = 20;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> m_SparkRenders;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
};
