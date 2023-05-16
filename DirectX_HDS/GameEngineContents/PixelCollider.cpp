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

// 인자가 굳이 필요 없긴 하다. 
bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
{
	// 여기서 콜맵세팅을 하고, 검사 

	if (nullptr == m_CurColMap)
	{
		MsgAssert("ColMap 이 nullptr 입니다.");
		return false;
	}

	// 굳이 필요없네.. 
	if (nullptr == _Object)
	{
		MsgAssert("인자로 들어온 오브젝트가 nullptr 입니다.");
		return false;
	}

	// 체크할 위치 
	float4 CheckPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	// 충돌맵의 플레이어와 겹치는 위치의 색상을 받아온다. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// y 축으로 이동한값 
	int UpCount = 0;
	if (m_BlackPixel == ColPixel)
	{
		// true 여야 빠져나온거임.
		while (true)
		{
			// 아 - 해줘야되지
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

// 충돌 검사 함수
bool PixelCollider::RightPixelCheck()
{
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// 픽셀 크기 계산
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// 충돌 위치 계산
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// 현재 맵의 범위에서 벗어날 경우 충돌로 간주
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // 충돌 발생 (맵 범위를 벗어남)
	}

	// 검사할 위치의 픽셀값을 받아온다.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
	
	// 충돌 검사
	if (m_BlackPixel == ColPixel)
	{
		return true; // 충돌 발생
	}

	return false; // 충돌 없음
}

// 충돌 검사 함수 (Left 충돌)
bool PixelCollider::LeftPixelCheck()
{
	/*float4 RightCheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 BottomCheckPos = Player::MainPlayer->m_DebugRender_Bottom->GetTransform()->GetWorldPosition();*/

	// 지금 x축반전으로 인해서 Left 값이 라이트 값으로 바뀌고 있으니까 그냥 Right 값을 그대로 두면 되지않을까? 
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// 픽셀 크기 계산
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// 충돌 위치 계산
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// 현재 맵의 범위에서 벗어날 경우 충돌로 간주
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // 충돌 발생 (맵 범위를 벗어남)
	}

	// 검사할 위치의 픽셀값을 받아온다.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// 충돌 검사
	if (m_BlackPixel == ColPixel)
	{
		return true; // 충돌 발생
	}

	return false; // 충돌 없음
}

bool PixelCollider::TopPixelCheck()
{
	float4 CheckPos = Player::MainPlayer->m_DebugRender_Top->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();
	
	// 픽셀 크기 계산
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// 충돌 위치 계산
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// 현재 맵의 범위에서 벗어날 경우 충돌로 간주
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // 충돌 발생 (맵 범위를 벗어남)
	}

	// 충돌맵의 플레이어와 겹치는 위치의 색상을 받아온다. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// 빠져나왔는지 체크
	bool Check = false;
	// y 축으로 이동한값 
	int DownCount = 0;
	
	if (m_BlackPixel == ColPixel)
	{
		// 빠져나올 때까지 반복
		while (true)
		{
			// 아래로 이동
			++CheckY;
			++DownCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

			if (m_WhitePixel == ColPixel)
			{
				// 빠져나온 픽셀의 아래 픽셀이 흰색이면 빠져나옴
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0, -static_cast<float>(DownCount) });
				break;
			}
		}

		return true;
	}

	return false;
}



