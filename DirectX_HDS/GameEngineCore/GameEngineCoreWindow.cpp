#include "PrecompileHeader.h"
#include "GameEngineCoreWindow.h"

GameEngineCoreWindow::GameEngineCoreWindow()
{
}

GameEngineCoreWindow::~GameEngineCoreWindow()
{
}

void GameEngineCoreWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::Button("Button1"))
	{
		if (nullptr != Test)
		{
			Test();
		}
	}

	if (ImGui::Button("Button2"))
	{
		if (nullptr != Test1)
		{
			Test1();
		}
	}
}