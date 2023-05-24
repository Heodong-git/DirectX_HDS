#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Battery : public BaseActor
{
public:
	static Battery* MainBattery;

public:
	// constrcuter destructer
	Battery();
	~Battery();

	// delete Function
	Battery(const Battery& _Other) = delete;
	Battery(Battery&& _Other) noexcept = delete;
	Battery& operator=(const Battery& _Other) = delete;
	Battery& operator=(Battery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> m_CaseRender = nullptr;

	std::shared_ptr<class MySpriteRenderer> m_TestRender = nullptr;
};
