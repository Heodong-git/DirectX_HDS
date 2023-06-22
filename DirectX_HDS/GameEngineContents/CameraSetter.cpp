#include "PrecompileHeader.h"
#include "CameraSetter.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "BaseLevel.h"
#include "Battery.h"

CameraSetter* CameraSetter::MainCamSetter = nullptr;
std::vector<float4> CameraSetter::m_CameraPivots = std::vector<float4>();

CameraSetter::CameraSetter()
{
	MainCamSetter = this;
}

CameraSetter::~CameraSetter()
{
}

void CameraSetter::Update(float _DeltaTime)
{
}

void CameraSetter::CameraSetting()
{
	GameEngineLevel* CurLevel = GameEngineCore::GetCurLevel().get();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel);

	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다. ");
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
	case LevelType::CLUBMAP4:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP4)]);
		}
	}
		break;
	case LevelType::CLUBBOSS0:
	{
		if (nullptr != Player::MainPlayer)
		{
			// 1번맵과 동일하게 그자리에서 보여주면 되기 때문에 1번맵의 피봇을 그대로 사용한다. 
			CastLevel->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP1)]);
		}
	}
		break;
	}
}

bool CameraSetter::PlayerDeathCheck()
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

void CameraSetter::Reset()
{
	CameraSetting();
}

void CameraSetter::Start()
{
	// 맵별 카메라세팅
	if (0 == m_CameraPivots.size())
	{
		m_CameraPivots.reserve(8);

		m_CameraPivots.push_back(float4{ -360.0f , 34.0f , 0 });    // 0 
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 1 
		m_CameraPivots.push_back(float4{ -335.0f , -250.0f , 0 });  // 2
		m_CameraPivots.push_back(float4{ -135.52f, 356.0f });	  // 3		여기부터 설정
		m_CameraPivots.push_back(float4{ -638.82f , -384.76f});        // 4
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 5 
	}

}
