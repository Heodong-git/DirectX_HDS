#pragma once
#include "CKatanaZero_Actor.h"

// ���� : Ÿ��Ʋ�������� ����ϴ� ��� UI�� ����
class GameEngineRenderer;
class CTitleUIManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CTitleUIManager();
	~CTitleUIManager();

	// delete Function
	CTitleUIManager(const CTitleUIManager& _Other) = delete;
	CTitleUIManager(CTitleUIManager&& _Other) noexcept = delete;
	CTitleUIManager& operator=(const CTitleUIManager& _Other) = delete;
	CTitleUIManager& operator=(CTitleUIManager&& _Other) noexcept = delete;

	//const std::list <std::shared_ptr<class GameEngineActor>>& GetUIList() const
	//{
	//	return m_UIList;
	//}
	
	void CreateRender();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//std::list <std::shared_ptr<class GameEngineActor>> m_UIList;
	std::shared_ptr<class GameEngineSpriteRenderer> m_KatanaRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ZERRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ORender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_FenceRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_PlantsRender = nullptr;
};
