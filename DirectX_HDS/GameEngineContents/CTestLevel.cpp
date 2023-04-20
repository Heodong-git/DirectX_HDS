#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include "PrecompileHeader.h"
#include <GameEngineCore/GameEngineCamera.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"


CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Start()
{
	// 각 레벨에서는 반드시 시작할때 투영타입을 세팅해준다. 
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	// 카메라가 어느 위치에서 바라볼 것인지
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();

	CKatanaZero_Level::Start();
}

