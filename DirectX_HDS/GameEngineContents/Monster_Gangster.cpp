#include "PrecompileHeader.h"
#include "Monster_Gangster.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

Monster_Gangster::Monster_Gangster()
{
}

Monster_Gangster::~Monster_Gangster()
{
}

void Monster_Gangster::Start()
{
	// ���������� �� ����
	ComponentSetting();
	// ���ҽ� �ε�
	LoadAndCreateAnimation();

	if (false == GameEngineInput::IsKey("gangster_DebugSwitch"))
	{
		GameEngineInput::CreateKey("gangster_DebugSwitch", 'Q');
	}
}

void Monster_Gangster::Update(float _DeltaTime)
{
	DebugUpdate();
}

void Monster_Gangster::Render(float _DeltaTime)
{
}

void Monster_Gangster::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();
	}

	if (true == IsDebug())
	{
		m_DebugRender->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender->Off();
	}
}

void Monster_Gangster::ComponentSetting()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	
	// ������, �浹ü ����
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f , 50.0f });
	m_MainRender->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
	m_Collision->GetTransform()->SetLocalScale({ 100.0f, 100.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 0.0f });

	// ����׷��� ����
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
}

void Monster_Gangster::LoadAndCreateAnimation()
{
	// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
	{
		if (nullptr == GameEngineSprite::Find("gangster_idle"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("katanazero_resources");
			Dir.Move("katanazero_resources");
			Dir.Move("Texture");
			Dir.Move("ClubLevel");
			Dir.Move("gangster");
			
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_idle").GetFullPath());
	
			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_idle", .SpriteName = "gangster_idle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->ChangeAnimation("gangster_idle");
}


// -------------------------------------------- State ----------------------------------------------------
// 