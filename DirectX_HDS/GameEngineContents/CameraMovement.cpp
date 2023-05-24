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
	// 생성하면 현재 레벨의 카메라를 받아온다.. 음 ㅇㅁㄴㅇㄹㄴㅁㅇㄹ
}

void CameraMovement::Update(float _DeltaTime)
{
	// 맵의 범위를 벗어나게 되면 카메라는 움직이지 않음 
	if (true == RangeOverCheck())
	{
		return;
	}

	Move(_DeltaTime);
}

void CameraMovement::Render(float _DeltaTime)
{
}

// 플레이어를 받아와서 움직일거. 
void CameraMovement::Move(float _DeltaTime)
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("플레이어가 nullptr 입니다.");
		return;
	}

	// 카메라 범위 안일 경우
	// 카메라는 플레이어의 위치를 받아와서 그 방향으로 이동 하기전에 범위체크 
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
}

// 카메라가 맵의 범위를 넘어서는지 
// 당연히 현재 레벨에 진입하고, 레벨이 모두 세팅되어있다는 가정하에. 
// 카메라가 
bool CameraMovement::RangeOverCheck()
{
	// 맵가져와
	std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel.get());

	// 만약 null 이면 return
	if (nullptr == CastLevel)
	{
		return true;
	}

	// 현재 레벨의 타입도 가져와
	LevelType CurLevelType = CastLevel->GetLevelType();

	if (LevelType::NONE == CurLevelType)
	{
		MsgAssert("레벨의 타입이 세팅되지 않았습니다.");
		return true;
	}

	// 픽셀컬라이더의 충돌맵을 가져오고
	std::shared_ptr<GameEngineTexture> CurMap = PixelCollider::PixelCol->GetColMap();

	if (nullptr == CurMap)
	{
		// MsgAssert("현재 맵이 nullptr 입니다.");
		return true;
	}

	// 맵이 nullptr이 아닐 경우 맵의 크기를 받아오고 ... 여기서.. 
	float4 MapSize = CurMap->GetScale();

	// 현재 맵 타입에 따라서 범위를 전부 다르게 계산 
	// 어차피 이동할때만 하면되니까 ㅇㅇ 
	// 여기서 어떻게 할거니 ㅎㅎ 
	// 맵에따라서 들어오게 까지 완성
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
