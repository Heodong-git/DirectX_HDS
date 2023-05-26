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
		// 이게 맞나.. 일단 0번맵 범위
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -360.0f , 34.0f };
		float4 RightTop = { 307.0f , 34.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);

		m_MapRanges.insert(make_pair(0, Ranges));
	}

	{
		// 1번맵은 범위 필요없으니까 건너뛰고 키값을 2부터 시작
		
	}
}

void CameraMovement::Update(float _DeltaTime)
{
	if (nullptr != GameEngineCore::GetCurLevel())
	{
		m_MainCamera = GameEngineCore::GetCurLevel()->GetMainCamera();
	}

	// 맵의 범위를 벗어나게 되면 카메라는 움직이지 않음 
	if (true == RangeOverCheck(_DeltaTime))
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
	float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

	float4 Dir = PlayerPos - CameraPos;
	Dir.y = 0.0f;
	Dir.Normalize();
	m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
	
}

// 카메라가 맵의 범위를 넘어서는지 
// 당연히 현재 레벨에 진입하고, 레벨이 모두 세팅되어있다는 가정하에. 
// 카메라가 
bool CameraMovement::RangeOverCheck(float _DeltaTime)
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
	// 일단 되긴하는데 정리가 좀 필요하다. 
	switch (CurLevelType)
	{
	case LevelType::CLUBMAP0:
	{
		// 이부분이 뭔가 맘에 안들어.. 
		if (nullptr == m_MainCamera)
		{
			return true;
		}

		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(0);
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("맵 범위 저장 벡터가 비어있습니다.");
		}

		// 그게아니라면 맵의 범위를 받아오고 
		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];

		// 카메라가 이동했을 때의 카메라의 위치가 범위를 벗어난다면 이동하지 않도록 처리
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// 이동할 위치가 카메라의 이동가능범위를 벗어나면 이동하지 않음
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			return true;
		}

		// 이동이 가능하다면 false 반환, 
		return false;
	}
		break;
	case LevelType::CLUBMAP1:
	{
		// 얘는 그냥 카메라 안에 다들어와서 노상관 아무것도 없어도 될듯
		return false;
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
