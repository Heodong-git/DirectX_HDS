#include "PrecompileHeader.h"
#include "PompEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Monster_Pomp.h"

PompEffect::PompEffect()
{
}

PompEffect::~PompEffect()
{
}

void PompEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("pomp_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("pomp");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "pomp_effect", .SpriteName = "pomp_effect", .Start = 0, .End = 5,
								  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(1.5f);
	m_Render->ChangeAnimation("pomp_effect");

	Set_Recording_StartFrame();
}

void PompEffect::Update(float _DeltaTime)
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
		// 만약 좌클릭 입력시 바로 death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_Render.get());

		// 역재생 함수 호출 후 , 나의 인포사이즈가 0 이라면 나를 death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}

	if (BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS_FORWARD != m_CurState)
		{
			SetMaxIndex();
			ChangeState(EffectState::RECORDING_PROGRESS_FORWARD);
			return;
		}
	}

	if (EffectState::RECORDING_PROGRESS_FORWARD == m_CurState)
	{
		// 만약 좌클릭 입력시 바로 death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Play_RecordingForward(m_Render.get());
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
