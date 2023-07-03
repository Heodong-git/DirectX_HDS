#include "PrecompileHeader.h"
#include "Bullet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ReflectEffect.h"

#include "Player.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	if (nullptr == GameEngineSprite::Find("Bullet"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("bullet").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BULLET);
	m_Render->SetTexture("Bullet_00.png");
	m_Render->GetTransform()->SetLocalScale(float4{ 34.0f , 2.0f });

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BULLET);
	m_Collision->GetTransform()->SetLocalScale(float4{ 34.0f , 2.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);
}

void Bullet::Update(float _DeltaTime)
{
	if (GetLiveTime() >= m_LiveTime)
	{
		if (true == IsUpdate())
		{
			this->Death();
		}
		return;
	}
	
	GetTransform()->AddLocalPosition(m_MoveDir * m_MoveSpeed * _DeltaTime);

	std::shared_ptr<GameEngineCollision> DoorCol = m_Collision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != DoorCol)
	{
		m_Collision->Off();
		this->Death();
		return;
	}

	// 플레이어의 공격과 충돌했다면
	// 임시로 구충돌로 
	std::shared_ptr<GameEngineCollision> AttCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK);
	if (nullptr != AttCol)
	{
		{
			// 내가 패링이 아닌상태에서
			if (false == m_Parring)
			{
				m_SoundPlayer = GameEngineSound::Play("slash_bullet_parring.wav");
				m_SoundPlayer.SetVolume(0.7f);
				CreateReflectEffect();
			}
			// 충돌을 했으면, 이제 콜리전의 액터가 있을거고 
			Bullet* Obj = dynamic_cast<Bullet*>(AttCol->GetActor());
			// 여기서 리플렉트 이펙트 만들어 

			// 그녀석을 다이나믹캐스트로 반환하여 받아봤을때. nullptr이면 Bullet이 아닌거고. 제대로 받아왔으면 불렛인거잖아?
			// 불렛이면 패링안해 
			if (nullptr == Obj)
			{
				m_Parring = true;
				DirCorrection();
			}
		}
		return;
		// 반사사운드 출력
	}

	if (true == this->IsUpdate())
	{
		std::shared_ptr<GameEngineCollision> PlayerCol = m_Collision->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != PlayerCol)
		{
			GameEngineSound::Play("death_bullet.wav");
			Player::MainPlayer->BulletCollision();
			Player::MainPlayer->CreateHitEffect(m_Collision);
			this->Death();
			return;
		}
	}


	
	if (true == m_Parring)
	{
		// 이동시키는데, 내가 몬스터와 충돌했다면 나를 데스, 몬스터도 총알과 충돌했다면 데스
		std::shared_ptr<GameEngineCollision> MonsterCol = m_Collision->Collision(ColOrder::MONSTER, ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != MonsterCol)
		{
			GameEngineSound::Play("death_bullet.wav");
			// 충돌체의 액터를 받아와서, 액터의 오버라이드된 불릿충돌 함수 호출

			// 그리고 여기서 리플렉트 이펙트도 만들어야함 
			std::shared_ptr<BaseActor> Actor = MonsterCol->GetActor()->DynamicThis<BaseActor>();
			Actor->BulletCollision();
			this->Death();
			return;
		}
	}
}

void Bullet::Render(float _DeltaTime)
{
}

void Bullet::CreateReflectEffect()
{
	std::shared_ptr<ReflectEffect> Effect = GetLevel()->CreateActor<ReflectEffect>();
	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

void Bullet::DirCorrection()
{
	if (true == m_Parring && false == m_DirChange)
	{
		m_DirChange = true;
		float4 CurMoveDir = m_MoveDir;
		// 패링이 true 라면 총알이 반사되었다는거고. 
		// 현재 방향을 정확히 반대로 바꾸주면 된다 
		if (CurMoveDir.x <= 0.0f)
		{
			CurMoveDir.x = abs(CurMoveDir.x);
		}

		else if (CurMoveDir.x > 0.0f)
		{
			CurMoveDir.x = -CurMoveDir.x;
		}

		if (CurMoveDir.y <= 0.0f)
		{
			CurMoveDir.y = abs(CurMoveDir.y);
		}

		else if (CurMoveDir.y > 0.0f)
		{
			CurMoveDir.y = -CurMoveDir.y;
		}

		m_Collision->SetOrder(static_cast<int>(ColOrder::PLAYER_BULLET));
		m_MoveDir = CurMoveDir;
	}
}
