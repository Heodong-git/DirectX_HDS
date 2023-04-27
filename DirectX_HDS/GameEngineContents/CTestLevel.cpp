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
	// 해당 레벨에서 사용할 리소스를 로드한다. 
	// 해당 레벨이 종료되면 로드한 리소스를 모두 삭제한다 
	// 파일을 로드 할 경우 동일한 이름으로는 저장할 수 없음.
	{
		// 디렉토리 클래스생성
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("TestLevel");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// 각 레벨에서는 반드시 시작할때 투영타입을 세팅해준다. 
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	// 카메라가 어느 위치에서 바라볼 것인지
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CMouse> NewMouse = CreateActor<CMouse>("Mouse");
	SetMouse(NewMouse);
}

void CTestLevel::Update(float _DeltaTime)
{
	// 어 
	std::shared_ptr<CMouse> Mouse = GetMouse();
	if (nullptr != Mouse)
	{
		m_CurMouseLocalPos = Mouse->GetTransform()->GetLocalPosition();
	}
 
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTestLevel::LevelChangeStart()
{
	int a = 0;
}

void CTestLevel::LevelChangeEnd()
{
	int a = 0;
}

