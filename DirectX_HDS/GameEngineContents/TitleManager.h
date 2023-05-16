#pragma once
#include "BaseActor.h"

enum class EMENU_TYPE
{
	NEWGAME,
	SETTING,
	EXIT,
	CHANGE,
	MAX,
};

// 설명 : 타이틀레벨에서 사용하는 모든 UI를 관리
class TitleManager : public BaseActor
{
public:
	// constrcuter destructer
	TitleManager();
	~TitleManager();

	// delete Function
	TitleManager(const TitleManager& _Other) = delete;
	TitleManager(TitleManager&& _Other) noexcept = delete;
	TitleManager& operator=(const TitleManager& _Other) = delete;
	TitleManager& operator=(TitleManager&& _Other) noexcept = delete;
	
	// 사용할 렌더러 생성
	void CreateRender();
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 메뉴 업데이트
	void MenuUpdate(float _DeltaTime);

	// UI 이동연산
	void FenceRenderMove(float _DeltaTime);
	void KatanaRenderMove(float _DeltaTime);
	void ZERRenderMove(float _DeltaTime);
	void ORenderMove(float _DeltaTime);
	void BoxRenderMove(float _DeltaTime);
	
	// Text 렌더러 이동연산
	void TextMove(float _DeltaTime);

	// 메뉴선택창의 text 의 렌더러 on 
	void TextMenuOn();

	// 타이틀화면의 ZERO <-- 텍스트 깜빡이는거처럼 보이도록, 렌더러 ON,OFF 
	void BlinkRender();

	// 렌더러 이동 완료여부 
	bool m_FenceArrive = false;
	bool m_KatanaArrive = false;
	bool m_ZERArrive = false;
	bool m_OArrive = false;

	bool m_TextMoveArrive = false;
	bool m_BoxMoveArrive = false;

	bool m_AllRenderArrive = false;

	// Katana ZERO 렌더 
	std::shared_ptr<class GameEngineSpriteRenderer> m_KatanaRender = nullptr;
	float4 m_KatanaRenderPos = float4{ 0.0f , 100.0f };
	std::shared_ptr<class GameEngineSpriteRenderer> m_ZERRender = nullptr;
	float4 m_ZERRenderPos = float4{ -55.0f , 30.0f };
	std::shared_ptr<class GameEngineSpriteRenderer> m_ORender = nullptr;
	float4 m_ORenderPos = float4{ 160.0f , 30.0f };

	// 나머지 텍스트를 제외한 렌더
	std::shared_ptr<class GameEngineSpriteRenderer> m_FenceRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_PlantsRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TranslucentBoxRender = nullptr;
	float4 m_TranslucentBoxRenderPos = float4{ 0 , -210.0f };

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
	std::shared_ptr<class GameEngineSpriteRenderer> m_MenuSelectBoxRender = nullptr;
	
	// 점멸간격
	float m_BoxFlashingTime = 0.6f;

	// 각 텍스트메뉴들의 초기위치설정
	float4 m_MenuMovePos = float4{ 0.0f, -50.0f };
	float4 m_MenuStartPos = float4{ 0.0f , -160.0f };
	float4 m_MenuMiddlePos = float4{ 0.0f , -210.0f };
	float4 m_MenuEndPos = float4{ 0.0f, -260.0f };
};
