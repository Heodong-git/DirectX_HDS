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
	// 애니메이션렌더, 3분할 홀더, 바디, 포탑 
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	// m_MainRender->Off();

	m_TopRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_HolderRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_BodyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::TURRET_BODY);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4.0f , 4.0f });
	m_DebugRender->Off();

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale(float4{ 50.0f , 70.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->Off();

	LoadAndCreateAnimation();

	m_TopRender->SetTexture("spr_floor_turret_top_0.png");
	m_TopRender->GetTransform()->SetLocalPosition(float4{ 3.0f, 17.0f });
	m_TopRender->GetTransform()->SetLocalScale(float4{ 94.0f, 60.0f });
	m_TopRender->Off();

	m_BodyRender->SetTexture("spr_floor_turret_1.png");
	m_BodyRender->GetTransform()->SetLocalPosition(float4{ 5.0f, 18.0f });
	m_BodyRender->GetTransform()->SetLocalScale(float4{ 94.0f, 60.0f });
	m_BodyRender->Off();

	m_HolderRender->SetTexture("spr_bunker_turret_holder_0.png");
	m_HolderRender->GetTransform()->SetLocalPosition(float4{ -5.0f ,-20.0f });
	m_HolderRender->GetTransform()->SetLocalScale(float4{ 98.0f, 52.0f });
	m_HolderRender->Off();
}

void Turret::Update(float _DeltaTime)
{
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
		// 내가 지금 노말 상태일때.
		if (TurretState::NORMAL == m_CurState)
		{
			std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
			if (nullptr != Col)
			{
				// 플레이어와 충돌했다면, 
				m_SoundPlayer = GameEngineSound::Play("sound_turretdie.wav");
				PlaySupporter::MainSupporter->CameraShakeOn();
				m_TopRender->ChangeAnimation("turret_die");
				m_TopRender->GetTransform()->AddLocalPosition(float4{ -16.0f ,5.0f });
				m_TopRender->SetScaleRatio(2.0f);
				m_Collision->Off();
				m_CurState = TurretState::DEATH;
				return;
			}

			if (nullptr != Player::MainPlayer)
			{
				m_FireTime -= _DeltaTime;
				// 특정물체를 바라보게 하기 위한

				// 타겟의 위치를 받아온다. 
				float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

				// 내 위치를 받아온다. 
				float4 TurretPos = GetTransform()->GetLocalPosition();
				
				// 내가 보고 있는 방향을 구한다. (각도)
				float4 TurretPos1 = m_TopRender->GetTransform()->GetLocalRotation();

				// z 값을 인자로 넣어주면, 인자로 넣어준 벡터가 보고 있는 방향값을 반환해준다, float4 로 
				float4 Dir = float4::AngleToDirection2DToDeg(TurretPos1.z);

				// 방향벡터 구해주고 노말라이즈 
				float4 TargetPos = PlayerPos - TurretPos;
				TargetPos.Normalize();

				float Angle = float4::GetAngleVectorToVectorDeg360(Dir, TargetPos);

				float4 Attdir = float4{ 0.0f, 0.0f, Angle };
				m_TopRender->GetTransform()->AddLocalRotation(Attdir * _DeltaTime);
	
				if (0.0f >= m_FireTime)
				{
					m_FireTime = 1.5f;
					// 일단해 
					Fire(TargetPos, m_TopRender->GetTransform()->GetLocalRotation().z);
				}
				
			}

			// 0.03  
			// 
			return;
		}


		// 애니메이션이 종료되었을때, 트랜스폼상태라면 
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
