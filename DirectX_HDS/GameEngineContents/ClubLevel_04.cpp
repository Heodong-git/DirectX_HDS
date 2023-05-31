#include "PrecompileHeader.h"
#include "ClubLevel_04.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	float4 InitPos = {0.0f , 0.0f };
	ActorInit(NewPlayer, InitPos);
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