#include "PrecompileHeader.h"
#include "PixelCollider.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

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

bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
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

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �������Դ��� üũ
	bool Check = false;
	// y ������ �̵��Ѱ� 
	int UpCount = 0;
	if (m_BlackPixel == ColPixel)
	{
		// true ���� �������°���.
		while (false == Check)
		{
			// �� - ����ߵ���
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (m_WhitePixel == ColPixel)
			{
				Check = true;
				_Object->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
			}
		}

		return true;
	}

	return false;
}
