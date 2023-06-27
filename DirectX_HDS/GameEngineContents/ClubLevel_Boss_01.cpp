#include "PrecompileHeader.h"
#include "ClubLevel_Boss_01.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "StageEditer.h"
#include "PlaySupporter.h"
#include "Boss_HeadHunter.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Hud.h"
#include "Battery.h"
#include "Inven.h"
#include "Timer.h"
#include "Map.h"
#include "Cursor.h"
#include "Platform.h"

#include "GunSmoke_Effect.h"
#include "GunSpark_Effect2.h"



ClubLevel_Boss_01::ClubLevel_Boss_01()
{
}

ClubLevel_Boss_01::~ClubLevel_Boss_01()
{
}

void ClubLevel_Boss_01::CreateHeadHunter()
{
	m_Appear = true;
	std::shared_ptr<Boss_HeadHunter> Boss = CreateActor<Boss_HeadHunter>(static_cast<int>(RenderOrder::BOSS), "Boss_HeadHunter");
	float4 InitPos = float4{ 358.0f, -263.0f };
	ActorInit(Boss, InitPos);
	Boss->ChangePhase(BossPhase::SECOND);
}

void ClubLevel_Boss_01::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();
	SetLevelType(LevelType::CLUBBOSS1);
	ResourcesLoad();
	ActorLoad();

	// �ӽ�
	SetState(BaseLevel::LevelState::WAIT);
}

// ������Ʈ������, �÷��̾ IDLE ���·� ����ȴٸ� 
// �����ѰŰ�, �׼����� Ư����ġ�� ������� ����
// �׳� �ٴڿ� �浹ü �ϳ� �����ΰ�, �� �ٴ��浹ü��, �÷��̾�� �浹�ߴٸ� PLAY ���·� ����, 
// ������ �÷��̾���ġ�� 
void ClubLevel_Boss_01::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
	if (true == m_ColCheckObj->IsUpdate())
	{
		LevelStartCheck();
	}
}

void ClubLevel_Boss_01::LevelStartCheck()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = m_ColCheckObj->GetCollision()->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerCol)
	{
		m_ColCheckObj->Off();
		SetState(BaseLevel::LevelState::PLAY);
		CreateHeadHunter();
	}


}

void ClubLevel_Boss_01::LevelChangeStart()
{
	GUISetting();

	// ī�޶� �Ǻ�����
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// �÷��̾� ��ġ����
	// ���ʵ��� ��ġ�� ���� �������ش�. 
	// �ʱ�ȭ ��ġ�� �������ְ� 
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 FallPos = { -343.0f, 68.0f };
	float4 InitPos = { -334.0f, -264.0f };
	ActorInit(NewPlayer, InitPos);
	NewPlayer->GetTransform()->SetLocalPosition(FallPos);
	NewPlayer->ChangeState(PlayerState::FALL);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// ������, Ŀ��
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	CreateObjAndInit();
}

void ClubLevel_Boss_01::LevelChangeEnd()
{
	SetState(BaseLevel::LevelState::WAIT);

	Player::MainPlayer->Death();

	// GUI Off 
	// GUI �� ������̶�� Off
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_Boss_01::ResourcesLoad()
{
}

void ClubLevel_Boss_01::ActorLoad()
{
	// �ӽ÷� 0���� ����
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetTexture("ClubMap_Boss_01.png");
	m_Map->GetRender()->GetTransform()->SetLocalScale(float4{ 1280.0f, 720.0f });
}

void ClubLevel_Boss_01::CreateObjAndInit()
{
	// ���� ���۽ÿ� �÷����ϳ� �����, �� �÷����� �÷��̾ �浹�ߴٸ� PLAY 
	{
		m_ColCheckObj = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		m_ColCheckObj->GetTransform()->SetLocalPosition(float4{ 0.0f , -264.0f });
		m_ColCheckObj->GetCollision()->GetTransform()->SetLocalScale(float4{ 1280.0f, 2.0f });
	}
}

void ClubLevel_Boss_01::KeyUpdate()
{
}

void ClubLevel_Boss_01::CreateKey()
{
}

void ClubLevel_Boss_01::GUISetting()
{
	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();
}
