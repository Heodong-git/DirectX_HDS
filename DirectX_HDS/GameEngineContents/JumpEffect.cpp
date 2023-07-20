#include "PrecompileHeader.h"
#include "JumpEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

JumpEffect::JumpEffect()
{
}

JumpEffect::~JumpEffect()
{
}

void JumpEffect::Start()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("jumpcloud"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("jumpcloud").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float PlayerRenderPivot = Player::MainPlayer->GetRenderPivot();
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER_EFFECT);
	m_Render->GetTransform()->SetLocalPosition( { PlayerPos.x , PlayerPos.y + 50.0f , -2.0f});
	m_Render->ColorOptionValue.MulColor.a = 0.7f;
	m_Render->SetScaleRatio(2.0f);
	m_Render->CreateAnimation({ .AnimationName = "jump_cloud", .SpriteName = "jumpcloud", .Start = 0, .End = 3 ,
								  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("jump_cloud");
	Set_Recording_StartFrame();
}

void JumpEffect::Update(float _DeltaTime)
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

void JumpEffect::Render(float _DeltaTime)
{
}
