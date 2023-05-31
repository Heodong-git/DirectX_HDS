#include "PrecompileHeader.h"
#include "ClubLevel_00.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI ������
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

// ������
#include "CameraSetter.h"
#include "PlaySupporter.h"
#include "Player.h"
#include "Cursor.h"
#include "Battery.h"
#include "Timer.h"
#include "Inven.h"
#include "Hud.h"
#include "Map.h"
#include "Monster_Gangster.h"
#include "Monster_Pomp.h"
#include "Monster_Grunt.h"
#include "StageEditer.h"
#include "IronDoor.h"
#include "FadeEffect.h"

ClubLevel_00::ClubLevel_00()
{
}

ClubLevel_00::~ClubLevel_00()
{
}

// ���� Start �⺻ �������̽� 
void ClubLevel_00::Start()
{
	GUISetting();
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubLevel01", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel_ChangeMap", '2');
	}

	// �⺻ ���̸��� 0������. 0������ �����ҰŴϱ� 
	SetLevelType(LevelType::CLUBMAP0);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();
}

void ClubLevel_00::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_01");
		return;
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_00::LevelChangeStart()
{
	// ī�޶� �Ǻ�����
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// ���� �� ������ PLAY ���·� ����
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_00::LevelChangeEnd()
{
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	// GUI �� ������̶�� Off
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_00::ResourcesLoad()
{
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Map");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

// ���ͷε� �⺻ �������̽� 
// �ʱ�ȭ �ʿ��� ���ʹ� Push_ResetActor
void ClubLevel_00::ActorLoad()
{
	//float4 ScreenSize = GameEngineWindow::GetScreenSize();

	// ���� �����ϰ�, ����� �ؽ��Ĥ��� ����
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	// �÷��̾�
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	NewPlayer->GetTransform()->AddLocalPosition(m_PlayerSetPos);
	Push_ResetActor(NewPlayer);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// Ŀ��
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// �̸� �����ұ�~~~ 
	{
		// �Լ��� ����� ���� �� �����ϴ�.. 
		std::shared_ptr<Monster_Gangster> NewGangster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { 584.0f , -94.0f };
		NewGangster->GetTransform()->SetLocalPosition(InitPos);
		NewGangster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewGangster);
	}
	
	{
		std::shared_ptr<Monster_Pomp> NewPomp = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { -202.0f , -94.0f };
		NewPomp->GetTransform()->SetLocalPosition(InitPos);
		NewPomp->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewPomp);
	}
	{
		std::shared_ptr<Monster_Pomp> NewPomp = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { -1.0f , -94.0f };
		NewPomp->GetTransform()->SetLocalPosition(InitPos);
		NewPomp->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewPomp);
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -474.0f , -94.0f };
		NewGrunt->GetTransform()->SetLocalPosition(InitPos);
		NewGrunt->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewGrunt);
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 40.0f , -94.0f };
		NewGrunt->GetTransform()->SetLocalPosition({ 404.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
		NewGrunt->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewGrunt);
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 344.0f , -94.0f };
		NewGrunt->GetTransform()->SetLocalPosition(InitPos);
		NewGrunt->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewGrunt);
	}
	{
		// ���� ������ ���� ���ݾ�? 
		std::shared_ptr<IronDoor> NewDoor = CreateActor<IronDoor>(static_cast<int>(RenderOrder::DOOR), "IronDoor");
		NewDoor->GetTransform()->SetLocalPosition({ -67.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
		Push_ResetActor(NewDoor);
	}

	// �÷��̼�����
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
}

void ClubLevel_00::GUISetting()
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
