#include "PrecompileHeader.h"
#include "PixelCollider.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"

PixelCollider::PixelCollider()
{
}

PixelCollider::~PixelCollider()
{
}

void PixelCollider::Start()
{
	m_CurColMap = GameEngineTexture::Find("Club_0_ColMap.png");
}

bool PixelCollider::PixelCollision(class GameEngineObject* _Object)
{
	if (nullptr == m_CurColMap)
	{
		MsgAssert("ColMap �� nullptr �Դϴ�.");
		return false;
	}

	if (nullptr == _Object)
	{
		MsgAssert("���ڷ� ���� ������Ʈ�� nullptr �Դϴ�.");
		return false;
	}

	float4 CheckPos = _Object->GetTransform()->GetLocalPosition();
	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	float CheckX = CheckPos.x + WidthHalf;
	float CheckY = HeightHalf - CheckPos.y;

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColMapPixel = m_CurColMap->GetPixel(static_cast<int>(CheckX), static_cast<int>(CheckY));

	// Ư�������� ���� ����


	return false;

}

bool PixelCollider::ColMapSetting()
{
	// ���⼭ ���緹���� ������ ���� �˻��� �浹���� ������

	return false;
}

// ���ڰ� ���� �ʿ� ���� �ϴ�. 
bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
{
	// ���⼭ �ݸʼ����� �ϰ�, �˻� 

	if (nullptr == m_CurColMap)
	{
		MsgAssert("ColMap �� nullptr �Դϴ�.");
		return false;
	}

	// ���� �ʿ����.. 
	if (nullptr == _Object)
	{
		MsgAssert("���ڷ� ���� ������Ʈ�� nullptr �Դϴ�.");
		return false;
	}

	// üũ�� ��ġ 
	float4 CheckPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// y ������ �̵��Ѱ� 
	int UpCount = 0;
	if (m_BlackPixel == ColPixel)
	{
		// true ���� �������°���.
		while (true)
		{
			// �� - ����ߵ���
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (m_WhitePixel == ColPixel)
			{
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
				break;
			}
		}

		return true;
	}

	return false;
}

// �浹 �˻� �Լ�
bool PixelCollider::RightPixelCheck()
{
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �˻��� ��ġ�� �ȼ����� �޾ƿ´�.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
	
	// �浹 �˻�
	if (m_BlackPixel == ColPixel)
	{
		return true; // �浹 �߻�
	}

	return false; // �浹 ����
}

// �浹 �˻� �Լ� (Left �浹)
bool PixelCollider::LeftPixelCheck()
{
	/*float4 RightCheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 BottomCheckPos = Player::MainPlayer->m_DebugRender_Bottom->GetTransform()->GetWorldPosition();*/

	// ���� x��������� ���ؼ� Left ���� ����Ʈ ������ �ٲ�� �����ϱ� �׳� Right ���� �״�� �θ� ����������? 
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �˻��� ��ġ�� �ȼ����� �޾ƿ´�.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �浹 �˻�
	if (m_BlackPixel == ColPixel)
	{
		return true; // �浹 �߻�
	}

	return false; // �浹 ����
}

bool PixelCollider::TopPixelCheck()
{
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Top->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();
	
	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �������Դ��� üũ
	bool Check = false;
	// y ������ �̵��Ѱ� 
	int DownCount = 0;
	
	if (m_BlackPixel == ColPixel)
	{
		// �������� ������ �ݺ�
		while (true)
		{
			// �Ʒ��� �̵�
			++CheckY;
			++DownCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

			if (m_WhitePixel == ColPixel)
			{
				// �������� �ȼ��� �Ʒ� �ȼ��� ����̸� ��������
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0, -static_cast<float>(DownCount) });
				break;
			}
		}

		return true;
	}

	return false;
}



