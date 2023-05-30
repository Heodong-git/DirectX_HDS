#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Timer : public BaseActor
{
public:
	static Timer* MainTimer;
public:
	// constrcuter destructer
	Timer();
	~Timer();

	// delete Function
	Timer(const Timer& _Other) = delete;
	Timer(Timer&& _Other) noexcept = delete;
	Timer& operator=(const Timer& _Other) = delete;
	Timer& operator=(Timer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	virtual void Reset();

	void GaugeUpdate();
	void Blink();
	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_GaugeRender = nullptr;

	int m_GaugeWidth = 200;
	int m_GaugeHeight = 25;

	const float m_FullGauge = 110.0f;
};
