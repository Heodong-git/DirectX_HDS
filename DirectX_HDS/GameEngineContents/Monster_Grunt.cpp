#include "PrecompileHeader.h"
#include "Monster_Grunt.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Monster_Grunt::Monster_Grunt()
{
}

Monster_Grunt::~Monster_Grunt()
{
}

void Monster_Grunt::Start()
{
	if (false == GameEngineInput::IsKey("Grunt_DebugSwitch"))
	{
		GameEngineInput::CreateKey("Grunt_DebugSwitch", 'Q');
	}

	// ���������� �� ����
	ComponentSetting();
	// ���ҽ� �ε�
	LoadAndCreateAnimation();

	ChangeState(GruntState::IDLE);
}

void Monster_Grunt::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Monster_Grunt::Render(float _DeltaTime)
{
}

void Monster_Grunt::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("gangster_debugswitch"))
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

void Monster_Grunt::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::MONSTER));
	m_MainRender->GetTransform()->SetLocalPosition({ 0, 0 });
	m_MainRender->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
	m_Collision->GetTransform()->SetLocalScale({ 100.0f, 100.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 0.0f });
}

void Monster_Grunt::LoadAndCreateAnimation()
{
	//// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
	//{
	//	if (nullptr == GameEngineSprite::Find("grunt_idle"))
	//	{
	//		GameEngineDirectory Dir;
	//		Dir.MoveParentToDirectory("katanazero_resources");
	//		Dir.Move("katanazero_resources");
	//		Dir.Move("Texture");
	//		Dir.Move("ClubLevel");
	//		Dir.Move("grunt");

	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_idle").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_walk").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_hitground").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_run").GetFullPath());

	//		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	//	}
	//}

	//m_MainRender->CreateAnimation({ .AnimationName = "grunt_idle", .SpriteName = "grunt_idle", .Start = 0, .End = 7 ,
	//							  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true });
}


void Monster_Grunt::DirCheck()
{
	// ����Ƽ��, �װ�Ƽ�� �Լ� ���ÿ� ������ �ƴ϶� ������ Ʈ�������� ����ؾ��� ���� 
	// ����üũ 
	// ������ 
	if (0 < m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	// ���� 
	else if (0 > m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

// -------------------------------------------- State ----------------------------------------------------

void Monster_Grunt::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case GruntState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case GruntState::WALK:
		WalkUpdate(_DeltaTime);
		break;
	case GruntState::CHASE:
		ChaseUpdate(_DeltaTime);
		break;
	case GruntState::HITGROUND:
		HitGroundUpdate(_DeltaTime);
		break;
	}
}

// state ����, ����� ������ start, ���� ������ end ����
void Monster_Grunt::ChangeState(GruntState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	//WALK,	 // �ȱ�
	//	CHASE,	 // �ٱ� 
	//	HIT,	 // �ĸ���
	//	AIM,	 // ���� 

	// start 
	switch (m_NextState)
	{
	case GruntState::IDLE:
		IdleStart();
		break;
	case GruntState::WALK:
		WalkStart();
		break;
	case GruntState::CHASE:
		ChaseStart();
		break;
	case GruntState::HITGROUND:
		HitGroundStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case GruntState::IDLE:
		IdleEnd();
		break;
	case GruntState::WALK:
		WalkEnd();
		break;
	case GruntState::CHASE:
		ChaseEnd();
		break;
	case GruntState::HITGROUND:
		HitGroundEnd();
		break;
	}
}


void Monster_Grunt::IdleStart()
{
}

void Monster_Grunt::IdleUpdate(float _DeltaTime)
{
}

void Monster_Grunt::IdleEnd()
{
}

void Monster_Grunt::WalkStart()
{
}

void Monster_Grunt::WalkUpdate(float _DeltaTime)
{
}

void Monster_Grunt::WalkEnd()
{
}

void Monster_Grunt::ChaseStart()
{
}

void Monster_Grunt::ChaseUpdate(float _DeltaTime)
{
}

void Monster_Grunt::ChaseEnd()
{
}

void Monster_Grunt::HitGroundStart()
{
}

void Monster_Grunt::HitGroundUpdate(float _DeltaTime)
{
}

void Monster_Grunt::HitGroundEnd()
{
}
