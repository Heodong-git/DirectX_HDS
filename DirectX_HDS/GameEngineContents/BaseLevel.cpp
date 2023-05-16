#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineCamera.h>


BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	CameraSetting();
}

void BaseLevel::Update(float _DeltaTime)
{
	// 현재 커서가 nullptr 이 아니라면 
	// 받아와서 로컬포지션을 저장
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	// GameEngineLevel 의 update 를 virtual 로 변경해준다면 삭제
	GameEngineLevel::Update(_DeltaTime);
}

void BaseLevel::LevelChangeStart()
{
	
}

void BaseLevel::CameraSetting()
{
	// 카메라세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}
