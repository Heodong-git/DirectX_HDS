#include "PrecompileHeader.h"
#include "FanBlade.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

FanBlade::FanBlade()
{
}

FanBlade::~FanBlade()
{
}

void FanBlade::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
}

void FanBlade::Update(float _DeltaTime)
{
	m_FanRender->GetTransform()->SetLocalPosition(m_FanRenderInitPos);
	CorrectionRenderPos();
	DebugUpdate();
	PlayerSkillCheck();
}

void FanBlade::Render(float _DeltaTime)
{
}

void FanBlade::Reset()
{
}

void FanBlade::CorrectionRenderPos()
{
	// 프레임별로 위치보정
	if (1 == m_FanRender->GetCurrentFrame())
	{
		m_FanRender->GetTransform()->AddLocalPosition(float4{ 1.0f, 3.0f });
	}

	else if ( 2 == m_FanRender->GetCurrentFrame())
	{
		m_FanRender->GetTransform()->AddLocalPosition(float4{ 7.0f, 8.0f });
	}

	else if (3 == m_FanRender->GetCurrentFrame())
	{
		m_FanRender->GetTransform()->AddLocalPosition(float4{ 9.0f, 7.0f });
	}

	else if (4 == m_FanRender->GetCurrentFrame())
	{
		m_FanRender->GetTransform()->AddLocalPosition(float4{ 9.0f, -11.0f });
	}

	else if (5 == m_FanRender->GetCurrentFrame())
	{
		m_FanRender->GetTransform()->AddLocalPosition(float4{ 8.0f, -12.0f });
	}
}

void FanBlade::PlayerSkillCheck()
{
	// 플레이어 스킬 사용여부를 체크해서
	// 현재 플레이어가 스킬 사용중이라면
	if (true == Player::MainPlayer->IsSkill())
	{	
		// 특정 프레임에서의 충돌체를 off 할건데 
		if (4 != m_FanRender->GetCurrentFrame())
		{
			// 현재 프레임값이 1이라면 충돌체 off
			m_Collision->Off();
		}
		else
		{
			// 그게 아니라면 온 
			m_Collision->On();
		}
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_Collision->On();
	}
}

void FanBlade::DebugUpdate()
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
		
		if (nullptr != m_DebugRender)
		{
			if (true == m_DebugRender->IsUpdate())
			{
				m_DebugRender->Off();
			}

			else
			{
				m_DebugRender->On();
			}
		}
	}
}

void FanBlade::ComponentSetting()
{
	m_CoverRender_Left = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FANBLADE);
	m_CoverRender_Right = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FANBLADE);
	m_FanRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FANBLADE);
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::FANBLADE);
	m_Collision->SetColType(ColType::OBBBOX3D);

	m_Collision->GetTransform()->SetLocalScale(float4{ 50.0f, 120.0f });
	m_Collision->GetTransform()->AddLocalPosition(float4{ -2.0f, 77.0f });
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4, 4 });
	m_DebugRender->Off();
}

void FanBlade::LoadAndCreateAnimation()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("fanblade_idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("fanblade");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("fanblade_idle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("fanblade_cover").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("fanblade_origin").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });

		m_FanRender->CreateAnimation({ .AnimationName = "fanblade_idle_first", .SpriteName = "fanblade_idle", .Start = 0, .End = 1 ,
							.FrameInter = 0.01f , .Loop = true , .ScaleToTexture = false });
		m_FanRender->CreateAnimation({ .AnimationName = "fanblade_origin", .SpriteName = "fanblade_origin", .Start = 0, .End = 5,
						.FrameInter = 0.02f , .Loop = true , .ScaleToTexture = false });
	}

	// 위치 안맞는 프레임이 동작할때 위치보정함수를 이벤트로 추가? 아니면 애니메이션을 다따로만들어 
	m_FanRender->ChangeAnimation("fanblade_origin");
	m_FanRenderInitPos = GetTransform()->GetLocalPosition() + float4{ -8.0f, 80.0f };
	m_FanRender->GetTransform()->SetLocalPosition(m_FanRenderInitPos);
	m_FanRender->GetTransform()->SetLocalScale(float4{ 50.0f , 120.0f });
	//m_FanRender->SetScaleRatio(1.5f);
	m_CoverRender_Left->SetTexture("spr_fan_bg_0.png");
	m_CoverRender_Left->GetTransform()->SetLocalScale(float4{ 60.0f, 170.0f });
	m_CoverRender_Left->GetTransform()->AddLocalPosition(float4{ -25.0f , 87.0f });
	m_CoverRender_Right->SetTexture("spr_fan_fg_0.png");
	m_CoverRender_Right->GetTransform()->SetLocalScale(float4{ 60.0f, 170.0f });
	m_CoverRender_Right->GetTransform()->AddLocalPosition(float4{ 24.0f , 87.0f });
}
