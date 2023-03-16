#include "GameEngineCore.h"
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>

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

void GameEngineCore::Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End)
{
	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1280, 720 }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::EngineStart, GameEngineCore::EngineUpdate, GameEngineCore::EngineEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name) 
{

}