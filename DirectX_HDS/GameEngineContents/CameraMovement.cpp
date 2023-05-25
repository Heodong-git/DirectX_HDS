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
	{
		// �̰� �³�.. �ϴ� 0���� ����
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -360.0f , 34.0f };
		float4 RightTop = { 307.0f , 34.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);

		m_MapRanges.insert(make_pair(0, Ranges));
	}
}

void CameraMovement::Update(float _DeltaTime)
{
	if (nullptr != GameEngineCore::GetCurLevel())
	{
		m_MainCamera = GameEngineCore::GetCurLevel()->GetMainCamera();
	}

	// ���� ������ ����� �Ǹ� ī�޶�� �������� ���� 
	if (true == RangeOverCheck(_DeltaTime))
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
	float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

	float4 Dir = PlayerPos - CameraPos;
	Dir.y = 0.0f;
	Dir.Normalize();
	m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
	
}

// ī�޶� ���� ������ �Ѿ���� 
// �翬�� ���� ������ �����ϰ�, ������ ��� ���õǾ��ִٴ� �����Ͽ�. 
// ī�޶� 
bool CameraMovement::RangeOverCheck(float _DeltaTime)
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
	// �ϴ� �Ǳ��ϴµ� ������ �� �ʿ��ϴ�. 
	switch (CurLevelType)
	{
	case LevelType::CLUBMAP0:
	{
		// �̺κ��� ���� ���� �ȵ��.. 
		if (nullptr == m_MainCamera)
		{
			return true;
		}

		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(0);
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("�� ���� ���� ���Ͱ� ����ֽ��ϴ�.");
		}

		// �װԾƴ϶�� ���� ������ �޾ƿ��� 
		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];

		// ī�޶� �̵����� ���� ī�޶��� ��ġ�� ������ ����ٸ� �̵����� �ʵ��� ó��
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// �̵��� ��ġ�� ī�޶��� �̵����ɹ����� ����� �̵����� ����
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			return true;
		}

		// �̵��� �����ϴٸ� false ��ȯ, 
		return false;
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
