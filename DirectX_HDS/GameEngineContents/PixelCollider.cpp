#include "PrecompileHeader.h"
#include "PixelCollider.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "BaseLevel.h"
#include "Player.h"

PixelCollider* PixelCollider::PixelCol = nullptr;
std::vector<std::shared_ptr<class GameEngineTexture>> PixelCollider::m_ColMaps = std::vector<std::shared_ptr<class GameEngineTexture>>();

GameEnginePixelColor PixelCollider::g_BlackPixel = { static_cast<char>(0), static_cast<char>(0) , static_cast<char>(0) ,
										static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_WhitePixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) ,
									static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_GreenPixel = { static_cast<char>(0), static_cast<char>(255) , static_cast<char>(0) ,
									static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_ErrorPixel = { static_cast<char>(255), static_cast<char>(0) , static_cast<char>(255) ,
									static_cast<char>(255) };

PixelCollider::PixelCollider()
{
	PixelCol = this;
}

PixelCollider::~PixelCollider()
{
}

void PixelCollider::Start()
{
	if (0 == m_ColMaps.size())
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("ColMap");

		// 파일 전체로드 
		// 여기서 순서대로 저장되기 때문에 파일의 순서가 바뀌면 안된다. 
		// 이럴거면 맵이 나은거 같기도.. 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			m_ColMaps.push_back(GameEngineTexture::Load(File[i].GetFullPath()));
		}

		// 다저장하고 만약 사이즈가 0이라면 assert
		if (0 == m_ColMaps.size())
		{
			MsgAssert("충돌맵이 저장되지 않았습니다.");
			return;
		}
	}
}

bool PixelCollider::ColMapSetting()
{
	if (0 == m_ColMaps.size())
	{
		MsgAssert("ColMap이 벡터에 저장되지 않았습니다.");
		return false;
	}

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("Player 가 nullptr 입니다.");
		return false;
	}

	BaseLevel* CurLevel = Player::MainPlayer->GetReturnCastLevel();

	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return false;
	}

	LevelType CurMapName = CurLevel->GetLevelType();

	// 픽셀콜라이더에서 현재 레벨의 타입을 받아오고, 그 레벨타입에 맞는 충돌맵을 세팅해준다. 
	switch (CurMapName)
	{
	case LevelType::CLUBMAP0:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP0)];
		break;
	case LevelType::CLUBMAP1:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP1)];
		break;
	case LevelType::CLUBMAP2:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP2)];
		break;
	case LevelType::CLUBMAP3:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP3)];
		break;
	case LevelType::CLUBMAP4:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP4)];
		break;
	}

	if (nullptr == m_CurColMap)
	{
		MsgAssert("충돌맵이 nullptr 입니다. PixelCollider 클래스를 확인하세요.");
		return false;
	}
	return true;
}


GameEnginePixelColor PixelCollider::PixelCollision(const float4& _Pos)
{
	// 충돌맵 세팅
	ColMapSetting();

	// 체크할 위치
	float4 CheckPos = _Pos;

	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// 
	if (g_BlackPixel == ColPixel)
	{
		return g_BlackPixel;
	}

	// y 축으로 이동한값 
	int UpCount = 0;
	if (g_BlackPixel == ColPixel)
	{
		// true 여야 빠져나온거임.
		while (true)
		{
			// 아 - 해줘야되지
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (g_WhitePixel == ColPixel)
			{
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
				break;
			}
		}

		return g_WhitePixel;
	}

	return g_WhitePixel;
}



// 인자가 굳이 필요 없긴 하다. 
bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
{
	ColMapSetting();

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
	if (g_BlackPixel == ColPixel)
	{
		// true 여야 빠져나온거임.
		while (true)
		{
			// 아 - 해줘야되지
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (g_WhitePixel == ColPixel)
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
	// 만약 내가 왼쪽을 보고 있다면 
	ColMapSetting();

	float4 CheckPos = {};
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}
	
	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}
	
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
	if (g_BlackPixel == ColPixel)
	{
		return true; // 충돌 발생
	}

	return false; // 충돌 없음
}

bool PixelCollider::RightWallCheck(float4& _Pos)
{
	// 만약 내가 왼쪽을 보고 있다면 
	ColMapSetting();

	float4 CheckPos = _Pos;
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}

	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}

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
	if (g_BlackPixel == ColPixel)
	{
		return true; // 충돌 발생
	}

	return false; // 충돌 없음
}

// 충돌 검사 함수 (Left 충돌)
bool PixelCollider::LeftPixelCheck()
{
	ColMapSetting();

	float4 CheckPos = {};
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}

	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}
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
	if (g_BlackPixel == ColPixel)
	{
		return true; // 충돌 발생
	}

	return false; // 충돌 없음
}

bool PixelCollider::TopPixelCheck()
{
	ColMapSetting();

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
	
	if (g_BlackPixel == ColPixel)
	{
		// 빠져나올 때까지 반복
		while (true)
		{
			// 아래로 이동
			++CheckY;
			++DownCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

			if (g_WhitePixel == ColPixel)
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

