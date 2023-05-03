#pragma once
#include "CKatanaZero_Actor.h"

enum class EMENU_TYPE
{
	NEWGAME,
	SETTING,
	EXIT,
	MAX,
};

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
	void MenuUpdate(float _DeltaTime);
	void FenceRenderMove(float _DeltaTime);

	bool m_Arrive = false;
	
	std::shared_ptr<class GameEngineSpriteRenderer> m_KatanaRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ZERRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ORender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_FenceRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_PlantsRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TranslucentBoxRender = nullptr;

	// 텍스트렌더러 
	float4 m_TextRenderOriginPos = float4{ 0 , -160 };
	std::shared_ptr<class GameEngineSpriteRenderer> m_NewGameTextRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_SettingTextRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ExitTextRender = nullptr;

	// 메뉴 
	EMENU_TYPE m_CurMenu = EMENU_TYPE::NEWGAME;
	std::vector<EMENU_TYPE> m_vecMenu;
	int m_CurIdx = 0;

	// 투명박스 
	std::shared_ptr<class GameEngineSpriteRenderer> m_TransparencyBoxRender = nullptr;
};
