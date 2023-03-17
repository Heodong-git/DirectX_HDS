#include "GameEngineCore.h"
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>

// static 으로 선언했기 때문에 cpp 상단에 구현
std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

void GameEngineCore::EngineStart() 
{

}
void GameEngineCore::EngineUpdate() 
{

}
void GameEngineCore::EngineEnd()
{

}

// ? 
void GameEngineCore::Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End)
{
	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	// 메인윈도우생성
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1280, 720 }, { 0, 0 });

	// 윈도우 루프 실행
	// 아직 코드 작성 안해서 그런거같은데 아마?도?
	GameEngineWindow::WindowLoop(GameEngineCore::EngineStart, GameEngineCore::EngineUpdate, GameEngineCore::EngineEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name) 
{

}