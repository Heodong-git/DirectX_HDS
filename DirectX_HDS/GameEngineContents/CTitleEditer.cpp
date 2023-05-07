#include "PrecompileHeader.h"
#include "CTitleEditer.h"

CTitleEditer::CTitleEditer()
{
}

CTitleEditer::~CTitleEditer()
{
}

void CTitleEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	std::string Text = GameEngineString::AnsiToUTF8("Tutorial_Level");
	if (ImGui::Button(Text.c_str()))
	{

	}

	Text = GameEngineString::AnsiToUTF8("Stage01_Level");
	if (ImGui::Button(Text.c_str()))
	{

	}

	Text = GameEngineString::AnsiToUTF8("Stage02_Level");
	if (ImGui::Button(Text.c_str()))
	{

	}
}
