#include "PrecompileHeader.h"
#include "DashEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

DashEffect::DashEffect()
{
}

DashEffect::~DashEffect()
{
}

void DashEffect::Start()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("dashcloud"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("dashcloud").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float PlayerRenderPivot = Player::MainPlayer->GetRenderPivot();
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER_EFFECT);
	GetTransform()->SetLocalPosition({ PlayerPos.x , PlayerPos.y + 20.0f });
	m_Render->ColorOptionValue.MulColor.a = 0.7f;
	m_Render->SetScaleRatio(3.0f);
	m_Render->CreateAnimation({ .AnimationName = "dash_cloud", .SpriteName = "dashcloud", .Start = 0, .End = 9 ,
								  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

	m_Render->ChangeAnimation("dash_cloud");
}

void DashEffect::Update(float _DeltaTime)
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

	bool DirValue = Player::MainPlayer->GetDir();

	if (true == DirValue)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}

	else if (false == DirValue)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
}

void DashEffect::Render(float _DeltaTime)
{
}
