#include "PrecompileHeader.h"
#include "LandEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Player.h"

LandEffect::LandEffect()
{
}

LandEffect::~LandEffect()
{
}

void LandEffect::Start()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("landcloud"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("landcloud").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float PlayerRenderPivot = Player::MainPlayer->GetRenderPivot();
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER_EFFECT);
	m_Render->GetTransform()->SetLocalPosition({ PlayerPos.x , PlayerPos.y + 15.0f});
	m_Render->ColorOptionValue.MulColor.a = 0.7f;
	m_Render->SetScaleRatio(2.0f);
	m_Render->CreateAnimation({ .AnimationName = "land_cloud", .SpriteName = "landcloud", .Start = 0, .End = 3 ,
								  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("land_cloud");
}

void LandEffect::Update(float _DeltaTime)
{
	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd())
		{
			this->Death();
			return;
		}
	}
}

void LandEffect::Render(float _DeltaTime)
{
}
