#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "TitleManager.h"
#include "TitleEditer.h"
#include "TitleBackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GetMainCamera()->SetSortType(0, SortType::YSort);

	ResourcesLoad();
	ActorLoad();
	SetState(BaseLevel::LevelState::WAIT);
	BaseLevel::Start();
}

void TitleLevel::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::IsDown("DebugChange_Tutorial"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
		return;
	}*/

	BaseLevel::Update(_DeltaTime);
}

void TitleLevel::LevelChangeStart()
{
	/*m_GUI = GameEngineGUI::FindGUIWindowConvert<TitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	
	m_GUI->On();*/
}

void TitleLevel::LevelChangeEnd()
{
	if (m_GUI != nullptr)
	{
		m_GUI->Off();
	}

	SetState(BaseLevel::LevelState::WAIT);
}

void TitleLevel::ResourcesLoad()
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

	if (nullptr == GameEngineSprite::Find("player_idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("TitleSub");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Plants_Anim").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
}

void TitleLevel::ActorLoad()
{
	// background 생성, 검은색깔개 + 뒷배경
	std::shared_ptr<TitleBackGround> NewBackGround = CreateActor<TitleBackGround>();

	// Title 의 모든 UI 와 연산 사실상 얘가 다하는걸로
	m_TitleManager = CreateActor<TitleManager>();
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