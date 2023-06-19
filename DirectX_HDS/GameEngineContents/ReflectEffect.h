#pragma once
#include "BaseActor.h"

// Ό³Έν :
class ReflectEffect	: public BaseActor
{
public:
	// constrcuter destructer
	ReflectEffect();
	~ReflectEffect();

	// delete Function
	ReflectEffect(const ReflectEffect& _Other) = delete;
	ReflectEffect(ReflectEffect&& _Other) noexcept = delete;
	ReflectEffect& operator=(const ReflectEffect& _Other) = delete;
	ReflectEffect& operator=(ReflectEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};
