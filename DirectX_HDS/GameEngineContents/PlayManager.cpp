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
}

void PlayManager::CameraSetting()
{
	// ó���� ������Ⱑ 00�̶� �ȵ��� �׷� �׳� �ٷ��� �ؼ� ���̳���ĳ��Ʈ
	// �ٵ� �̷��ʿ� ���� �׳� ���������ϸ� ���� ī�޶� �����ϸ� �ɰŰ�����'???? 
	// �ȵǳ�?? �׳��̷��� �� �����¸��� 
	// ��.. ���߿� ���� �����.. 
	// BaseLevel* Level = GetReturnCastLevel();

	GameEngineLevel* CurLevel = GameEngineCore::GetCurLevel().get();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel);

	if (nullptr == CurLevel)
	{
		MsgAssert("���� ������ nullptr �Դϴ�. Level �� Start ���� LevelType�� �����ϼ���.");
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
			CastLevel->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP0)]);
		}
		
	}
		break;
	case LevelType::CLUBMAP1:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP1)]);
		}
	}
		break;
	case LevelType::CLUBMAP2:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP2)]);
		}
	}
		break;
	case LevelType::CLUBMAP3:
	{
		if (nullptr != Player::MainPlayer)
		{
			CastLevel->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivots[static_cast<int>(LevelType::CLUBMAP3)]);
		}
	}
	break;
	default:
		break;
	}
}

void PlayManager::Start()
{
	if (0 == m_CameraPivots.size())
	{
		m_CameraPivots.reserve(8);

		m_CameraPivots.push_back(float4{ -360 , 34 , 0 });    // 0 
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 1 
		m_CameraPivots.push_back(float4{ -335 , -250 , 0 });  // 2
		m_CameraPivots.push_back(float4{ -912 , 1076 , 0 });		  // 3		������� ����
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });        // 4
		m_CameraPivots.push_back(float4{ 0 , 0 , 0 });		  // 5 
	}
}
