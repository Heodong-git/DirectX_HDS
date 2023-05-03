#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

// TEST
#include "CTitleManager.h"
#include "CBackGround.h"

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

// imgui 테스트용
void CTitleLevel::TestFunction()
{
	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();
}

// 부모함수를 재정의 했기 때문에 이녀석이 호출됨
void CTitleLevel::Start()
{
	CKatanaZero_Level::Start();
	ResourcesLoad();
	ActorLoad();

	// imgui window 생성시 인터페이스, 윈도우를 생성하고 함수를 넘겨준다.
	// 각각의 레벨에서 imgui 로 사용할 함수들을 바인딩해주고 사용한다. 
	// 하 ㅡㅡ 
	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");

	if (nullptr == Window)
	{
		MsgAssert("테스트 코드 미작동");
		return;
	}

	Window->Test = std::bind(&CTitleLevel::TestFunction, this);
	Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);
}

void CTitleLevel::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
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
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
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