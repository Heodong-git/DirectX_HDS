#include "PrecompileHeader.h"
#include "CTutorialLevel.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "CPlayManager.h"
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CMouse.h"

CTutorialLevel::CTutorialLevel()
{
}

CTutorialLevel::~CTutorialLevel()
{
}

void CTutorialLevel::Start()
{
	CKatanaZero_Level::Start();

	// 리소스로드 
	ResourcesLoad();
	// 액터로드 
	ActorLoad();
}

void CTutorialLevel::Update(float _DeltaTime)
{
}

void CTutorialLevel::LevelChangeStart()
{
}

void CTutorialLevel::LevelChangeEnd()
{
}

void CTutorialLevel::ResourcesLoad()
{
	{
		// 디렉토리 클래스생성
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("TutorialLevel");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

void CTutorialLevel::ActorLoad()
{
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CMouse> NewMouse = CreateActor<CMouse>("Mouse");
	SetMouse(NewMouse);
}
