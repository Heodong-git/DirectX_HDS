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
	// �� ���������� �ݵ�� �����Ҷ� ����Ÿ���� �������ش�. 
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	// ī�޶� ��� ��ġ���� �ٶ� ������
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();

	CKatanaZero_Level::Start();
}

