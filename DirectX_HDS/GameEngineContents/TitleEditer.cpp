#include "PrecompileHeader.h"
#include "TitleEditer.h"

#include <GameEngineCore/GameEngineCore.h>

TitleEditer::TitleEditer()
{
}

TitleEditer::~TitleEditer()
{
}

void TitleEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::BeginMenu("LevelChange"))
	{
		std::string Text = GameEngineString::AnsiToUTF8("LevelChange");
		ImGui::Text(Text.c_str());

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

		// 메뉴를 열었으면 반드시 닫아야 하는듯, 안닫으면  터짐
		ImGui::EndMenu();
	}
}
