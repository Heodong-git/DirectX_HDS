#include "PrecompileHeader.h"
#include "TeleportEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TeleportEffect::TeleportEffect()
{
	
}

TeleportEffect::~TeleportEffect()
{
}

void TeleportEffect::Start()
{
	LoadAndCreateAnimation();
	SetRenders();
}

void TeleportEffect::Update(float _DeltaTime)
{ 
	// 건스파크 이펙트의 마지막 애니메이션까지 종료 되었다면
	if (true == m_SparkRenders[m_FirstRenderCount - 1]->IsAnimationEnd())
	{
		// 모든렌더러를 순회하며 off 
		this->Death();
		return;
	}

	// 클라우드의 경우 반복문을 돌아서 애니메이션이 종료 되었다면 off 처리 
	for (size_t i = 0; i < m_CloudRenders.size(); ++i)
	{
		if (true == m_CloudRenders[i]->IsAnimationEnd())
		{
			m_CloudRenders[i]->Off();
		}
	}

}

void TeleportEffect::Render(float _DeltaTime)
{
}


void TeleportEffect::LoadAndCreateAnimation()
{
	// 일단그냥 이렇게 
	// first effect
	if (nullptr == GameEngineSprite::Find("gunspark_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	if (nullptr == GameEngineSprite::Find("gunspark_effect2"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	// gunsmoke
	if (nullptr == GameEngineSprite::Find("gunsmoke_effect2"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");
		Dir.Move("gunsmoke_effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunsmoke_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	// second effect
	if (nullptr == GameEngineSprite::Find("dashcloud"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("dashcloud").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	// cloud
	

	m_SparkRenders.reserve(m_FirstRenderCount + m_SecondRenderCount);
	for (size_t i = 0; i < m_FirstRenderCount + m_SecondRenderCount; ++i)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

		if (i < m_FirstRenderCount)
		{
			Render->CreateAnimation({ .AnimationName = "gunspark_effect", .SpriteName = "gunspark_effect", .Start = 0, .End = 7 ,
							  .FrameInter = 0.12f , .Loop = false , .ScaleToTexture = true });
			Render->ChangeAnimation("gunspark_effect");
		}

		if (i >= m_FirstRenderCount)
		{
			Render->CreateAnimation({ .AnimationName = "gunspark_effect2", .SpriteName = "gunspark_effect2", .Start = 0, .End = 7 ,
							  .FrameInter = 0.12f , .Loop = false , .ScaleToTexture = true });
			Render->ChangeAnimation("gunspark_effect2");
		}

		Render->SetScaleRatio(2.0f);
		m_SparkRenders.push_back(Render);
	}

	m_CloudRenders.reserve(m_CloudRenderCount + m_CloudRenderCount2);
	for (size_t i = 0; i < m_CloudRenderCount + m_CloudRenderCount2; ++i)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

		// 대시클라우드 
		if (i < m_CloudRenderCount)
		{
			Render->CreateAnimation({ .AnimationName = "dashcloud", .SpriteName = "dashcloud", .Start = 0, .End = 9 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
			Render->ChangeAnimation("dashcloud");
		}
		
		// 대시클라우드의 개수보다 더 크다면 
		if (i >= m_CloudRenderCount)
		{
			// 다른 클라우드임 
			Render->CreateAnimation({ .AnimationName = "gunsmoke_effect2", .SpriteName = "gunsmoke_effect2", .Start = 0, .End = 11 ,
							  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });
			Render->ChangeAnimation("gunsmoke_effect2");
		}

		Render->SetScaleRatio(2.0f);
		m_CloudRenders.push_back(Render);
	}
}

void TeleportEffect::SetRenders()
{
	// 디버그 렌더
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 10.0f, 10.0f });
	m_DebugRender->Off();

	// 첫번째 
	m_SparkRenders[0]->GetTransform()->SetLocalPosition(float4{ -120.0f , 10.0f });
	m_SparkRenders[0]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 180.0f });

	m_SparkRenders[1]->GetTransform()->SetLocalPosition(float4{ 70.0f, 10.0f, 0.0f });

	m_SparkRenders[2]->GetTransform()->SetLocalPosition(float4{ -105.0f , 30.0f });
	m_SparkRenders[2]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 160.0f });

	m_SparkRenders[3]->GetTransform()->SetLocalPosition(float4{ 50.0f , 30.0f });
	m_SparkRenders[3]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 40.0f });

	m_SparkRenders[4]->GetTransform()->SetLocalPosition(float4{ -90.0f , 60.0f });
	m_SparkRenders[4]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 140.0f });

	m_SparkRenders[5]->GetTransform()->SetLocalPosition(float4{ 30.0f , 60.0f });
	m_SparkRenders[5]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 77.0f });

	m_SparkRenders[6]->GetTransform()->SetLocalPosition(float4{ -10.0f , 140.0f });
	m_SparkRenders[6]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 95.0f });

	m_SparkRenders[7]->GetTransform()->SetLocalPosition(float4{ -30.0f , 126.0f });
	m_SparkRenders[7]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 113.0f });

	// 두번째 
	m_SparkRenders[8]->GetTransform()->SetLocalPosition(float4{ -50.0f , 2.0f });
	m_SparkRenders[8]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 180.0f });

	m_SparkRenders[9]->GetTransform()->SetLocalPosition(float4{ -40.0f , 20.0f });
	m_SparkRenders[9]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 160.0f });

	m_SparkRenders[10]->GetTransform()->SetLocalPosition(float4{ 0.0f , 20.0f });
	m_SparkRenders[10]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 170.0f });

	m_SparkRenders[11]->GetTransform()->SetLocalPosition(float4{ -30.0f , 40.0f });
	m_SparkRenders[11]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 155.0f });

	// 클라우드 
	m_CloudRenders[0]->GetTransform()->SetLocalPosition(float4{ -60.0f , 20.0f });
	m_CloudRenders[0]->GetTransform()->SetLocalRotation(float4{ 0.0f, 180.0f, 0.0f });
	m_CloudRenders[1]->GetTransform()->SetLocalPosition(float4{ 60.0f , 20.0f });

	m_CloudRenders[2]->GetTransform()->SetLocalPosition(float4{ -60.0f , 80.0f });
	m_CloudRenders[2]->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f , 120.0f});
	m_CloudRenders[2]->SetScaleRatio(3.0f);

	m_CloudRenders[3]->GetTransform()->SetLocalPosition(float4{ -80.0f , 60.0f });
	m_CloudRenders[3]->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f , 140.0f });
	m_CloudRenders[3]->SetScaleRatio(3.0f);

	m_CloudRenders[4]->GetTransform()->SetLocalPosition(float4{ -10.0f , 90.0f});
	m_CloudRenders[4]->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f , 90.0f });
	m_CloudRenders[4]->SetScaleRatio(3.0f);

	m_CloudRenders[5]->GetTransform()->SetLocalPosition(float4{ 40.0f , 80.0f });
	m_CloudRenders[5]->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f , 65.0f });
	m_CloudRenders[5]->SetScaleRatio(2.0f);

	m_CloudRenders[6]->GetTransform()->SetLocalPosition(float4{ -100.0f , 0.0f });
	m_CloudRenders[6]->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f , 180.0f });
	m_CloudRenders[6]->SetScaleRatio(2.5f);
}
