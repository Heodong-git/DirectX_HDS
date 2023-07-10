#include "PrecompileHeader.h"
#include "HitEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

HitEffect::HitEffect()
{
}

HitEffect::~HitEffect()
{
}

// 안씀
void HitEffect::SetObject(std::shared_ptr<GameEngineObject> _Obj)
{
	if (nullptr == _Obj)
	{
		MsgAssert("오브젝트가 nullptr 입니다.");
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

	// 레벨이 녹화진행중이라면, 
	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		// 내 상태를 녹화상태로 변경하고, 
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
		}
	}

	// 녹화 상태라면 
	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
		// 리버스 함수 호출 
		Reverse(m_MainRender.get());

		// 역재생 함수 호출 후 , 나의 인포사이즈가 0 이라면 나를 death 
		if (0 == Infos.size())
		{
			this->Death();
		}
		return;
	}

	if (nullptr != m_MainRender)
	{
		// 애니메이션이 종료되었고, 내가 데스상태가 아닐때만 
		if (m_MainRender->IsAnimationEnd() && EffectState::DEATH != m_CurState)
		{
			// 데스시키지 않고, 상태만 변경
			ChangeState(EffectState::DEATH);
			m_MainRender->Off();
			m_IsRecording = false;
			return;
		}
	}

	// 오브젝트 쫓아가기 
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

		// 나의 스테이트가, 녹화진행중이 아니라면, 녹화 정보를 저장한다. 
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
