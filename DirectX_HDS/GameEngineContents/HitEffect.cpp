#include "PrecompileHeader.h"
#include "HitEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

HitEffect::HitEffect()
{
}

HitEffect::~HitEffect()
{
}

// �Ⱦ�
void HitEffect::SetObject(std::shared_ptr<GameEngineObject> _Obj)
{
	if (nullptr == _Obj)
	{
		MsgAssert("������Ʈ�� nullptr �Դϴ�.");
	}
	
	m_FollowObj = _Obj;
}

void HitEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("hit_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("hit_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_MainRender->ColorOptionValue.MulColor.r = 0.7f;
	m_MainRender->SetScaleRatio(2.0f);
	m_MainRender->CreateAnimation({ .AnimationName = "hit_effect", .SpriteName = "hit_effect", .Start = 0, .End = 5 ,
								  .FrameInter = 0.045f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->GetTransform()->SetLocalPosition(float4{ 47.0f, 30.0f });
	m_MainRender->ChangeAnimation("hit_effect");
}

void HitEffect::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;

	// ������ ��ȭ�������̶��, 
	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		// �� ���¸� ��ȭ���·� �����ϰ�, 
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
		}
	}

	// ��ȭ ���¶�� 
	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
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

void HitEffect::Render(float _DeltaTime)
{
}
