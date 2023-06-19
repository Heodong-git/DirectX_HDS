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

// �׸��� �Ѿ���. �浹�ߴٸ� �ٷ� ����. 
void Bullet::Update(float _DeltaTime)
{
	if (GetLiveTime() >= m_LiveTime)
	{
		this->Death();
		return;
	}
	
	// �÷��̾��� ���ݰ� �浹�ߴٸ�
	std::shared_ptr<GameEngineCollision> PlayerCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	
	if (nullptr != PlayerCol)
	{
		// �浹�� ������, ���� �ݸ����� ���Ͱ� �����Ű� 
		Bullet* Obj = dynamic_cast<Bullet*>(PlayerCol->GetActor());

		// �׳༮�� ���̳���ĳ��Ʈ�� ��ȯ�Ͽ� �޾ƺ�����. nullptr�̸� Bullet�� �ƴѰŰ�. ����� �޾ƿ����� �ҷ��ΰ��ݾ�?
		// �ҷ��̸� �и����� 
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
		// �и��� true ��� �Ѿ��� �ݻ�Ǿ��ٴ°Ű�. 
		// ���� ������ ��Ȯ�� �ݴ�� �ٲ��ָ� �ȴ� 
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
