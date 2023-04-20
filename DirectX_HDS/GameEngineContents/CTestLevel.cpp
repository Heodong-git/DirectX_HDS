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
	// 카메라는 부모의 생성자에서 무조건 만들어지기 때문에
	// 여기서 위치를 세팅해준다. 
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();

	CKatanaZero_Level::Start();
}

