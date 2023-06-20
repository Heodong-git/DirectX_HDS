#include "PrecompileHeader.h"
#include "ClubLevel_04.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "StageEditer.h"
#include "PlaySupporter.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Hud.h"
#include "Battery.h"
#include "Inven.h"
#include "Timer.h"
#include "Map.h"
#include "Cursor.h"
#include "Platform.h"
#include "Monster_Grunt.h"
#include "Monster_Gangster.h"
#include "Monster_Pomp.h"
#include "Laser.h"
#include "IronDoor.h"
#include "Partition.h"

ClubLevel_04::ClubLevel_04()
{
}

ClubLevel_04::~ClubLevel_04()
{
}

void ClubLevel_04::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	SetLevelType(LevelType::CLUBMAP4);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();

	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_04::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_04::LevelChangeStart()
{
	GUISetting();

	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// �÷��̾� ��ġ����
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = float4 { -1142.82f, -682.76f };
	ActorInit(NewPlayer, InitPos);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// ������, Ŀ��
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	CreateObjAndInit();

	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_04::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_04::ResourcesLoad()
{
}

void ClubLevel_04::ActorLoad()
{
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_04.png");
}

void ClubLevel_04::KeyUpdate()
{
}

void ClubLevel_04::CreateKey()
{
}

void ClubLevel_04::CreateObjAndInit()
{
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -462.0f, -237.62f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 167.28f, -236.51f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { 106.0f, 20.24f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -656.37f, 275.24f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { -170.0f, 274.24f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Pomp> Monster = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { -365.0f, -684.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Pomp> Monster = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { 1147.0f, 467.24f };
		ActorInit(Monster, InitPos);
	}
	
	// ù��° 
	{
		std::shared_ptr<Platform> NewPlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		NewPlatform->GetTransform()->SetLocalPosition(float4{ -320.0f , -179.0f });
		NewPlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 150.0f, 10.0f });
	}

	// �ι�°
	{
		std::shared_ptr<Platform> NewPlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		NewPlatform->GetTransform()->SetLocalPosition(float4{ 339.0f , 82.0f });
		NewPlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 450.0f, 10.0f });
	}

	// ����° 
	{
		std::shared_ptr<Platform> NewPlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		NewPlatform->GetTransform()->SetLocalPosition(float4{ -457.0f , 334.0f });
		NewPlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 430.0f, 10.0f });
	}

	// �������� �����ʿ� �װ�, ������ �װ� ����� ���� �θ� �������ش�.
	{
		m_LaserRight = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		m_LaserRight->GetTransform()->SetLocalPosition(float4{ 300.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		m_LaserRight->SetLaserScale(Scale);
	}

	// ���� �������� ���� ���ٿ��ش�
	// �θ���� �������־���� 
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ 270.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ 240.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ 210.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	
	// ���� 
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -815.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -840.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -865.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -890.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -915.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -940.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		NewLaser->GetTransform()->SetLocalPosition(float4{ -965.0f , 370.0f });
		float4 Scale = float4{ 5.0f , 190.0f };
		NewLaser->SetLaserScale(Scale);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -715.0f, -682.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -179.0f, -682.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -179.0f, -682.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -851.0f, -236.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 414.0f, -236.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 580.0f, 18.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -449.0f, 18.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -782.0f, 275.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 835.0f, 275.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 861.0f, 471.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 1420.0f, 471.0f };
		ActorInit(PartitionObj, InitPos);
	}
}

void ClubLevel_04::GUISetting()
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