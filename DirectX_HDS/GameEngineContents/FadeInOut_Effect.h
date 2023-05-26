#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// ���� :
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

// 1. ����Ʈ���μ��� Ŭ������ ��ӹް�
// 2. ��ŸƮ, ����Ʈ �Լ��� �������Ѵ�. 
// 3. ����Ʈ�� �����ߴٸ� ����� �������� �ش� ����Ʈ��ü�� ����� �� �ְ� ��� �ִ´�. 
// 4. ����� ������ Start ���� effect create 
// 