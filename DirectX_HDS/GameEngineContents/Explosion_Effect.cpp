#include "PrecompileHeader.h"
#include "Explosion_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Explosion_Effect::Explosion_Effect()
{
}

Explosion_Effect::~Explosion_Effect()
{
}

void Explosion_Effect::SetType(EffectType _Type)
{
	{
		switch (_Type)
		{
		case EffectType::NONE:
		{
			MsgAssert("Explosion 이펙트의 타입을 지정하지 않았습니다.");

		}
		break;
		case EffectType::FIRST:
			m_Render->ChangeAnimation("explosion_effect1");
			break;
		case EffectType::SECOND:
			m_Render->ChangeAnimation("explosion_effect2");
			break;
		}
	}
}

void Explosion_Effect::CollisionOff()
{
	m_Collision->Off();
}

void Explosion_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS_EXPLOSION);

	m_Collision->GetTransform()->SetLocalScale(float4{ 20.0f , 20.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);

	if (nullptr == GameEngineSprite::Find("explosion_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("explosion_effect").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("explosion_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "explosion_effect", .SpriteName = "explosion_effect", .Start = 0, .End = 9 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "explosion_effect2", .SpriteName = "explosion_effect2", .Start = 0, .End = 9 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	
	m_Render->SetAnimationStartEvent("explosion_effect", static_cast<size_t>(7), std::bind(&Explosion_Effect::CollisionOff, this));
	m_Render->SetAnimationStartEvent("explosion_effect2", static_cast<size_t>(7), std::bind(&Explosion_Effect::CollisionOff, this));

	m_Render->SetScaleRatio(2.0f);
	m_Render->ChangeAnimation("explosion_effect");

}

void Explosion_Effect::Update(float _DeltaTime)
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

void Explosion_Effect::Render(float _DeltaTime)
{
}
