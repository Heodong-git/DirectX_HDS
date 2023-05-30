#include "PrecompileHeader.h"
#include "ColEventObj.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

#include "BaseLevel.h"

ColEventObj::ColEventObj()
{
}

ColEventObj::~ColEventObj()
{
}

void ColEventObj::Start()
{
	ComponentSetting();
}

void ColEventObj::Update(float _DeltaTime)
{
	DebugUpdate();
	CollisionUpdate(_DeltaTime);



}

void ColEventObj::Render(float _DeltaTime)
{
}

void ColEventObj::DebugUpdate()
{
}

void ColEventObj::CollisionUpdate(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> PlayerCol = m_Collision->Collision(ColOrder::PLAYER, ColType::AABBBOX2D, ColType::AABBBOX2D);

	// nullptr�� �ƴ϶�� �÷��̾�� �浹�ѰŰ� 
	if (nullptr != PlayerCol)
	{
		// ��� Ŭ���� ���¿����� �����Ǵϱ�
		BaseLevel* CurLevel = GetReturnCastLevel();
		LevelType CurLevelType = CurLevel->GetLevelType();

		switch (CurLevelType)
		{
		case LevelType::CLUBMAP0:
			GameEngineCore::ChangeLevel("ClubLevel_01");
			break;
		case LevelType::CLUBMAP1:
			GameEngineCore::ChangeLevel("ClubLevel_02");
			break;
		case LevelType::CLUBMAP2:
			GameEngineCore::ChangeLevel("ClubLevel_03");
			break;
		case LevelType::CLUBMAP3:
			GameEngineCore::ChangeLevel("ClubLevel_04");
			break;
		case LevelType::CLUBMAP4:
			GameEngineCore::ChangeLevel("ClubLevel_05");
			break;
		}
	}
}

void ColEventObj::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_MainRender->GetTransform()->SetLocalScale({ 50.0f, 50.0f });
	
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::STAGE_COL_OBJ);
	m_Collision->GetTransform()->SetLocalScale({ 50.0f, 50.0f });
}
