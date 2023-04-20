#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
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
	// 임시 파일로드
	// 파일을 로드 할 경우 동일한 이름으로는 저장할 수 없음.
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("katanazero_resources");
		NewDir.Move("katanazero_resources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}


	// 각 레벨에서는 반드시 시작할때 투영타입을 세팅해준다. 
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	// 카메라가 어느 위치에서 바라볼 것인지
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();

	CKatanaZero_Level::Start();
}

