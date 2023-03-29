#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"



CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Loading()
{
	GetMainCamera()->GetTransform().SetLocalPosition({ 0 , 0 , -1000 });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>();
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
}
