#include "PrecompileHeader.h"
#include "ClubLevel_00.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI ������ ���
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// ������
#include "PlayManager.h"
#include "Cursor.h"
#include "Player.h"
#include "CameraMovement.h"
#include "Monster_Gangster.h"
#include "StageEditer.h"
#include "Battery.h"
#include "Map.h"
#include "Inven.h"
#include "Timer.h"
#include "Hud.h"
#include "FadeInOut_Effect.h"

ClubLevel_00::ClubLevel_00()
{
}

ClubLevel_00::~ClubLevel_00()
{
}

void ClubLevel_00::Start()
{
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	// �ʿ��� Ű����
	// ���� ���̽������� ������ �ɰŰ����� 
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

	// ī�޶� ����Ʈ ����
	// �̷� �÷� ��� 
	// m_FadeEffect = GetLastTarget()->CreateEffect<FadeInOut_Effect>();
}

void ClubLevel_00::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_01");
		return;
	}


	// ������Ʈ�� ��� BaseLevel::LevelState::WAIT �� PLAY �϶��� ������Ʈ �ϰ� ������ �ʿ��� �Լ��� ȣ���ϵ��� �Ұ�

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_00::LevelChangeStart()
{
	//����ü�����ϸ鼭 imgui �� on ��ų�� ��Ŀ���� �����Ǵ���
	//���� start �� �⺻ �������̽�

	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	
	m_GUI->On();

	// �ʿ��� ���� ����, �ʱ�ȭ(����)
	CreateActor<PlayManager>();
	PlayManager::MainManager->CameraSetting();

	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_00::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_00::ResourcesLoad()
{
	// ���� ���ҽ��ε� 
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

// 00 ���������� ��ŸƮ���� 
void ClubLevel_00::ActorLoad()
{
	// �� 
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// �÷��̾�
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	NewPlayer->GetTransform()->AddLocalPosition(PlayerSetPos);
	
	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");

	// �÷��̾� ���͸� 
	CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery");

	// Ŀ�� 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// ī�޶�
	CreateActor<CameraMovement>();

	// Ÿ�̸�
	CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer");

	// �κ�
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
	Monster->GetTransform()->SetLocalPosition({ 0.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
}

void ClubLevel_00::DebugUpdate()
{
}


