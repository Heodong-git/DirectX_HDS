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
		MsgAssert("���� ������ nullptr �Դϴ�. ");
		return;
	}

	LevelType Type = CastLevel->GetLevelType();

	switch (Type)
	{
	case LevelType::NONE:
	{
		MsgAssert("���� ����Ÿ���� NONE �Դϴ�. Level �� Start���� LevelType�� �����ϼ���.");
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
			// 1���ʰ� �����ϰ� ���ڸ����� �����ָ� �Ǳ� ������ 1������ �Ǻ��� �״�� ����Ѵ�. 
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
	// �ʺ� ī�޶���
	if (0 == m_CameraPivots.size())
	{
		m_CameraPivots.reserve(8);

		m_CameraPivots.push_back(float4{ -360.0f , 34.0f , 0 });    // 0 
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 1 
		m_CameraPivots.push_back(float4{ -335.0f , -250.0f , 0 });  // 2
		m_CameraPivots.push_back(float4{ -135.52f, 356.0f });	  // 3		������� ����
		m_CameraPivots.push_back(float4{ -638.82f , -384.76f});        // 4
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 5 
	}

}
