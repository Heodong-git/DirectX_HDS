#include "PrecompileHeader.h"
#include "RollEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

RollEffect::RollEffect()
{
}

RollEffect::~RollEffect()
{
}

void RollEffect::Start()
{
}

void RollEffect::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;

	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
		}
	}

	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
		Reverse(m_Render.get());

		// 역재생 함수 호출 후 , 나의 인포사이즈가 0 이라면 나를 death 
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

	// 나의 스테이트가, 녹화진행중이 아니라면, 녹화 정보를 저장한다. 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}
}

void RollEffect::Render(float _DeltaTime)
{
}
