#pragma once
#include "CKatanaZero_Actor.h"

enum class EMENU_TYPE
{
	NEWGAME,
	SETTING,
	EXIT,
	MAX,
};

// ���� : Ÿ��Ʋ�������� ����ϴ� ��� UI�� ����
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

	// �ؽ�Ʈ������ 
	float4 m_TextRenderOriginPos = float4{ 0 , -160 };
	std::shared_ptr<class GameEngineSpriteRenderer> m_NewGameTextRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_SettingTextRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_ExitTextRender = nullptr;

	// �޴� 
	EMENU_TYPE m_CurMenu = EMENU_TYPE::NEWGAME;
	std::vector<EMENU_TYPE> m_vecMenu;
	int m_CurIdx = 0;

	// ����ڽ� 
	std::shared_ptr<class GameEngineSpriteRenderer> m_TransparencyBoxRender = nullptr;
};
