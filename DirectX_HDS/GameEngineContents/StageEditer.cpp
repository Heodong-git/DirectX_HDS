#include "PrecompileHeader.h"
#include "StageEditer.h"

#include <GameEngineCore/GameEngineCore.h>

StageEditer::StageEditer()
{
}

StageEditer::~StageEditer()
{
}

void StageEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::BeginMenu("LevelChange"))
	{
		std::string Text = GameEngineString::AnsiToUTF8("LevelChange");
		ImGui::Text(Text.c_str());

		//Text = GameEngineString::AnsiToUTF8("Tutorial_Level");
		//if (ImGui::Button(Text.c_str()))
		//{
		//	// 그냥 호출해도 되지 않을까
		//	GameEngineCore::ChangeLevel("TutorialLevel");
		//	ImGui::EndMenu();
		//	return;
		//}

		Text = GameEngineString::AnsiToUTF8("StageLevel_01");
		if (ImGui::Button(Text.c_str()))
		{
			GameEngineCore::ChangeLevel("StageLevel_01");
			ImGui::EndMenu();
			return;
		}

		Text = GameEngineString::AnsiToUTF8("TitleLevel");
		if (ImGui::Button(Text.c_str()))
		{
			GameEngineCore::ChangeLevel("TitleLevel");
			ImGui::EndMenu();
			return;
		}

		ImGui::EndMenu();
	}
}
