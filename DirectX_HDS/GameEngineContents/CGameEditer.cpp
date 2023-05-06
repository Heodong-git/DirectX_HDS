#include "PrecompileHeader.h"
#include "CGameEditer.h"

CGameEditer::CGameEditer()
{
}

CGameEditer::~CGameEditer()
{
}

void CGameEditer::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
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
