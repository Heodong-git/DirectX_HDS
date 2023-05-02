#pragma once
#include "CKatanaZero_Actor.h"

// 설명 : 타이틀레벨에서 사용하는 모든 UI를 관리
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
	
	void CreateRender();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void FenceRenderMove(float _DeltaTime);
	
	std::shared_ptr<class GameEngineSpriteRenderer> m_KatanaRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ZERRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ORender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_FenceRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_PlantsRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TranslucentBoxRender = nullptr;
};
