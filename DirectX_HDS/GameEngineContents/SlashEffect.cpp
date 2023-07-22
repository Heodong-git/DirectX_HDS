#include "PrecompileHeader.h"
#include "SlashEffect.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"
#include "PlaySupporter.h"

#include "SlashLaser_Effect.h"

#include "BloodEffect.h"

SlashEffect::SlashEffect()
{
}

SlashEffect::~SlashEffect()
{
}

void SlashEffect::Start()
{
	if (false == GameEngineInput::IsKey("SlashEffect_DebugSwitch"))
	{
		GameEngineInput::CreateKey("SlashEffect_DebugSwitch", 'Q');
	}

	// ��������Ʈ������ nullptr �϶��� 
	if (nullptr == GameEngineSprite::Find("slash"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slash").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	// baseactor override �ϴ°� ������ 
	// ����� ������Ʈ����
	ComponentSetting();

	// ���� ��ȭ�� �����ؾ��� �����Ӱ� ���� 
	Set_Recording_StartFrame();
}

void SlashEffect::Update(float _DeltaTime)
{
	if (true == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(0.5f);
	}

	m_RecordingFrame = !m_RecordingFrame;

	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
			return;
		}
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
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}
		
		Play_RecordingForward(m_Render.get());
		return;
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


	DebugUpdate();
	MoveUpdate(_DeltaTime);
	CollisionUpdate(_DeltaTime);

	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}
}

void SlashEffect::Render(float _DeltaTime)
{
	
}

void SlashEffect::SlashSoundPlay()
{
	m_SoundPlayer = GameEngineSound::Play("death_sword.wav");
	m_SoundPlayer.SetVolume(0.7f);
}

void SlashEffect::DebugUpdate()
{
}

void SlashEffect::ComponentSetting()
{
	// ��
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER_EFFECT);
	m_Render->SetScaleRatio(2.0f);
	m_Render->CreateAnimation({ .AnimationName = "slash_effect", .SpriteName = "slash", .Start = 0, .End = 4 ,
								.FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("slash_effect");

	// ����Ʈ ��ġ, �������
	float RenderPivot = Player::MainPlayer->GetRenderPivot();
	const float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	const float4 AttackPos = Player::MainPlayer->GetAttackPos();

	float4 Dir = AttackPos - PlayerPos;
	m_Angle = atan2f(Dir.y, Dir.x) * GameEngineMath::RadToDeg;
	m_Render->GetTransform()->SetLocalRotation({ 0 , 0 , m_Angle });

	// �浹ü 
	// �������� �ӽ�ũ�� 
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::PLAYER_ATTACK);
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalRotation({ 0 , 0 , m_Angle });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOn();
	
	// �̺�Ʈ�߰�
	
	//m_Render->SetAnimationStartEvent("slash_effect", static_cast<size_t>(4), std::bind(&SlashEffect::CollisionOff, this));
}

// ���� ����, ���� �����Ϸ� 
void SlashEffect::CollisionUpdate(float _DeltaTime)
{
	// �� ���⼭ ���ϱ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::MONSTER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		// �긦 ���⼭ ���� 
		//Col->GetActor()->DynamicThis<BaseActor>()->SetDeath();
		// �̶� ���Ͷ� �浹�ߴٸ� ī�޶� ����Ʈ ȣ�� 
		
		float RandomValue = GameEngineRandom::MainRandom.RandomFloat(35.0f, 60.0f);
		std::weak_ptr<BloodEffect> Blood_Effect = GetLevel()->CreateActor<BloodEffect>();
		Blood_Effect.lock()->SetType(BloodType::NORMAL);
		Blood_Effect.lock()->GetTransform()->SetWorldPosition(Col->GetTransform()->GetWorldPosition() + float4 { 0.0f, RandomValue });

		SlashSoundPlay();
		PlaySupporter::MainSupporter->CameraShakeOn();
		PlaySupporter::MainSupporter->CameraZoomEffect(0.97f);

		// �׸��� �������Ӹ� ��ŸŸ���� ������ �ϰ������ 
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::MONSTER, 0.1f);
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::PLAYER, 0.1f);

		// �浹�� ������ ��ǥ 
		float4 ColPos = Col->GetTransform()->GetParent()->GetLocalPosition();
		const float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

		float4 Dir = ColPos - PlayerPos;

		float DirY = Dir.y;
		float EffectX = 0.0f; 
		float EffectY = 0.0f;
		if (ColPos.x >= PlayerPos.x)
		{
			EffectX = -800.0f;
		}

		else
		{
			EffectX = 800.0f;
		}

		if (ColPos.y >= PlayerPos.y)
		{
			EffectY = -330.0f;
		}

		else
		{
			EffectY = 330.0f;
		}
		
		// �׷��� ������ ����Ʈ�� �����ϴµ�. 
		std::shared_ptr<SlashLaser_Effect> Effect = GetLevel()->CreateActor<SlashLaser_Effect>(static_cast<int>(RenderOrder::EFFECT));
		
		// ��ġ�� ���� �Ű����ҵ�. 
		Effect->GetTransform()->SetLocalPosition({ EffectX , EffectY });
		Effect->SetMovePos(ColPos);
	}

	std::shared_ptr<GameEngineCollision> BossCol = m_Collision->Collision(ColOrder::BOSS, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != BossCol)
	{
		SlashSoundPlay();
		PlaySupporter::MainSupporter->CameraShakeOn();
		PlaySupporter::MainSupporter->CameraZoomEffect(0.97f);
	}


	std::shared_ptr<GameEngineCollision> DoorCol = m_Collision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != DoorCol)
	{
		PlaySupporter::MainSupporter->CameraShakeOn();
		PlaySupporter::MainSupporter->CameraZoomEffect(0.97f);
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::PLAYER, 0.27f);
	}
}

void SlashEffect::MoveUpdate(float _DeltaTime)
{
	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd())
		{
			ChangeState(EffectState::DEATH);
			CollisionOff();
			m_Render->Off();
			m_IsRecording = false;
			
			// this->Death();
			PlaySupporter::MainSupporter->CameraZoomEffect(1.0f);
			GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::MONSTER, 1.0f);
			GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::PLAYER, 1.0f);
			return;
		}
	}

	// �浹ü�� ����Ʈ�� 3�������ӿ��� ����
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�.");
		return;
	}

	m_PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	m_Render->GetTransform()->SetLocalPosition({ m_PlayerPos.x , m_PlayerPos.y + m_RenderPivot , -1.0f });	
	if (false == Player::MainPlayer->GetDir())
	{
		m_Collision->GetTransform()->SetLocalPosition({ m_PlayerPos.x + -m_ColPivot , m_PlayerPos.y + m_RenderPivot });
		return;
	}

	m_Collision->GetTransform()->SetLocalPosition({ m_PlayerPos.x + m_ColPivot , m_PlayerPos.y + m_RenderPivot - 10.0f });
}

void SlashEffect::CollisionOff()
{
	if (nullptr != m_Collision)
	{
		m_Collision->Off();
	}
}



