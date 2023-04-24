#include "PrecompileHeader.h"
#include "CTitleManager.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

CTitleManager::CTitleManager()
{
}

CTitleManager::~CTitleManager()
{
}

void CTitleManager::Start()
{
	if (false == GameEngineInput::IsKey("TitleMenu_Up"))
	{
		GameEngineInput::CreateKey("TitleMenu_Up", 'w');
		GameEngineInput::CreateKey("TitleMenu_Down", 's');
		GameEngineInput::CreateKey("TitleMenu_Select", VK_SPACE);
	}
}

void CTitleManager::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("TitleMenu_Select"))
	{
		int a = 0; 
	}
}

void CTitleManager::Render(float _DeltaTime)
{
}
