#pragma once
#include "CKatanaZero_Actor.h"
// 설명 :
class GameEngineRenderer;
class CTitleManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CTitleManager();
	~CTitleManager();

	// delete Function
	CTitleManager(const CTitleManager& _Other) = delete;
	CTitleManager(CTitleManager&& _Other) noexcept = delete;
	CTitleManager& operator=(const CTitleManager& _Other) = delete;
	CTitleManager& operator=(CTitleManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderer> m_BackGroundRenderer;
	// 렌더러가 컴포넌트 리스트에 추가는 되고, 따로 사용하려면 가지고 있는게 편한가?
};
