#pragma once
#include "BaseActor.h"

// 설명 :
class YouCanDoThis : public BaseActor
{
public:
	// constrcuter destructer
	YouCanDoThis();
	~YouCanDoThis();

	// delete Function
	YouCanDoThis(const YouCanDoThis& _Other) = delete;
	YouCanDoThis(YouCanDoThis&& _Other) noexcept = delete;
	YouCanDoThis& operator=(const YouCanDoThis& _Other) = delete;
	YouCanDoThis& operator=(YouCanDoThis&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 렌더러생성 및 세팅
	void ComponentSetting();
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
};
