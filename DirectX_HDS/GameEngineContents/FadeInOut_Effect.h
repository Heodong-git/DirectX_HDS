#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// 설명 :
class FadeInOut_Effect : GameEnginePostProcess
{
public:
	// constrcuter destructer
	FadeInOut_Effect();
	~FadeInOut_Effect();

	// delete Function
	FadeInOut_Effect(const FadeInOut_Effect& _Other) = delete;
	FadeInOut_Effect(FadeInOut_Effect&& _Other) noexcept = delete;
	FadeInOut_Effect& operator=(const FadeInOut_Effect& _Other) = delete;
	FadeInOut_Effect& operator=(FadeInOut_Effect&& _Other) noexcept = delete;

protected:
	void Start(std::shared_ptr<GameEngineRenderTarget> _Target) override;
	void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) override;

private:

};

// 1. 포스트프로세스 클래스를 상속받고
// 2. 스타트, 이펙트 함수를 재정의한다. 
// 3. 이펙트를 구현했다면 사용할 레벨에서 해당 이펙트객체를 사용할 수 있게 들고 있는다. 
// 4. 사용할 레벨의 Start 에서 effect create 
// 