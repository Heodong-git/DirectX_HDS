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
	// 蕉艦五戚芝兄希, 3歳拝 筈希, 郊巨, 匂転 
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	// m_MainRender->Off();

	m_TopRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_HolderRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_BodyRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::TURRET_BODY);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4.0f , 4.0f , 1.0f});
	m_DebugRender->Off();

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
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
	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState() ||
		BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD == GetReturnCastLevel()->GetCurState())
	{
		return;
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
		// 鎧亜 走榎 葛源 雌殿析凶.
		if (TurretState::NORMAL == m_CurState)
		{
			std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
			if (nullptr != Col)
			{
				// 巴傾戚嬢人 中宜梅陥檎, 
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
				// 働舛弘端研 郊虞左惟 馬奄 是廃

				// 展為税 是帖研 閤焼紳陥. 
				float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

				// 鎧 是帖研 閤焼紳陥. 
				float4 TurretPos = GetTransform()->GetLocalPosition();
				
				// 鎧亜 左壱 赤澗 号狽聖 姥廃陥. (唖亀)
				float4 TurretPos1 = m_TopRender->GetTransform()->GetLocalRotation();

				// z 葵聖 昔切稽 隔嬢爽檎, 昔切稽 隔嬢層 困斗亜 左壱 赤澗 号狽葵聖 鋼発背層陥, float4 稽 
				float4 Dir = float4::AngleToDirection2DToDeg(TurretPos1.z);

				// 号狽困斗 姥背爽壱 葛源虞戚綜 
				float4 TargetPos = PlayerPos - TurretPos;
				TargetPos.Normalize();

				/*
				降持馬澗 庚薦繊 : Angle 葵戚 nan 戚 級嬢神壱 陥製 覗傾績拭 斗型税 転兄希君亜 紫虞走檎辞 斗像 
				nan : 製呪税 薦咽悦聖 姥馬形壱 馬暗蟹, 0生稽 蟹刊形壱 梅聖 凶 降持
				戚 爽汐 是楕拭辞 乞窮 葵戚 舛雌戚嬢亀, 焼掘 敗呪(GetAngleVectorToVectorDeg360)拭辞 鋼発馬澗 葵戚 nan 昔 井酔亜 赤生悟
				戚 凶, 是拭辞 姥廃 痕呪級税 葵戚 昔切稽 級嬢亜澗汽 (Dir, TargetPos) <--- 戚 呪帖級戚 乞砧 舛雌旋昔 葵績拭亀 nan 戚 鋼発 吉陥. 
				
				----------------------------- 性採歳精 溌叔馬惟 溌昔吉 採歳, 焼熊採歳精 蕉古廃 採歳  ------------------
				1. 斗霜凶亀 赤壱 
				2. 照斗霜凶亀 赤製 , 訊 照斗走澗走澗 設 乞硯 
				3. 焼掘 坪球拭辞 Angle 痕呪拭 nan 戚 鋼発鞠檎, 湛 if庚拭 級嬢亜走 省壱 else 拭 遭脊, 掻舘繊戚 杏軒惟 鞠澗汽 
				   陥製 覗傾績拭辞 訊 m_TopRender (薄仙斗型衝斗税 兄希君) 税 闘沓什廿汽戚斗亜 咽但戚 蟹赤澗亜??? せせせせせせせせせせせせせ
				*/

				float Angle = float4::GetAngleVectorToVectorDeg360(Dir, TargetPos);

				// 剰澗 績獣稽 葵左形壱 杏嬢黍 if庚 
				if (-100.0f <= Angle || 100.0f >= Angle)
				{
					float4 Attdir = float4{ 0.0f, 0.0f, Angle };
					m_TopRender->GetTransform()->AddLocalRotation(Attdir * _DeltaTime);

					if (0.0f >= m_FireTime)
					{
						m_FireTime = 1.5f;
						// 析舘背 
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


		// 蕉艦五戚芝戚 曽戟鞠醸聖凶, 闘沓什廿雌殿虞檎 
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
