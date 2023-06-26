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
	void LoadAndCreateAnimation();
	void SetRenders();
	size_t m_FirstRenderCount = 8;
	size_t m_SecondRenderCount = 4;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> m_SparkRenders;

	size_t m_CloudRenderCount = 2;
	size_t m_CloudRenderCount2 = 5;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> m_CloudRenders;

	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
};
