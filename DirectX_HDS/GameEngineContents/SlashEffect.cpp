#include "PrecompileHeader.h"
#include "SlashEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

SlashEffect::SlashEffect()
{
}

SlashEffect::~SlashEffect()
{
}

void SlashEffect::Start()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("slash"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slash").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetScaleRatio(2.0f);
	m_Render->CreateAnimation({ .AnimationName = "slash_effect", .SpriteName = "slash", .Start = 0, .End = 4 ,
								  .FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("slash_effect");

}

void SlashEffect::Update(float _DeltaTime)
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
		m_Render->GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == DirValue)
	{
		m_Render->GetTransform()->SetLocalNegativeScaleX();
	}


	// 여기서 위치를 
	float RenderPivot = Player::MainPlayer->GetRenderPivot();
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float4 AttackPos = Player::MainPlayer->GetAttackPos();
	m_Render->GetTransform()->SetLocalPosition({ PlayerPos.x , PlayerPos.y + RenderPivot });
	
	float Angle = AttackPos.y - PlayerPos.y;
	// 회전을 건드려야 되는데 값을.. 어떻게.. y값을 빼고, 그 값을 z축에 ㅠ 
	m_Render->GetTransform()->SetLocalRotation({ 0 , 0 });
}

void SlashEffect::Render(float _DeltaTime)
{
	
}
