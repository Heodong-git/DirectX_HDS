#include "PrecompileHeader.h"
#include "Remote_Mine.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Explosion_Effect.h"

#include "GunSpark_Effect.h"
#include "GunSpark_Effect2.h"

Remote_Mine::Remote_Mine()
{
}

Remote_Mine::~Remote_Mine()
{
}

void Remote_Mine::Start()
{
	m_ExplosionPos.reserve(m_ExplosionPosCount);
	float4 ExPos0 = float4{ -45.0f, 30.0f };
	float4 ExPos1 = float4{ -45.0f, 30.0f };
	float4 ExPos2= float4{ -40.0f, 37.0f };
	float4 ExPos3 = float4{ 40.0f, 34.0f };
	float4 ExPos4 = float4{ 0.0f, 0.0f };
	float4 ExPos5 = float4{ -30.0f, -30.0f };
	float4 ExPos6 = float4{ 30.0f, 30.0f };
	float4 ExPos7 = float4{ 40.0f, -20.0f };
	float4 ExPos8 = float4{ 50.0f, -25.0f };
	float4 ExPos9 = float4{ 20.0f, -35.0f };
	float4 ExPos10 = float4{ 0.0f, 55.0f };
	float4 ExPos11 = float4{ 0.0f, -55.0f };

	m_ExplosionPos.push_back(ExPos0);
	m_ExplosionPos.push_back(ExPos1);
	m_ExplosionPos.push_back(ExPos2);
	m_ExplosionPos.push_back(ExPos3);
	m_ExplosionPos.push_back(ExPos4);
	m_ExplosionPos.push_back(ExPos5);
	m_ExplosionPos.push_back(ExPos6);
	m_ExplosionPos.push_back(ExPos7);
	m_ExplosionPos.push_back(ExPos8);
	m_ExplosionPos.push_back(ExPos9);
	m_ExplosionPos.push_back(ExPos10);
	m_ExplosionPos.push_back(ExPos11);

	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);


	if (nullptr == GameEngineSprite::Find("mine_ground"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("mine");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("mine_ground").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "mine_ground", .SpriteName = "mine_ground", .Start = 0, .End = 1 ,
								  .FrameInter = 0.25f , .Loop = true , .ScaleToTexture = true });
	m_Render->ChangeAnimation("mine_ground");
	m_Render->SetScaleRatio(2.0f);
}

// 마인은 폭발 시간을 지정해주고, 지정한 시간이 지나면 폭파한다.
// 이때 폭파상태로 진입하고, 폭발상태에서는 render off, 후 특정 위치에 익스플로전 이펙트 생성 
void Remote_Mine::Update(float _DeltaTime)
{
	if (MineState::EXPLOSION == m_CurState)
	{
		this->Death();

		// 이제 폭발이펙트만 만들어주면됨 
		for (size_t i = 0; i < m_ExplosionPosCount; i++)
		{
			std::shared_ptr<Explosion_Effect> Effect = GetLevel()->CreateActor<Explosion_Effect>();
			Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + m_ExplosionPos[i]);
			Effect->SetType(EffectType::SECOND);
		}

		std::shared_ptr<GunSpark_Effect> Effect1 = GetLevel()->CreateActor<GunSpark_Effect>();
		Effect1->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		Effect1->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 110.0f });
		Effect1->GetRender()->SetScaleRatio(2.0f);

		std::shared_ptr<GunSpark_Effect> Effect2 = GetLevel()->CreateActor<GunSpark_Effect>();
		Effect2->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		Effect2->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 70.0f });
		Effect2->GetRender()->SetScaleRatio(2.0f);
		

		/*std::shared_ptr<GunSpark_Effect2> Effect = GetLevel()->CreateActor<GunSpark_Effect2>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		Effect->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 110.0f });*/
		return;
	}

	if (0.0f >= m_TimeLimit)
	{
		m_TimeLimit = 0.0f;
		m_CurState = MineState::EXPLOSION;
		return;
	}

	m_TimeLimit -= _DeltaTime;
}

void Remote_Mine::Render(float _DeltaTime)
{
}
