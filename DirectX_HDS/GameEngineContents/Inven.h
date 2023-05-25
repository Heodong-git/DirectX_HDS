#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Inven : public BaseActor
{
public:
	// constrcuter destructer
	Inven();
	~Inven();

	// delete Function
	Inven(const Inven& _Other) = delete;
	Inven(Inven&& _Other) noexcept = delete;
	Inven& operator=(const Inven& _Other) = delete;
	Inven& operator=(Inven&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Blink();
	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_LeftRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_RightRender = nullptr;
};
