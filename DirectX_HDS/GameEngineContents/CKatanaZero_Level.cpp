#include "PrecompileHeader.h"
#include "CKatanaZero_Level.h"
#include "CCursor.h"
#include <GameEngineCore/GameEngineCamera.h>


CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Start()
{
	CameraSetting();
}

void CKatanaZero_Level::Update(float _DeltaTime)
{
	// 현재 커서가 nullptr 이 아니라면 
	// 받아와서 로컬포지션을 저장
	std::shared_ptr<CCursor> Cursor = GetCursor();
	if (nullptr != Cursor)
	{
		m_CurMouseLocalPos = Cursor->GetTransform()->GetLocalPosition();
	}

	// GameEngineLevel 의 update 를 virtual 로 변경해준다면 삭제
	GameEngineLevel::Update(_DeltaTime);

}

void CKatanaZero_Level::LevelChangeStart()
{
	
}

void CKatanaZero_Level::CameraSetting()
{
	// 카메라세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });
}
