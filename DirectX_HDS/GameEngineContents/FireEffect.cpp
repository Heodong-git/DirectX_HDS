#include "PrecompileHeader.h"
#include "FireEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

FireEffect::FireEffect()
{
}

FireEffect::~FireEffect()
{
}

void FireEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("gangster_fire_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("gangster");
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_fire_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "gangster_fire_effect", .SpriteName = "gangster_fire_effect", .Start = 0, .End = 7 ,
							  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);

	m_Render->ChangeAnimation("gangster_fire_effect");
}

void FireEffect::Update(float _DeltaTime)
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

	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd() && EffectState::DEATH != m_CurState)
		{
			ChangeState(EffectState::DEATH);
			m_Render->Off();
			m_IsRecording = false;
			//this->Death();
			return;
		}
	}

	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}
}

void FireEffect::Render(float _DeltaTime)
{
}
