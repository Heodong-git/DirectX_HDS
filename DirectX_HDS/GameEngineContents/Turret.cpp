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
		// 만약 좌클릭 입력시 바로 death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_TopRender.get());

		// 역재생 함수 호출 후 , 나의 인포사이즈가 0 이라면 나를 death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}

	// 나의 스테이트가, 녹화진행중이 아니라면, 녹화 정보를 저장한다. 
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

			std::shared_ptr<GameEngineCollision> Col2 = m_Collision->Collision(ColOrder::PLAYER_BULLET, ColType::OBBBOX3D, ColType::OBBBOX3D);
			if (nullptr != Col2)
			{
				// 플레이어와 충돌했다면, 
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
				// 특정물체를 바라보게 하기 위한

				// 타겟의 위치를 받아온다. 
				float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

				if (PlayerPos.x <= m_MaxXPos)
				{
					return;
				}

				// 내 위치를 받아온다. 
				float4 TurretPos = GetTransform()->GetLocalPosition();
				
				// 내가 보고 있는 방향을 구한다. (각도)
				float4 TurretPos1 = m_TopRender->GetTransform()->GetLocalRotation();

				// z 값을 인자로 넣어주면, 인자로 넣어준 벡터가 보고 있는 방향값을 반환해준다, float4 로 
				float4 Dir = float4::AngleToDirection2DToDeg(TurretPos1.z);

				// 방향벡터 구해주고 노말라이즈 
				float4 TargetPos = PlayerPos - TurretPos;
				TargetPos.Normalize();

				/*
				발생하는 문제점 : 
				1. Angle 값이 nan 이 들어오는 경우가 있다.
				2. m_TopRender 의 트랜스폼 데이터가 곱창이 나서 터진다.
				3. Angle 값이 nan 이 들어온 걸 확인 한 이후에도 터지지 않는다. ( 확인 후 F5 를 연타했을 때 터지는 경우는 없었음, 현재까지는 ) 

				nan : 음수의 제곱근을 구하려고 하거나, 0으로 나누려고 했을 때 발생
				이 주석 위쪽에서 모든 값이 정상이어도, 아래 함수(GetAngleVectorToVectorDeg360)에서 반환하는 값이 nan 인 경우가 있으며
				이 때, 위에서 구한 변수들의 값이 인자로 들어가는데 (Dir, TargetPos) <--- 이 수치들이 모두 정상적인 값임에도 nan 이 반환 된다. 
				
				----------------------------- 윗부분은 확실하게 확인된 부분, 아랫부분은 애매한 부분  ------------------
				1. 터질때도 있고 
				2. 안터질때도 있음 , 왜 안터지는지는 잘 모름 
				3. 아래 코드에서 Angle 변수에 nan 이 반환되면, 첫 if문에 들어가지 않고 else 에 진입, 중단점이 걸리게 되는데 
				   다음 프레임에서 왜 m_TopRender (현재터렛액터의 렌더러) 의 트랜스폼데이터가 곱창이 나있는가 <-- 딱 한번 그랬음 
				4. 우연인지는 모르겠으나 아래 if문 코드를 임시로 작성한 이후로는 딱 한번 빼고는 m_TopRender 의 트랜스폼데이터가 멀쩡함 ( 15~20분확인함) 

				*/

				float Angle = float4::GetAngleVectorToVectorDeg360(Dir, TargetPos);

				// 얘는 임시로 값보려고 걸어둔 if문 
				if (-100.0f <= Angle || 100.0f >= Angle)
				{
					float4 Attdir = float4{ 0.0f, 0.0f, Angle };
					m_TopRender->GetTransform()->AddLocalRotation(Attdir * _DeltaTime);

					if (0.0f >= m_FireTime)
					{
						m_FireTime = 1.5f;
						// 일단해 
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
