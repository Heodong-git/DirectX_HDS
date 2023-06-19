#include "PrecompileHeader.h"
#include "Bullet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	m_Render->SetScaleToTexture("Bullet_00.png");
	m_Render->GetTransform()->SetLocalScale(float4{ 68.0f , 2.0f });

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BULLET);
	m_Collision->GetTransform()->SetLocalScale(float4{ 68.0f , 2.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);
}

// 그리고 총알이. 충돌했다면 바로 삭제. 
void Bullet::Update(float _DeltaTime)
{
	if (GetLiveTime() >= m_LiveTime)
	{
		this->Death();
		return;
	}
	
	// 플레이어의 공격과 충돌했다면
	std::shared_ptr<GameEngineCollision> PlayerCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	
	if (nullptr != PlayerCol)
	{
		// 충돌을 했으면, 이제 콜리전의 액터가 있을거고 
		Bullet* Obj = dynamic_cast<Bullet*>(PlayerCol->GetActor());

		// 그녀석을 다이나믹캐스트로 반환하여 받아봤을때. nullptr이면 Bullet이 아닌거고. 제대로 받아왔으면 불렛인거잖아?
		// 불렛이면 패링안해 
		if (nullptr == Obj)
		{
			m_Parring = true;
			DirCorrection();
		}
	}

	GetTransform()->AddLocalPosition(m_MoveDir * m_MoveSpeed * _DeltaTime);
}

void Bullet::Render(float _DeltaTime)
{
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

		m_Collision->SetOrder(static_cast<int>(ColOrder::PLAYER_ATTACK));
		m_MoveDir = CurMoveDir;
	}

	if (false == m_Parring)
	{
		
	}
}
