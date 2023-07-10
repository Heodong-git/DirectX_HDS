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

void Bullet::BulletDeath()
{	
	ChangeState(EffectState::DEATH);
	m_Collision->Off();
	m_Render->Off();
	m_IsRecording = false;
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

		// ����� �Լ� ȣ�� �� , ���� ��������� 0 �̶�� ���� death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}


	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	// �̰� �����־ ��������°Ű��⵵�ѵ� 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}

	// ���̺�Ÿ�� ����� ������ �ƴ�, 
	if (GetLiveTime() >= m_LiveTime)
	{
		if (true == IsUpdate() && EffectState::DEATH != m_CurState)
		{
			BulletDeath();
		}

		return;
	}
	
	// �̵���Ű��
	GetTransform()->AddLocalPosition(m_MoveDir * m_MoveSpeed * _DeltaTime);

	// �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> DoorCol = m_Collision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != DoorCol)
	{
		// �浹ü, �������� ���� �������·� �ٲٴµ� ����. 
		// ���� �������¸� 
		BulletDeath();
		return;
	}

	// �÷��̾��� ���ݰ� �浹�ߴٸ�
	// �ӽ÷� ���浹�� 
	std::shared_ptr<GameEngineCollision> AttCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK);
	if (nullptr != AttCol)
	{
		{
			// ���� �и��� �ƴѻ��¿���
			if (false == m_Parring)
			{
				m_SoundPlayer = GameEngineSound::Play("slash_bullet_parring.wav");
				m_SoundPlayer.SetVolume(0.7f);
				CreateReflectEffect();
			}
			// �浹�� ������, ���� �ݸ����� ���Ͱ� �����Ű� 
			Bullet* Obj = dynamic_cast<Bullet*>(AttCol->GetActor());
			// ���⼭ ���÷�Ʈ ����Ʈ ����� 

			// �׳༮�� ���̳���ĳ��Ʈ�� ��ȯ�Ͽ� �޾ƺ�����. nullptr�̸� Bullet�� �ƴѰŰ�. ����� �޾ƿ����� �ҷ��ΰ��ݾ�?
			// �ҷ��̸� �и����� 
			if (nullptr == Obj)
			{
				m_Parring = true;
				DirCorrection();
			}
		}
		return;
		// �ݻ���� ���
	}

	if (true == this->IsUpdate())
	{
		std::shared_ptr<GameEngineCollision> PlayerCol = m_Collision->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != PlayerCol)
		{
			if (true == Player::MainPlayer->IsInvincibility())
			{
				return;
			}

			GameEngineSound::Play("death_bullet.wav");
			Player::MainPlayer->BulletCollision();
			Player::MainPlayer->CreateHitEffect(m_Collision);
			BulletDeath();
			return;
		}
	}


	
	if (true == m_Parring)
	{
		// �̵���Ű�µ�, ���� ���Ϳ� �浹�ߴٸ� ���� ����, ���͵� �Ѿ˰� �浹�ߴٸ� ����
		std::shared_ptr<GameEngineCollision> MonsterCol = m_Collision->Collision(ColOrder::MONSTER, ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != MonsterCol)
		{
			GameEngineSound::Play("death_bullet.wav");
			// �浹ü�� ���͸� �޾ƿͼ�, ������ �������̵�� �Ҹ��浹 �Լ� ȣ��

			// �׸��� ���⼭ ���÷�Ʈ ����Ʈ�� �������� 
			std::shared_ptr<BaseActor> Actor = MonsterCol->GetActor()->DynamicThis<BaseActor>();
			Actor->BulletCollision();
			BulletDeath();
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

		m_Collision->SetOrder(static_cast<int>(ColOrder::PLAYER_BULLET));
		m_MoveDir = CurMoveDir;
	}
}
