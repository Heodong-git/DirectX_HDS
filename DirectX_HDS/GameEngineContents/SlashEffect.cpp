#include "PrecompileHeader.h"
#include "SlashEffect.h"

#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

#include "SlashLaser_Effect.h"

SlashEffect::SlashEffect()
{
}

SlashEffect::~SlashEffect()
{
}

void SlashEffect::Start()
{
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
}

void SlashEffect::Update(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	CollisionUpdate(_DeltaTime);
}

void SlashEffect::Render(float _DeltaTime)
{
	
}

void SlashEffect::ComponentSetting()
{
	// ������Ʈ ����
	// ������ 
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
	float Angle = atan2f(Dir.y, Dir.x) * GameEngineMath::RadToDeg;
	m_Render->GetTransform()->SetLocalRotation({ 0 , 0 , Angle });

	// �浹ü 
	// �������� �ӽ�ũ�� 
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::PLAYER_ATTACK);
	m_Collision->GetTransform()->SetLocalScale({ 100, 50 });
}

void SlashEffect::CollisionUpdate(float _DeltaTime)
{
	// ����Ʈ�� ���Ϳ� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::MONSTER, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// ���� ������ �浹 �ѰŰ�. 
	if (nullptr != Col)
	{
		// �浹�� ������ ��ǥ 
		float4 ColPos = Col->GetTransform()->GetParent()->GetLocalPosition();
		const float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

		float4 Dir = ColPos - PlayerPos;

		float EffectX = 0.0f; 
		float EffectY = 0.0f;
		if (ColPos.x >= PlayerPos.x)
		{
			EffectX = -900.0f;
		}

		else
		{
			EffectX = 900.0f;
		}

		if (ColPos.y >= PlayerPos.y)
		{
			EffectY = -320.0f;
		}

		else
		{
			EffectY = 320.0f;
		}
		
		// �׷��� ������ ����Ʈ�� �����ϴµ�. 
		std::shared_ptr<SlashLaser_Effect> Effect = GetLevel()->CreateActor<SlashLaser_Effect>(static_cast<int>(RenderOrder::EFFECT));
		
		// ��ġ�� ���� �Ű����ҵ�. 
		Effect->GetTransform()->SetLocalPosition({ EffectX , EffectY });
		Effect->SetMovePos(ColPos);
	}
}

void SlashEffect::MoveUpdate(float _DeltaTime)
{
	// ���⼭ �浹üũ���ؼ� �浹ü�� ������Ű�°� ���ҰŰ�����
	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd())
		{
			this->Death();
			return;
		}
	}

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�. ���� ");
		return;
	}

	float RenderPivot = Player::MainPlayer->GetRenderPivot();
	const float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	m_Render->GetTransform()->SetLocalPosition({ PlayerPos.x , PlayerPos.y + RenderPivot });
	m_Collision->GetTransform()->SetLocalPosition({ PlayerPos.x , PlayerPos.y + RenderPivot });
}
