#include "PrecompileHeader.h"
#include "BloodEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

BloodEffect::BloodEffect()
{
}

BloodEffect::~BloodEffect()
{
}

void BloodEffect::SetType(BloodType _Type)
{
	{
		switch (_Type)
		{
		case BloodType::NONE:
		{
			MsgAssert("GunSmoke ����Ʈ�� Ÿ���� �������� �ʾҽ��ϴ�.");

		}
		break;
		case BloodType::FIRST:
			m_Render->ChangeAnimation("blood_effect1");
			break;
		case BloodType::SECOND:
			m_Render->ChangeAnimation("blood_effect2");
			break;
		case BloodType::THIRD:
			m_Render->ChangeAnimation("blood_effect3");
			break;
		}
	}
}

void BloodEffect::Start()
{
	// �����������, �ִϸ��̼� �������� �־�ΰ�, ����Ʈ�����Ҷ� 
	// � �ִϸ��̼��� �����ٰ��� set 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	if (nullptr == GameEngineSprite::Find("blood_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");
		Dir.Move("blood_effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect1").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect2").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect3").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "blood_effect1", .SpriteName = "blood_effect1", .Start = 0, .End = 29 ,
								  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_Render->CreateAnimation({ .AnimationName = "blood_effect2", .SpriteName = "blood_effect2", .Start = 0, .End = 8 ,
							  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->CreateAnimation({ .AnimationName = "blood_effect3", .SpriteName = "blood_effect3", .Start = 0, .End = 6 ,
							  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	
	m_Render->SetScaleRatio(2.0f);
}

void BloodEffect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		int a = 0;
	}
}

void BloodEffect::Render(float _DeltaTime)
{
}
