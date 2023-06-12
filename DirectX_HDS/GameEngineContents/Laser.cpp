#include "PrecompileHeader.h"
#include "Laser.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::SetLaserScale(float4& _Scale)
{
	m_LaserScale = _Scale;
	m_LaserRender->GetTransform()->SetLocalScale(m_LaserScale);
	m_TopRender->GetTransform()->SetLocalPosition(float4{ 0.0f, m_LaserScale.y / 2.0f });
	m_Collision->GetTransform()->SetLocalScale(float4{ m_LaserScale.x / 2.0f , m_LaserScale.y });
}

void Laser::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
}

void Laser::Update(float _DeltaTime)
{
	DebugUpdate();
	UpdateState(_DeltaTime);
}

void Laser::Render(float _DeltaTime)
{
}

void Laser::Reset()
{
	m_CurState = LaserState::IDLE;
}

void Laser::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
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
	}
}

void Laser::ComponentSetting()
{
	m_LaserRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::LASER);
	m_TopRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::LASER);
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::LASER);
	m_Collision->GetTransform()->SetLocalScale(float4{ 2.0f, 460.0f });
}

void Laser::LoadAndCreateAnimation()
{
	// ��������Ʈ������ nullptr �϶��� 
	if (nullptr == GameEngineSprite::Find("laser_idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("laser");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("laser_idle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("laser_col").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("laser_on").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("laser_off").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_LaserRender->CreateAnimation({ .AnimationName = "laser_idle", .SpriteName = "laser_idle", .Start = 0, .End = 3 ,
							.FrameInter = 0.03f , .Loop = true , .ScaleToTexture = false });

	m_LaserRender->CreateAnimation({ .AnimationName = "laser_col", .SpriteName = "laser_col", .Start = 0, .End = 1 ,
						.FrameInter = 0.075f , .Loop = true , .ScaleToTexture = false });

	m_LaserRender->ChangeAnimation("laser_idle");
	m_LaserRender->GetTransform()->SetLocalScale(float4{ 4.0f, 460.0f });
	m_TopRender->SetScaleToTexture("laser_on_00.png");
	m_TopRender->GetTransform()->SetLocalScale(float4{ 18.0f , 16.0f });
	// y ���� ������ y�� �������� �ϴ°�.. 
	m_TopRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 230.0f });
}

void Laser::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case LaserState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case LaserState::COLLISION:
		CollisionUpdate(_DeltaTime);
		break;
	}
}

// state ����, ����� ������ start, ���� ������ end ����
void Laser::ChangeState(LaserState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case LaserState::IDLE:
		IdleStart();
		break;
	case LaserState::COLLISION:
		CollisionStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case LaserState::IDLE:
		IdleEnd();
		break;
	case LaserState::COLLISION:
		CollisionEnd();
		break;
	}
}

void Laser::IdleStart()
{
	m_LaserRender->ChangeAnimation("laser_idle");
}

void Laser::IdleUpdate(float _DeltaTime)
{
	// ���� ���� �÷��̾��� �����浹ü�� �浹���̶�� �ݸ������·� ����
	std::shared_ptr<GameEngineCollision> PlayerSubCol = m_Collision->Collision(ColOrder::PLAYER, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (nullptr != PlayerSubCol)
	{
		ChangeState(LaserState::COLLISION);
		return;
	}
}

void Laser::IdleEnd()
{
}

void Laser::CollisionStart()
{
	m_LaserRender->ChangeAnimation("laser_col");
	m_LaserRender->GetTransform()->SetLocalScale(float4{ m_LaserScale.x * 3.0f  , m_LaserScale.y });
}

void Laser::CollisionUpdate(float _DeltaTime)
{
	// �ִϸ��̼��� ���� �Ǿ��� �� �浹���� �ƴ϶�� idle�� ����
	if (true == m_LaserRender->IsAnimationEnd())
	{
		// ���� ���� �÷��̾��� �����浹ü�� �浹���̶�� �ݸ������·� ����
		std::shared_ptr<GameEngineCollision> PlayerSubCol = m_Collision->Collision(ColOrder::PLAYER, ColType::AABBBOX2D, ColType::AABBBOX2D);
		if (nullptr != PlayerSubCol)
		{
			return;
		}
		// �浹���� �ƴ϶�� idle�� ��ȯ 
		else if (nullptr == PlayerSubCol)
		{
			ChangeState(LaserState::IDLE);
			return;
		}
	}


}

void Laser::CollisionEnd()
{
	m_LaserRender->GetTransform()->SetLocalScale(m_LaserScale);
}
