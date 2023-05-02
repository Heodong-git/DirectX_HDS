#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CCursor.h"
#include "CBackGround.h"
#include "CTitleManager.h"
#include "CPlayManager.h"
#include "CRecordingManager.h"

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
	// 리소스, 액터로드 
	ResourcesLoad();
	ActorLoad();
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
	// 매니저. static이 맞는거같은데ㅋㅋㅋ
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	m_RecordingManager = CreateActor<CRecordingManager>("RecordingManager");

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>("Mouse");
	SetCursor(NewCursor);
}


void CTestLevel::LevelChangeStart()
{
}

void CTestLevel::LevelChangeEnd()
{
	
}

