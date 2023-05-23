#include "PrecompileHeader.h"
#include "JumpEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

JumpEffect::JumpEffect()
{
}

JumpEffect::~JumpEffect()
{
}

void JumpEffect::Start()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("jumpcloud"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("jumpcloud").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float PlayerRenderPivot = Player::MainPlayer->GetRenderPivot();
	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->GetTransform()->SetLocalPosition( { PlayerPos.x , PlayerPos.y + 50.0f });
	m_Render->ColorOptionValue.MulColor.a = 0.7f;
	m_Render->SetScaleRatio(2.0f);
	m_Render->CreateAnimation({ .AnimationName = "jump_cloud", .SpriteName = "jumpcloud", .Start = 0, .End = 3 ,
								  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("jump_cloud");
}

void JumpEffect::Update(float _DeltaTime)
{
	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd())
		{
			this->Death();
			return;
		}
	}

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("플레이어가 nullptr 입니다.");
		return;
	}
}

void JumpEffect::Render(float _DeltaTime)
{
}
