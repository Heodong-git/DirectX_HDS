#include "PrecompileHeader.h"
#include "EnemyFollow_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>


EnemyFollow_Effect::EnemyFollow_Effect()
{
}

EnemyFollow_Effect::~EnemyFollow_Effect()
{
}

void EnemyFollow_Effect::SetObject(std::shared_ptr<GameEngineObject> _Obj)
{
	if (nullptr == _Obj)
	{
		MsgAssert("������Ʈ�� nullptr �Դϴ�.");
	}

	m_FollowObj = _Obj;
}

void EnemyFollow_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	// ��������Ʈ������ nullptr �϶��� 
	if (nullptr == GameEngineSprite::Find("enemy_follow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("enemy_follow").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "enemy_follow", .SpriteName = "enemy_follow", .Start = 0, .End = 1 ,
								  .FrameInter = 0.2f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);
	m_Render->ChangeAnimation("enemy_follow");
}

void EnemyFollow_Effect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		this->Death();
		if (nullptr != m_Render)
		{
			m_Render = nullptr;
		}
	}

	if (nullptr != m_FollowObj)
	{
		if (true == m_IsPivot)
		{
			GetTransform()->SetWorldPosition(m_FollowObj->GetTransform()->GetWorldPosition() + m_Pivot);
			return;
		}

		GetTransform()->SetWorldPosition(m_FollowObj->GetTransform()->GetWorldPosition());
	}
}

void EnemyFollow_Effect::Render(float _DeltaTime)
{
}
