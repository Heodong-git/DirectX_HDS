#include "PrecompileHeader.h"
#include "FanBlade.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	DebugUpdate();
}

void FanBlade::Render(float _DeltaTime)
{
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
			if (true == m_DebugRender->IsDebug())
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
	m_CoverRender_Left = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_CoverRender_Right = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_FanRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_Collision = CreateComponent<GameEngineCollision>(RenderOrder::MONSTER);;

	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4, 4 });
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

		m_FanRender->CreateAnimation({ .AnimationName = "fanblade_idle", .SpriteName = "fanblade_idle", .Start = 0, .End = 31 ,
							.FrameInter = 0.01f , .Loop = true , .ScaleToTexture = true });
		m_FanRender->CreateAnimation({ .AnimationName = "fanblade_origin", .SpriteName = "fanblade_origin", .Start = 0, .End = 2 ,
						.FrameInter = 0.01f , .Loop = true , .ScaleToTexture = true });
	}

	// 위치 안맞는 프레임이 동작할때 위치보정함수를 이벤트로 추가? 아니면 애니메이션을 다따로만들어 
	m_FanRender->ChangeAnimation("fanblade_idle");
	m_FanRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 87.0f });
	m_FanRender->SetScaleRatio(1.5f);
	m_CoverRender_Left->SetTexture("spr_fan_bg_0.png");
	m_CoverRender_Left->GetTransform()->SetLocalScale(float4{ 60.0f, 170.0f });
	m_CoverRender_Left->GetTransform()->AddLocalPosition(float4{ -25.0f , 87.0f });
	m_CoverRender_Right->SetTexture("spr_fan_fg_0.png");
	m_CoverRender_Right->GetTransform()->SetLocalScale(float4{ 60.0f, 170.0f });
	m_CoverRender_Right->GetTransform()->AddLocalPosition(float4{ 24.0f , 87.0f });
}
