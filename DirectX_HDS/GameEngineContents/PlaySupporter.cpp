#include "PrecompileHeader.h"
#include "PlaySupporter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"
#include "PixelCollider.h"

PlaySupporter* PlaySupporter::MainSupporter = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_FailRender = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_BlackBoxRender = nullptr;
std::shared_ptr<GameEngineCollision> PlaySupporter::g_MouseCheckCollision = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_ClearRender = nullptr;

PlaySupporter::PlaySupporter()
{
	MainSupporter = this;
}

PlaySupporter::~PlaySupporter()
{
}

void PlaySupporter::Start()
{
	// 각 레벨별 카메라 범위저장
	SaveCameraRange();

	// 필요한 리소스 로드
	LoadResources();

	// 컴포넌트 세팅
	ComponentSetting();
}

void PlaySupporter::Update(float _DeltaTime)
{
	// 이것도 사실 필요한지 모르겠음 
	if (nullptr != GameEngineCore::GetCurLevel())
	{
		m_MainCamera = GameEngineCore::GetCurLevel()->GetMainCamera();
	}

	// 플레이어가 사망하면, 텍스트를 띄우고 레벨을 대기 상태로 변경한다. 
	if (true == PlayerDeathCheck())
	{
		GetReturnCastLevel()->SetState(BaseLevel::LevelState::WAIT);

		// 레벨리셋여부체크 
		LevelResetCheck();
	}

	// 맵의 범위를 벗어나게 되면 카메라는 움직이지 않음 
	// 이렇게 체크하는게 아니라 그냥 카메라 무브먼트에서 무빙까지 한번에 하는게 맞다 
	CameraMovement(_DeltaTime);
}

void PlaySupporter::Render(float _DeltaTime)
{
}

void PlaySupporter::CameraMovement(float _DeltaTime)
{
	std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel.get());

	// 만약 null 이면 return
	if (nullptr == CastLevel)
	{
		return;
	}

	// 현재 레벨의 타입도 가져와
	LevelType CurLevelType = CastLevel->GetLevelType();

	if (LevelType::NONE == CurLevelType)
	{
		MsgAssert("레벨의 타입이 세팅되지 않았습니다.");
		return;
	}

	// 픽셀컬라이더의 충돌맵을 가져오고, 어차피 실제 사용하는 맵과 크기는 동일
	std::shared_ptr<GameEngineTexture> CurMap = PixelCollider::PixelCol->GetColMap();

	if (nullptr == CurMap)
	{
		// MsgAssert("현재 맵이 nullptr 입니다.");
		return;
	}

	// 맵의 크기를 받아온다.
	float4 MapSize = CurMap->GetScale();

	// 현재 레벨 타입에 따라서 카메라 적용범위 계산
	switch (CurLevelType)
	{
	case LevelType::CLUBMAP0:
	{
		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(static_cast<int>(LevelType::CLUBMAP0));
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
		Dir.y = 0.0f;
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// 이동할 위치가 카메라의 이동가능범위를 벗어나면 이동하지 않음
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			Dir.x = 0.0f;
		}

		m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
		return;
	}
	break;
	case LevelType::CLUBMAP1:
	{
		// 카메라 이동 X 
		return;
	}
	break;
	case LevelType::CLUBMAP2:
	{
		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(static_cast<int>(LevelType::CLUBMAP2));
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("맵 범위 저장 벡터가 비어있습니다.");
		}

		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];
		float4 LeftBottom = Vector[2];
		float4 RightBottom = Vector[3];

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

		// 이동방향 
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// 범위체크 
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			Dir.x = 0.0f;
		}

		if (NextPos.y < LeftBottom.y || NextPos.y > RightTop.y)
		{
			Dir.y = 0.0f;
		}

		// 만약 플레이어가 벽타기 상태라면 x 축은 움직이지 않음
		if (PlayerState::RIGHTWALL == Player::MainPlayer->GetCurState() ||
			PlayerState::LEFTWALL == Player::MainPlayer->GetCurState())
		{
			Dir.x = 0.0f;
		}

		// 범위체크후 카메라 이동을 여기서 하고 카메라무브먼트 함수는 삭제 후 이 함수 이름 변경
		m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
		// 이동이 가능하다면 false 반환, 
		return;
	}
	break;
	case LevelType::CLUBMAP3:
	{
		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(static_cast<int>(LevelType::CLUBMAP3));
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("맵 범위 저장 벡터가 비어있습니다.");
		}

		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];
		float4 LeftBottom = Vector[2];
		float4 RightBottom = Vector[3];

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

		// 이동방향 
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// 범위체크 
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			Dir.x = 0.0f;
		}

		if (NextPos.y < LeftBottom.y || NextPos.y > RightTop.y)
		{
			Dir.y = 0.0f;
		}

		// 만약 플레이어가 벽타기 상태라면 x 축은 움직이지 않음
		if (PlayerState::RIGHTWALL == Player::MainPlayer->GetCurState() ||
			PlayerState::LEFTWALL == Player::MainPlayer->GetCurState())
		{
			Dir.x = 0.0f;
		}

		// 범위체크후 카메라 이동을 여기서 하고 카메라무브먼트 함수는 삭제 후 이 함수 이름 변경
		m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
		// 이동이 가능하다면 false 반환, 
		return;
	}
		break;
	case LevelType::CLUBMAP4:
	{
		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(static_cast<int>(LevelType::CLUBMAP4));
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("맵 범위 저장 벡터가 비어있습니다.");
		}

		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];
		float4 LeftBottom = Vector[2];
		float4 RightBottom = Vector[3];

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

		// 이동방향 
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// 범위체크 
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			Dir.x = 0.0f;
		}

		if (NextPos.y < LeftBottom.y || NextPos.y > RightTop.y)
		{
			Dir.y = 0.0f;
		}

		// 만약 플레이어가 벽타기 상태라면 x 축은 움직이지 않음
		if (PlayerState::RIGHTWALL == Player::MainPlayer->GetCurState() ||
			PlayerState::LEFTWALL == Player::MainPlayer->GetCurState())
		{
			Dir.x = 0.0f;
		}

		// 범위체크후 카메라 이동을 여기서 하고 카메라무브먼트 함수는 삭제 후 이 함수 이름 변경
		m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
		// 이동이 가능하다면 false 반환, 
		return;
	}
		break;
	case LevelType::NONE:
		break;
	default:
		break;
	}
}

bool PlaySupporter::PlayerDeathCheck()
{
	if (nullptr == Player::MainPlayer)
	{
		return false;
	}

	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return true;
	}

	return false;
}

void PlaySupporter::LevelResetCheck()
{
	g_BlackBoxRender->On();
	g_FailRender->On();

	if (nullptr == g_MouseCheckCollision)
	{
		MsgAssert("마우스클릭 체크용 충돌체가 nullptr입니다.");
		return;
	}

	// 만약 이 충돌체가 마우스 클릭 충돌체를 가진녀석과 충돌하게 되면 레벨의 리셋 호출 
	g_MouseCheckCollision->GetTransform()->SetLocalPosition(m_MainCamera->GetTransform()->GetLocalPosition());

	std::shared_ptr<GameEngineCollision> CursorCol = g_MouseCheckCollision->Collision(ColOrder::CURSOR, ColType::AABBBOX2D, ColType::AABBBOX2D);

	// 뭔가가 들어왔다는건 충돌했다는거고 
	// 그럼 충돌한 액터를 데스시키고 레벨리셋 호출 
	if (nullptr != CursorCol)
	{
		CursorCol->Off();
		g_BlackBoxRender->Off();
		g_FailRender->Off();
		// 리셋하고 
		GetReturnCastLevel()->LevelReset();
	}
}

void PlaySupporter::ComponentSetting()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	g_BlackBoxRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_BlackBoxRender->SetTexture("background_black.png");
	g_BlackBoxRender->GetTransform()->SetLocalScale({ ScreenSize.x / 3.0f , ScreenSize.y / 4.0f });
	g_BlackBoxRender->GetTransform()->SetLocalPosition({ 50.0f , 0.0f });
	g_BlackBoxRender->ColorOptionValue.MulColor.a = 0.4f;
	g_BlackBoxRender->Off();

	g_FailRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_FailRender->SetScaleToTexture("restart.png");
	g_FailRender->GetTransform()->SetLocalPosition({ 60.0f , 0.0f });
	g_FailRender->Off();

	g_ClearRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_ClearRender->SetTexture("youcandothis.png");
	g_ClearRender->GetTransform()->SetLocalScale(ScreenSize);
	g_ClearRender->Off();

	g_MouseCheckCollision = CreateComponent <GameEngineCollision>(ColOrder::CHECKBOX);
	g_MouseCheckCollision->GetTransform()->SetLocalScale(ScreenSize);
}

// 생각해보니 레프트탑 라이트바텀만 있으면 되는거아닌가 ? 
void PlaySupporter::SaveCameraRange()
{
	{
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -360.0f , 34.0f };
		float4 RightTop = { 307.0f , 34.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP0), Ranges));
	}

	{
		// 1번맵은 넣어두기만. 실제로 스위치문에서 적용 X 
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { 0.0f , 0.0f };
		float4 RightTop = { 0.0f, 0.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP1), Ranges));
	}

	{
		// 확인해서 추가 
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -335.0f, 84.18f }; 
		float4 RightTop = { 329.0f , 84.18f };
		float4 LeftBottom = { -355.0f , -250.f };
		float4 RightBottom = { 326.0f , -250.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		Ranges.push_back(LeftBottom);
		Ranges.push_back(RightBottom);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP2), Ranges));
	}
	{
		// 확인해서 추가 
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -135.52f, 356.0f };
		float4 RightTop = { 105.71f, 356.0f };
		float4 LeftBottom = { -135.52f , -353.06f };
		float4 RightBottom = { 105.71f, -353.06f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		Ranges.push_back(LeftBottom);
		Ranges.push_back(RightBottom);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP3), Ranges));
	}
	{
		// 확인해서 추가 
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -638.82f, 389.24f };
		float4 RightTop = { 634.63f, 389.24f };
		float4 LeftBottom = { -638.82f , -384.76f };
		float4 RightBottom = { 634.63f, -384.76f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		Ranges.push_back(LeftBottom);
		Ranges.push_back(RightBottom);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP4), Ranges));
	}
}

void PlaySupporter::LoadResources()
{
	if (nullptr == g_BlackBoxRender)
	{
		if (nullptr == GameEngineTexture::Find("restart.png"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("katanazero_resources");
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("youcandothis");

			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });

			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
	}
}

void PlaySupporter::Reset()
{
}

