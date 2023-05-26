#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player.h"
#include "BaseLevel.h"
#include "Battery.h"

PlayManager* PlayManager::MainManager = nullptr;
std::vector<float4> PlayManager::m_CameraPivots = {};


PlayManager::PlayManager()
{
	MainManager = this;
}

PlayManager::~PlayManager()
{
	
}

void PlayManager::Update(float _DeltaTime)
{
	// 플레이어 사망시 맵크기만큼의 충돌체 생성, 그리고 플레이어가 죽었을때만 
	// 커서가 충돌체를 생성하게 만들고, 그 충돌체가 여기 매니저에서 만든 충돌체랑 충돌하게 되면 둘다 death 시키고 
	// 레벨을 리셋한다. .. 어 .. ㅋ ㅋㅋ 
	if (true == PlayerDeathCheck())
	{
		int a = 0;
	}
}

void PlayManager::CameraSetting()
{
	// 처음에 만든레벨가 00이라서 안들어옴 그럼 그냥 겟레벨 해서 다이나믹캐스트
	// 근데 이럴필요 없이 그냥 레벨시작하면 지가 카메라 세팅하면 될거같은데'???? 
	// 안되네?? 그냥이렇게 써 이유는몰라 
	// 음.. 나중에 문제 생기면.. 
	// BaseLevel* Level = GetReturnCastLevel();

	GameEngineLevel* CurLevel = GameEngineCore::GetCurLevel().get();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel);

	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다. Level 의 Start 에서 LevelType를 세팅하세요.");
		return;
	}

	LevelType Type = CastLevel->GetLevelType();

	switch (Type)
	{
	case LevelType::NONE:
	{
		MsgAssert("현재 레벨타입이 NONE 입니다. Level 의 Start에서 LevelType를 세팅하세요.");
		return;
	}
		break;
	case LevelType::CLUBMAP0:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP0)]);
		}
		
	}
		break;
	case LevelType::CLUBMAP1:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP1)]);
		}
	}
		break;
	case LevelType::CLUBMAP2:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP2)]);
		}
	}
		break;
	case LevelType::CLUBMAP3:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP3)]);
		}
	}
	break;
	default:
		break;
	}
}

bool PlayManager::PlayerDeathCheck()
{
	if (nullptr == Player::MainPlayer)
	{
		return false;
	}


	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return true;
	}

	return false;
}

void PlayManager::Start()
{
	// 맵별 카메라세팅
	if (0 == m_CameraPivots.size())
	{
		m_CameraPivots.reserve(8);

		m_CameraPivots.push_back(float4{ -360 , 34 , 0 });    // 0 
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 1 
		m_CameraPivots.push_back(float4{ -335 , -250 , 0 });  // 2
		m_CameraPivots.push_back(float4{ -72 , 356 , 0 });		  // 3		여기부터 설정
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });        // 4
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 5 
	}

}
