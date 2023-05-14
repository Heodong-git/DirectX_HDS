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

bool PixelCollider::PixelCollision(GameEngineTransform* _Transform)
{
	if (nullptr == m_CurColMap)
	{
		MsgAssert("ColMap 이 nullptr 입니다.");
		return false;
	}
	
	if (nullptr == _Transform)
	{
		MsgAssert("트랜스폼이 nullptr 입니다.");
		return false;
	}

	float4 CheckPos = _Transform->GetLocalPosition();
	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	


	// 검정색
	GameEnginePixelColor CheckPixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) , 
									    static_cast<char>(255) };

	GameEnginePixelColor ColMapPixel = m_CurColMap->GetPixel(static_cast<int>(149), static_cast<int>(160));

	return false;

}
