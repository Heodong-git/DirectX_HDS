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
		MsgAssert("ColMap 이 nullptr 입니다.");
		return false;
	}
	
	if (nullptr == _Object)
	{
		MsgAssert("인자로 들어온 오브젝트가 nullptr 입니다.");
		return false;
	}

	float4 CheckPos = _Object->GetTransform()->GetLocalPosition();
	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	float CheckX = CheckPos.x + WidthHalf;
	float CheckY = HeightHalf - CheckPos.y;

	// 충돌맵의 플레이어와 겹치는 위치의 색상을 받아온다. 
	GameEnginePixelColor ColMapPixel = m_CurColMap->GetPixel(static_cast<int>(CheckX), static_cast<int>(CheckY));

	// 특정색상일 때의 구분
	

	return false;

}

bool PixelCollider::ColMapSetting()
{
	// 여기서 현재레벨의 구역에 따라서 검사할 충돌맵을 변경함

	return false;
}

bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
{
	if (nullptr == m_CurColMap)
	{
		MsgAssert("ColMap 이 nullptr 입니다.");
		return false;
	}

	if (nullptr == _Object)
	{
		MsgAssert("인자로 들어온 오브젝트가 nullptr 입니다.");
		return false;
	}

	float4 CheckPos = _Object->GetTransform()->GetLocalPosition();
	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	// 충돌맵의 플레이어와 겹치는 위치의 색상을 받아온다. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// 빠져나왔는지 체크
	bool Check = false;
	// y 축으로 이동한값 
	int UpCount = 0;
	if (m_BlackPixel == ColPixel)
	{
		// true 여야 빠져나온거임.
		while (false == Check)
		{
			// 아 - 해줘야되지
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (m_WhitePixel == ColPixel)
			{
				Check = true;
				_Object->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
			}
		}

		// 빠져나왔을 때 빠져나온 픽셀위치의 아랫 픽셀이 검은색이라면 현재 땅에 위치한것
	/*	float4 Pos = _Object->GetTransform()->GetLocalPosition();
		float4 GroundPos = { Pos.x , Pos.y - 1.0f };
		GameEnginePixelColor GroundPixel = m_CurColMap->GetPixel(static_cast<int>(GroundPos.x), static_cast<int>(GroundPos.y));
		
		if (m_BlackPixel == GroundPixel)
		{
			return true;
		}*/

		return true;
	}

	return false;
}
