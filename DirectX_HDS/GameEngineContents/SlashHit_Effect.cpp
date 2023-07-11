#include "PrecompileHeader.h"
#include "SlashHit_Effect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SlashHit_Effect::SlashHit_Effect()
{
}

SlashHit_Effect::~SlashHit_Effect()
{
}

void SlashHit_Effect::SetObject(std::shared_ptr<GameEngineObject> _Obj)
{
	if (nullptr == _Obj)
	{
		MsgAssert("������Ʈ�� nullptr �Դϴ�.");
	}

	m_FollowObj = _Obj;
}

void SlashHit_Effect::Start()
{
	if (nullptr == GameEngineSprite::Find("slash_hit"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slash_hit").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	ComponentSetting();
}

void SlashHit_Effect::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;

	// ������ ��ȭ�������̶��, 
	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		// �� ���¸� ��ȭ���·� �����ϰ�, 
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
			return;
		}
	}

	// ��ȭ ���¶�� 
	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}
		// ������ �Լ� ȣ�� 
		Reverse(m_MainRender.get());

		// ����� �Լ� ȣ�� �� , ���� ��������� 0 �̶�� ���� death 
		if (0 == Infos.size())
		{
			this->Death();
		}
		return;
	}

	if (nullptr != m_MainRender)
	{
		// �ִϸ��̼��� ����Ǿ���, ���� �������°� �ƴҶ��� 
		if (m_MainRender->IsAnimationEnd() && EffectState::DEATH != m_CurState)
		{
			// ������Ű�� �ʰ�, ���¸� ����
			ChangeState(EffectState::DEATH);
			m_MainRender->Off();
			m_IsRecording = false;
			return;
		}
	}

	// ������Ʈ �Ѿư��� 
	if (nullptr != m_FollowObj)
	{
		if (true == m_IsPivot)
		{
			GetTransform()->SetWorldPosition(m_FollowObj->GetTransform()->GetWorldPosition() + m_Pivot);
		}

		if (false == m_IsPivot)
		{
			GetTransform()->SetWorldPosition(m_FollowObj->GetTransform()->GetWorldPosition());
		}
		
		// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			if (true == m_RecordingFrame)
			{
				InfoSetting(m_MainRender.get());
			}
		}
	}

	
}

void SlashHit_Effect::Render(float _DeltaTime)
{
}

void SlashHit_Effect::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_MainRender->SetScaleRatio(2.0f);

	m_MainRender->CreateAnimation({ .AnimationName = "slash_hit", .SpriteName = "slash_hit", .Start = 0, .End = 4 ,
								.FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->ChangeAnimation("slash_hit");
}
