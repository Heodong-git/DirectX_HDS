#include "PrecompileHeader.h"
#include "GunSpark_Effect2.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GunSpark_Effect2::GunSpark_Effect2()
{
}

GunSpark_Effect2::~GunSpark_Effect2()
{
}

void GunSpark_Effect2::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	if (nullptr == GameEngineSprite::Find("gunspark_effect2"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "gunspark_effect2", .SpriteName = "gunspark_effect2", .Start = 0, .End = 7 ,
								  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->ChangeAnimation("gunspark_effect2");
	m_Render->SetScaleRatio(2.0f);
}

void GunSpark_Effect2::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;

	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
			return;
		}
	}

	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_Render.get());

		// ����� �Լ� ȣ�� �� , ���� ��������� 0 �̶�� ���� death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}

	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}

	if (true == m_Render->IsAnimationEnd())
	{
		ChangeState(EffectState::DEATH);
		m_Render->Off();
		m_IsRecording = false;
	}
}

void GunSpark_Effect2::Render(float _DeltaTime)
{
}
