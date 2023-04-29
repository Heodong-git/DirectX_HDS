#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CMouse.h"
#include "CBackGround.h"
#include "CTitleManager.h"
#include "CPlayManager.h"

// test
#include <GameEngineCore/GameEngineVideo.h>


CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Start()
{
	CKatanaZero_Level::Start();

	// 해당 레벨에서 사용할 리소스를 로드한다. 
	// 해당 레벨이 종료되면 로드한 리소스를 모두 삭제한다 
	// 파일을 로드 할 경우 동일한 이름으로는 저장할 수 없음.
	{
		//// 디렉토리 클래스생성
		//GameEngineDirectory NewDir;
		//// 원하는 폴더를 가진 디렉터리로 이동
		//NewDir.MoveParentToDirectory("katanazero_resources");
		//// 그 폴더로 이동
		//NewDir.Move("katanazero_resources");
		//NewDir.Move("Texture");
		//NewDir.Move("TestLevel");

		//// 파일 전체로드 
		//std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		//for (size_t i = 0; i < File.size(); i++)
		//{
		//	GameEngineTexture::Load(File[i].GetFullPath());
		//}
	}

	// 리소스, 액터로드 
	ResourcesLoad();
	ActorLoad();

	/*{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("katanazero_resources");
		NewDir.Move("katanazero_resources");
		NewDir.Move("TestMovie");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".avi", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineVideo::Load(File[i].GetFullPath());
		}
	}*/
}

void CTestLevel::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTestLevel::ResourcesLoad()
{
}

void CTestLevel::ActorLoad()
{
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CMouse> NewMouse = CreateActor<CMouse>("Mouse");
	SetMouse(NewMouse);
}


void CTestLevel::LevelChangeStart()
{
}

void CTestLevel::LevelChangeEnd()
{
	
}

