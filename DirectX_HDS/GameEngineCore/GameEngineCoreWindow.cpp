#include "PrecompileHeader.h"
#include "GameEngineCoreWindow.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineCoreWindow::GameEngineCoreWindow()
{
}

GameEngineCoreWindow::~GameEngineCoreWindow()
{
}

void GameEngineCoreWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	std::string Text = GameEngineString::AnsiToUTF8("ø¿»£»£»£√P");
	if (ImGui::Button(Text.c_str()))
	{
		
	}

	if (ImGui::Button("Test"))
	{
		
	}

	if (ImGui::Button("Test"))
	{
		
	}
}