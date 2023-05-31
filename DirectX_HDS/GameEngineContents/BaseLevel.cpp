#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Map.h"
#include "Player.h"
#include "FadeEffect.h"
#include "ColEventObj.h"
#include "Go_UI.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

// ��緹������ �ʿ��ϱ� ������ base level ���� ������ �ִ´�. 
// �ٵ� �ϴ� ���� ���� �ϼ��ϸ� ���� �ϴ� ���� Ŭ������ 00���� ���� 
void BaseLevel::Start()
{
	CameraSetting();

	// ���� �������� 
	m_ResetActors.reserve(8);

	// ���̵��ξƿ� ����Ʈ
	m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{

	// ���� Ŀ���� nullptr �� �ƴ϶�� 
	// �޾ƿͼ� ������������ ����
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	// ���⼭ Go�� ����� 
	// ���� ���� Ŭ���� �Ǿ�����
	if (true == IsClear() && LevelType::TITLE != m_LevelType)
	{
		if (false == m_IsClear)
		{
			m_IsClear = true;
			m_ColObj = CreateActor<ColEventObj>(static_cast<int>(RenderOrder::DEBUG));
			m_GoUI = CreateActor<Go_UI>(static_cast<int>(RenderOrder::UI));
			switch (m_LevelType)
			{
			case LevelType::CLUBMAP0:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 959.0f , -75.0f });
			}
				break;
			case LevelType::CLUBMAP1:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 653.0f, 48.0f});
			}
				break;
			case LevelType::CLUBMAP2:
			{

			}
				break;
			case LevelType::CLUBMAP3:
			{

			}
				break;
			case LevelType::CLUBMAP4:
			{

			}
				break;
			case LevelType::NONE:
				break;
			default:
				break;
			}
		}
	}


	// �÷��̾� ���̵�������Ʈ 
	if (true == Player::MainPlayer->IsSlowSkill())
	{
		GetFadeEffect()->FadeIn();
	}

	else if (false == Player::MainPlayer->IsSlowSkill())
	{
		//m_FadeEffect->FadeOut();
	}

	if (true == GameEngineInput::IsDown("ClubLevel_DebugSwitch"))
	{
		DebugSwitch();

		if (true == IsDebug())
		{
			ChangeColMap();
			return;
		}

		if (false == IsDebug())
		{
			ChangeMap();
			return;
		}
	}

	if (BaseLevel::LevelState::WAIT == m_CurState)
	{
		return;
	}

	// ��� ������ �ϴ� �ӽ÷� 
	// ���� ���� ������Ʈ�� Play ��� ���ѽð��� ���ҽ�Ų��. 
	if (BaseLevel::LevelState::PLAY == m_CurState)
	{

		if (0 >= m_LimitTime)
		{
			// �÷��̾� ���, ���� �����·� ����
			int a = 0;
		}

		m_LimitTime -= GameEngineTime::GlobalTime.GetDeltaTime();
	}

	GameEngineLevel::Update(_DeltaTime);
}

void BaseLevel::LevelChangeStart()
{
	
}


void BaseLevel::CameraSetting()
{
	// ī�޶���
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}



void BaseLevel::ChangeMap()
{
	if (nullptr == m_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_LevelType)
	{
	case LevelType::CLUBMAP0:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");
		break;
	case LevelType::CLUBMAP1:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");
		break;
	case LevelType::CLUBMAP2:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");
		break;
	case LevelType::CLUBMAP3:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_03.png");
		break;
	case LevelType::CLUBMAP4:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_04.png");
		break;
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}

void BaseLevel::ChangeColMap()
{
	// ���� ������ Ÿ��Ʋ �����̶�� return �ؾ���.
	if (LevelType::NONE== m_LevelType)
	{
		// Ÿ��Ʋ���� �� ��� ��Ÿ���� ���õ��� �ʱ⶧���� �ش� �Լ��� ȣ��Ǹ� �ٷ� return; 
			return;
	}
	if (nullptr == m_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_LevelType)
	{
	case LevelType::CLUBMAP0:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_00.png");
		break;
	case LevelType::CLUBMAP1:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_01.png");
		break;
	case LevelType::CLUBMAP2:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_02.png");
		break;
	case LevelType::CLUBMAP3:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_03.png");
		break;
	case LevelType::CLUBMAP4:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_04.png");
		break;
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}

void BaseLevel::DebugCamera()
{
}

// ���ͻ����� ���Ϳ� Ǫ��
void BaseLevel::Push_ResetActor(std::shared_ptr<class BaseActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("���Ͱ� nullptr �Դϴ�.");
		return;
	}

	m_ResetActors.push_back(_Actor);
}

// ���� ������ ȣ���ϸ� �׳� �갡 ȣ��Ǵ°��� �ڽĿ��� �����Ǵ� �����ʰ� 
void BaseLevel::LevelReset()
{
	// �ϴ� ������ ���ѽð� �ʱ�ȭ 
	Reset();

	// ���� Start ���� �ݵ�� ���Ϳ� �߰�
	//if (0 == m_ResetActors.size())
	//{
	//	// �ϴܰɾ�ΰ�
	//	// MsgAssert("���� �ʱ�ȭ�Ǿ���� ������ ���� 0 �Դϴ�.");
	//	return;
	//}

	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	// ���� ���Ϳ� ����� ���͵��� ��ȸ�ϸ鼭 ���� 
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Reset();
	}

	// �ϴ� ������� , �Ŀ� �߰� �۾��ʿ��� ��� �ڵ� �ۼ�
}

void BaseLevel::Reset()
{
	m_IsClear = false;
	SetLimitTime();
	ResetMonsterCount();
	ResetColObj();
	SetState(BaseLevel::LevelState::PLAY);
}

void BaseLevel::ResetColObj()
{
	if (nullptr != m_ColObj)
	{
		m_ColObj->Death();
	}
}

bool BaseLevel::IsClear()
{
	if (0 == m_MonsterCount)
	{
		return true;
	}

	return false;
}
