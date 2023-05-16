#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "BaseLevel.h"
#include "Battery.h"

PlayManager* PlayManager::MainManager = nullptr;
PlayManager::LevelName PlayManager::m_LevelName = PlayManager::LevelName::NONE;

PlayManager::PlayManager()
{
	MainManager = this;
}

PlayManager::~PlayManager()
{
	
}

void PlayManager::Update(float _DeltaTime)
{
}

void PlayManager::CameraSetting()
{
	switch (m_LevelName)
	{
	case PlayManager::LevelName::NONE:
		break;
	case PlayManager::LevelName::CLUB:
	{
		// 현재레벨이 클럽레벨일 경우, 이 피봇을 적용
		m_CameraPivot = { -360, 34 , 0 };
		if (nullptr != Player::MainPlayer)
		{
			Player::MainPlayer->GetReturnCastLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivot);
		}
		
	}
		break;
	case PlayManager::LevelName::CLUBBOSS:
		break;
	default:
		break;
	}
}
