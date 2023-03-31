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
	// ī�޶�� �θ��� �����ڿ��� ������ ��������� ������
	// ���⼭ ��ġ�� �������ش�. 
	GetMainCamera()->GetTransform().SetLocalPosition({ 0 , 0 , -1000.0f });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>();
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
}
