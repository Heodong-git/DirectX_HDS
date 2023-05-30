#include "PrecompileHeader.h"
#include "ClubLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI ������ ���
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "StageEditer.h"
#include "Map.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "PlaySupporter.h"
#include "Timer.h"
#include "Inven.h"
#include "Monster_Gangster.h"
#include "Monster_Grunt.h"

ClubLevel_01::ClubLevel_01()
{
}

ClubLevel_01::~ClubLevel_01()
{
}



void ClubLevel_01::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	// �ʿ��� Ű����
	if (false == GameEngineInput::IsKey("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineInput::CreateKey("ClubLevel01_ChangeLevel_ClubLevel02", VK_F1);
		//GameEngineInput::CreateKey("ClubLevel01_ChangeLevel_ClubLevel00", VK_F2);
		GameEngineInput::CreateKey("ClubLevel01_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel01_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel01_ChangeMap", '2');
	}

	// �⺻ ���̸��� 0������. 0������ �����ҰŴϱ� 
	SetLevelType(LevelType::CLUBMAP1);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();

	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_01::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_02");
		return;
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_01::LevelChangeStart()
{
	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();

	// �������ʿ��� ���ʹ� ���� push 
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// �÷��̾� ��ġ����
	Push_ResetActor(CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	Player::MainPlayer->GetTransform()->SetLocalPosition(m_PlayerSetPos);

	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");

	// �÷��̾� ���͸� 
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));

	// Ŀ�� 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// �÷��̼�����
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));

	// Ÿ�̸�
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));

	// �κ�
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	{
		std::shared_ptr<Monster_Gangster> NewMonster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { -228.0f , 34.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
	{
		std::shared_ptr<Monster_Grunt> NewMonster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -348.0f , 34.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
	{
		std::shared_ptr<Monster_Grunt> NewMonster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 493.0f , 32.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
}

void ClubLevel_01::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_01::ResourcesLoad()
{
}

void ClubLevel_01::ActorLoad()
{
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("���� �÷��̾ nullptr �Դϴ�.");
		return;
	}
}

void ClubLevel_01::DebugUpdate()
{
}