#include "PrecompileHeader.h"
#include "Turret.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

#include "Bullet.h"
#include "GunSpark_Effect.h"
#include "PlaySupporter.h"

Turret::Turret()
{
}

Turret::~Turret()
{
}

void Turret::SetType(TurretType _Type)
{
	m_Type = _Type;

	switch (m_Type)
	{
	case TurretType::NORMAL:
		break;
	case TurretType::WALL:
		m_MainRender->ChangeAnimation("turret_fromwall");
		break;
	default:
		break;
	}
}

void Turret::Start()
{
	// �ִϸ��̼Ƿ���, 3���� Ȧ��, �ٵ�, ��ž 
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	// m_MainRender->Off();

	m_TopRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_HolderRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_BodyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::TURRET_BODY);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4.0f , 4.0f , 1.0f});
	m_DebugRender->Off();

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::TURRET);
	m_Collision->GetTransform()->SetLocalScale(float4{ 50.0f , 70.0f , 1.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->Off();

	LoadAndCreateAnimation();

	m_TopRender->SetTexture("spr_floor_turret_top_0.png");
	m_TopRender->GetTransform()->SetLocalPosition(float4{ 3.0f, 17.0f });
	m_TopRender->GetTransform()->SetLocalScale(float4{ 94.0f, 60.0f , 1.0f});
	m_TopRender->Off();

	m_BodyRender->SetTexture("spr_floor_turret_1.png");
	m_BodyRender->GetTransform()->SetLocalPosition(float4{ 5.0f, 18.0f });
	m_BodyRender->GetTransform()->SetLocalScale(float4{ 94.0f, 60.0f , 1.0f });
	m_BodyRender->Off();

	m_HolderRender->SetTexture("spr_bunker_turret_holder_0.png");
	m_HolderRender->GetTransform()->SetLocalPosition(float4{ -5.0f ,-20.0f });
	m_HolderRender->GetTransform()->SetLocalScale(float4{ 98.0f, 52.0f , 1.0f });
	m_HolderRender->Off();
}

void Turret::Update(float _DeltaTime)
{
	if (BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	m_RecordingFrame = !m_RecordingFrame;

	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		if (TurretState::RECORDING_PROGRESS != m_CurState)
		{
			m_CurState = TurretState::RECORDING_PROGRESS;
			return;
		}
	}

	if (TurretState::RECORDING_PROGRESS == m_CurState)
	{
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_TopRender.get());

		// ����� �Լ� ȣ�� �� , ���� ��������� 0 �̶�� ���� death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}

	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	if (TurretState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_TopRender.get());
		}
	}

	if (true == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(0.5f);
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(1.0f);
	}

	DebugUpdate();
	if (TurretState::DEATH == m_CurState)
	{
		return;
	}


	if (TurretType::WALL == m_Type)
	{
		// ���� ���� �븻 �����϶�.
		if (TurretState::NORMAL == m_CurState)
		{
			std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
			if (nullptr != Col)
			{
				// �÷��̾�� �浹�ߴٸ�, 
				m_SoundPlayer = GameEngineSound::Play("sound_turretdie.wav");
				PlaySupporter::MainSupporter->CameraShakeOn();
				m_TopRender->ChangeAnimation("turret_die");
				m_TopRender->GetTransform()->AddLocalPosition(float4{ -16.0f ,5.0f });
				m_TopRender->SetScaleRatio(2.0f);
				m_Collision->Off();
				m_CurState = TurretState::DEATH;
				return;
			}

			std::shared_ptr<GameEngineCollision> Col2 = m_Collision->Collision(ColOrder::PLAYER_BULLET, ColType::OBBBOX3D, ColType::OBBBOX3D);
			if (nullptr != Col2)
			{
				// �÷��̾�� �浹�ߴٸ�, 
				m_SoundPlayer = GameEngineSound::Play("sound_turretdie.wav");
				PlaySupporter::MainSupporter->CameraShakeOn();
				m_TopRender->ChangeAnimation("turret_die");
				m_TopRender->GetTransform()->AddLocalPosition(float4{ -16.0f ,5.0f });
				m_TopRender->SetScaleRatio(2.0f);
				m_Collision->Off();
				m_CurState = TurretState::DEATH;
				std::shared_ptr<Bullet> bullet = Col2->GetActor()->DynamicThis<Bullet>();
				if (nullptr != bullet)
				{
					bullet->BulletDeath();
				}
				return;
			}

			if (nullptr != Player::MainPlayer)
			{
				m_FireTime -= _DeltaTime;
				// Ư����ü�� �ٶ󺸰� �ϱ� ����

				// Ÿ���� ��ġ�� �޾ƿ´�. 
				float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

				if (PlayerPos.x <= m_MaxXPos)
				{
					return;
				}

				// �� ��ġ�� �޾ƿ´�. 
				float4 TurretPos = GetTransform()->GetLocalPosition();
				
				// ���� ���� �ִ� ������ ���Ѵ�. (����)
				float4 TurretPos1 = m_TopRender->GetTransform()->GetLocalRotation();

				// z ���� ���ڷ� �־��ָ�, ���ڷ� �־��� ���Ͱ� ���� �ִ� ���Ⱚ�� ��ȯ���ش�, float4 �� 
				float4 Dir = float4::AngleToDirection2DToDeg(TurretPos1.z);

				// ���⺤�� �����ְ� �븻������ 
				float4 TargetPos = PlayerPos - TurretPos;
				TargetPos.Normalize();

				/*
				�߻��ϴ� ������ : 
				1. Angle ���� nan �� ������ ��찡 �ִ�.
				2. m_TopRender �� Ʈ������ �����Ͱ� ��â�� ���� ������.
				3. Angle ���� nan �� ���� �� Ȯ�� �� ���Ŀ��� ������ �ʴ´�. ( Ȯ�� �� F5 �� ��Ÿ���� �� ������ ���� ������, ��������� ) 

				nan : ������ �������� ���Ϸ��� �ϰų�, 0���� �������� ���� �� �߻�
				�� �ּ� ���ʿ��� ��� ���� �����̾, �Ʒ� �Լ�(GetAngleVectorToVectorDeg360)���� ��ȯ�ϴ� ���� nan �� ��찡 ������
				�� ��, ������ ���� �������� ���� ���ڷ� ���µ� (Dir, TargetPos) <--- �� ��ġ���� ��� �������� ���ӿ��� nan �� ��ȯ �ȴ�. 
				
				----------------------------- ���κ��� Ȯ���ϰ� Ȯ�ε� �κ�, �Ʒ��κ��� �ָ��� �κ�  ------------------
				1. �������� �ְ� 
				2. ���������� ���� , �� ������������ �� �� 
				3. �Ʒ� �ڵ忡�� Angle ������ nan �� ��ȯ�Ǹ�, ù if���� ���� �ʰ� else �� ����, �ߴ����� �ɸ��� �Ǵµ� 
				   ���� �����ӿ��� �� m_TopRender (�����ͷ������� ������) �� Ʈ�����������Ͱ� ��â�� ���ִ°� <-- �� �ѹ� �׷��� 
				4. �쿬������ �𸣰����� �Ʒ� if�� �ڵ带 �ӽ÷� �ۼ��� ���ķδ� �� �ѹ� ����� m_TopRender �� Ʈ�����������Ͱ� ������ ( 15~20��Ȯ����) 

				*/

				float Angle = float4::GetAngleVectorToVectorDeg360(Dir, TargetPos);

				// ��� �ӽ÷� �������� �ɾ�� if�� 
				if (-100.0f <= Angle || 100.0f >= Angle)
				{
					float4 Attdir = float4{ 0.0f, 0.0f, Angle };
					m_TopRender->GetTransform()->AddLocalRotation(Attdir * _DeltaTime);

					if (0.0f >= m_FireTime)
					{
						m_FireTime = 1.5f;
						// �ϴ��� 
						Fire(TargetPos, m_TopRender->GetTransform()->GetLocalRotation().z);
					}
				}

				else
				{
					int a = 0;
				}
			}

			// 0.03  
			// 
			return;
		}


		// �ִϸ��̼��� ����Ǿ�����, Ʈ���������¶�� 
		if (true == m_MainRender->IsAnimationEnd() && TurretState::TRANSFORM == m_CurState)
		{
			m_CurState = TurretState::NORMAL;
			m_MainRender->Off();
			m_TopRender->On();
			m_BodyRender->On();
			m_HolderRender->On();
			m_Collision->On();
			return;
		}
	}
}

void Turret::Render(float _DeltaTime)
{
}

void Turret::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_DebugSwitch"))
	{
		DebugSwitch();

		if (true == IsDebug())
		{
			m_DebugRender->On();
		}

		else if (false == IsDebug())
		{
			m_DebugRender->Off();
		}
	}
}

void Turret::LoadAndCreateAnimation()
{
	if (nullptr == GameEngineSprite::Find("turret_die"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("turret");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("turret_basic").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("turret_die").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("turret_fromwall").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_MainRender->CreateAnimation({ .AnimationName = "turret_die", .SpriteName = "turret_die", .Start = 0, .End = 13 ,
								  .FrameInter = 0.12f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "turret_fromwall", .SpriteName = "turret_fromwall", .Start = 0, .End = 15 ,
							  .FrameInter = 0.09f , .Loop = false , .ScaleToTexture = true });

	m_TopRender->CreateAnimation({ .AnimationName = "turret_die", .SpriteName = "turret_die", .Start = 0, .End = 13 ,
						  .FrameInter = 0.09f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->SetScaleRatio(2.0f);
	m_MainRender->ChangeAnimation("turret_fromwall");
}


void Turret::Fire(float4 _Dir , const float _Angle)
{
	GameEngineSound::Play("gun_fire_00.wav");
	std::shared_ptr<Bullet> Obj = GetLevel()->CreateActor<Bullet>();
	Obj->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { 52.0f, 23.0f });
	Obj->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, _Angle });
	Obj->SetType(BulletType::ROT);
	Obj->SetAngle(_Angle);
	Obj->SetMoveDir(_Dir);

	std::shared_ptr<GunSpark_Effect> Effect = GetLevel()->CreateActor<GunSpark_Effect>();
	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { 82.0f, 23.0f });
	Effect->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, _Angle });
}
