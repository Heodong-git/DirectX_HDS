#include "PrecompileHeader.h"
#include "DoorEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

DoorEffect::DoorEffect()
{
}

DoorEffect::~DoorEffect()
{
}

void DoorEffect::Start()
{
	ComponentSetting();

	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("door_glow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("door_glow").GetFullPath());	
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });

		m_MainRender->CreateAnimation({ .AnimationName = "door_glow", .SpriteName = "door_glow", .Start = 0, .End = 9 ,
							.FrameInter = 0.15f , .Loop = true , .ScaleToTexture = true });
	}

	m_MainRender->ChangeAnimation("door_glow");
	
}

void DoorEffect::Update(float _DeltaTime)
{
}

void DoorEffect::Render(float _DeltaTime)
{
}

void DoorEffect::DebugUpdate()
{
}

void DoorEffect::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_MainRender->SetScaleRatio(2.0f);
}
