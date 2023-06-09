#include "PrecompileHeader.h"
#include "IronDoor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

IronDoor::IronDoor()
{
}

IronDoor::~IronDoor()
{
}

void IronDoor::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
}

void IronDoor::Update(float _DeltaTime)
{
	DebugUpdate();
	UpdateState(_DeltaTime);
	
}

void IronDoor::Render(float _DeltaTime)
{
}

void IronDoor::Reset()
{
	// ���� ���� ���»��¶�� Ŭ���� ���·� ���� 
	if (IronDoorState::OPEN == m_CurState)
	{
		ChangeState(IronDoorState::CLOSE);
	}
}

void IronDoor::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("gangster_debugswitch"))
	{
		DebugSwitch();

		if (nullptr != m_Collision)
		{
			if (true == m_Collision->IsDebug())
			{
				m_Collision->DebugOff();
			}

			else
			{
				m_Collision->DebugOn();
			}
		}

		if (true == IsDebug())
		{
			m_DebugRender->On();
		}

		else if (false == IsDebug())
		{
			m_DebugRender->Off();
		}
	}
}

void IronDoor::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DOOR);
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivotY });
	//m_MainRender->GetTransform()->SetLocalScale({ 50.0f , 100.0f });
	m_MainRender->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::DOOR);
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ -m_ColPivot / 2.0f , m_ColPivot });

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
	m_DebugRender->Off();
}

void IronDoor::LoadAndCreateAnimation()
{
	// ��������Ʈ������ nullptr �϶��� 
	if (nullptr == GameEngineSprite::Find("slash"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("door");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("iron_door").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_MainRender->CreateAnimation({ .AnimationName = "iron_door", .SpriteName = "iron_door", .Start = 0, .End = 19 ,
								.FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->ChangeAnimation("iron_door");
	m_MainRender->SetAnimPauseOn();
}

// -------------------------------------------- State ----------------------------------------------------

void IronDoor::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case IronDoorState::CLOSE:
		CloseUpdate(_DeltaTime);
		break;
	case IronDoorState::OPEN:
		OpenUpdate(_DeltaTime);
		break;
	}
}

// state ����, ����� ������ start, ���� ������ end ����
void IronDoor::ChangeState(IronDoorState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case IronDoorState::CLOSE:
		CloseStart();
		break;
	case IronDoorState::OPEN:
		OpenStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case IronDoorState::CLOSE:
		CloseEnd();
		break;
	case IronDoorState::OPEN:
		OpenEnd();
		break;
	}
}

void IronDoor::CloseStart()
{
	m_MainRender->ChangeAnimation("iron_door");
	m_MainRender->SetAnimPauseOn();
	m_Collision->On();
}

void IronDoor::CloseUpdate(float _DeltaTime)
{
	// ���� �÷��̾� ���ݰ� �浹�ߴٸ�
	// ���� �÷��̾��� ���ݰ� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// ������ ���Դٴ°� �浹�ߴٴ°Ű� 
	// �׷� �浹�� ���͸� ������Ű�� �������� ȣ�� 
	if (nullptr != Col)
	{
		// ���� �浹ü�� off
		// �ִϸ��̼� ������ �����ִϸ��̼�������ȯ 
		m_Collision->Off();
		ChangeState(IronDoorState::OPEN);
	}
}

void IronDoor::CloseEnd()
{
}

void IronDoor::OpenStart()
{
	m_MainRender->SetAnimPauseOff();
}

void IronDoor::OpenUpdate(float _DeltaTime)
{
}

void IronDoor::OpenEnd()
{
}
