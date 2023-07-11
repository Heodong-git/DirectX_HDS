#include "PrecompileHeader.h"
#include "ReflectEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

ReflectEffect::ReflectEffect()
{
}

ReflectEffect::~ReflectEffect()
{
}

void ReflectEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("bullet_reflect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("bullet_reflect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "bullet_reflect", .SpriteName = "bullet_reflect", .Start = 0, .End = 4 ,
							  .FrameInter = 0.02f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);

	m_Render->ChangeAnimation("bullet_reflect");
}

void ReflectEffect::Update(float _DeltaTime)
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

void ReflectEffect::Render(float _DeltaTime)
{
}
