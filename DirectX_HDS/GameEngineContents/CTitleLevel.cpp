#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CTitleManager.h"
#include "CTitleEditer.h"
#include "CBackGround.h"

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

// imgui 버튼생성 인터페이스 , 어. 
// 1. 실행할 클래스멤버함수를 생성
// 2. 코어윈도우를 상속받은 클래스를 만들어서 아래처럼 함수포인터를 넘겨준다. 
// std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
// Window->Test = std::bind(&CTitleLevel::TestFunction, this);
// Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);

// imgui 테스트용
//void CTitleLevel::TestFunction()
//{
//	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();
//}

void CTitleLevel::Start()
{
	if (false == GameEngineInput::IsKey("DebugChange_Tutorial"))
	{
		// GameEngineInput::CreateKey("DebugChange_Tutorial", VK_F1);
		GameEngineInput::CreateKey("DebugChange_Stage01", VK_F2);
	}

	ResourcesLoad();
	ActorLoad();
	SetState(ELEVEL_STATE::WAIT);
	CKatanaZero_Level::Start();
}

void CTitleLevel::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::IsDown("DebugChange_Tutorial"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
		return;
	}*/

	if (true == GameEngineInput::IsDown("DebugChange_Stage01"))
	{
		GameEngineCore::ChangeLevel("StageLevel_01");
		return;
	}

	
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTitleLevel::LevelChangeStart()
{
	m_GUI = GameEngineGUI::FindGUIWindowConvert<CTitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	
	m_GUI->On();
}

void CTitleLevel::LevelChangeEnd()
{
	m_GUI->Off();
	SetState(ELEVEL_STATE::WAIT);
}

void CTitleLevel::ResourcesLoad()
{
	// 디렉토리 클래스생성
	GameEngineDirectory NewDir;
	// 원하는 폴더를 가진 디렉터리로 이동
	NewDir.MoveParentToDirectory("katanazero_resources");
	// 그 폴더로 이동
	NewDir.Move("katanazero_resources");
	NewDir.Move("Texture");
	NewDir.Move("TitleLevel");

	// 파일 전체로드 
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd"});
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
}

void CTitleLevel::ActorLoad()
{
	// background 생성, 검은색깔개 + 뒷배경
	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();

	// Title 의 모든 UI 
	m_TitleManager = CreateActor<CTitleManager>("TitleUIManager");
	m_TitleManager->CreateRender();
}

/*
	// 람다 : 이름이 없는 함수를 만들어주는 기능
	// 두개의 인자를 받는 function 객체에
	// [](인자)
	// {
	// }
	// 의 형태로 이름없는 함수를 만들어 대입할 수 있다. 코드블록 내부에 동작할 코드 작성
	// 이런 형태로 이름 없는 함수를 만들어주고 내부에서 무언가를 하게 만든다.
	//std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test =
	//	[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	//{
	//	MsgTextBox("공격");

	//	_Manager->AddEvent(3.0f, TestFunction, false);
	//};

	//// 소유한 타임이벤트의 함수호출
	//// 람다 테스트용으로 만든 Test 함수를 호출 한것.
	//TimeEvent.AddEvent(5.0f, TestFunction, false);
*/