#include "PrecompileHeader.h"
#include "CameraMovement.h"

#include "BaseLevel.h"
#include "Player.h"
#include "PixelCollider.h"

CameraMovement* CameraMovement::FollowCamera = nullptr;;

CameraMovement::CameraMovement()
{
	FollowCamera = this;
}

CameraMovement::~CameraMovement()
{
}

void CameraMovement::Start()
{
	// �����ϸ� ���� ������ ī�޶� �޾ƿ´�.. �� ������������������
}

void CameraMovement::Update(float _DeltaTime)
{
	// ���� ������ ����� �Ǹ� ī�޶�� �������� ���� 
	if (true == RangeOverCheck())
	{
		return;
	}

	Move(_DeltaTime);
}

void CameraMovement::Render(float _DeltaTime)
{
}

// �÷��̾ �޾ƿͼ� �����ϰ�. 
void CameraMovement::Move(float _DeltaTime)
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�.");
		return;
	}

	// ī�޶� ���� ���� ���
	// ī�޶�� �÷��̾��� ��ġ�� �޾ƿͼ� �� �������� �̵� �ϱ����� ����üũ 
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
}

// ī�޶� ���� ������ �Ѿ���� 
// �翬�� ���� ������ �����ϰ�, ������ ��� ���õǾ��ִٴ� �����Ͽ�. 
// ī�޶� 
bool CameraMovement::RangeOverCheck()
{
	// �ʰ�����
	std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel.get());

	// ���� null �̸� return
	if (nullptr == CastLevel)
	{
		return true;
	}

	// ���� ������ Ÿ�Ե� ������
	LevelType CurLevelType = CastLevel->GetLevelType();

	if (LevelType::NONE == CurLevelType)
	{
		MsgAssert("������ Ÿ���� ���õ��� �ʾҽ��ϴ�.");
		return true;
	}

	// �ȼ��ö��̴��� �浹���� ��������
	std::shared_ptr<GameEngineTexture> CurMap = PixelCollider::PixelCol->GetColMap();

	if (nullptr == CurMap)
	{
		// MsgAssert("���� ���� nullptr �Դϴ�.");
		return true;
	}

	// ���� nullptr�� �ƴ� ��� ���� ũ�⸦ �޾ƿ��� ... ���⼭.. 
	float4 MapSize = CurMap->GetScale();

	// ���� �� Ÿ�Կ� ���� ������ ���� �ٸ��� ��� 
	// ������ �̵��Ҷ��� �ϸ�Ǵϱ� ���� 
	// ���⼭ ��� �ҰŴ� ���� 
	// �ʿ����� ������ ���� �ϼ�
	switch (CurLevelType)
	{
	case LevelType::CLUBMAP0:
	{
		int a = 0;
		a = 123;
	}
		break;
	case LevelType::CLUBMAP1:
	{
		int a = 0;
	}
		break;
	case LevelType::CLUBMAP2:
	{
		int a = 0;
	}
		break;
	case LevelType::CLUBMAP3:
		break;
	case LevelType::CLUBMAP4:
		break;
	case LevelType::NONE:
		break;
	default:
		break;
	}

	// 
	return true;
}
