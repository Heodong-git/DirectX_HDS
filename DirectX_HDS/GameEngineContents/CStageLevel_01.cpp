#include "PrecompileHeader.h"
#include "CStageLevel_01.h"
#include "CPlayer.h"
#include "CKatanaZero_Level.h"

CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Start()
{
	CKatanaZero_Level::Start();
	// ���� shared_ptr �� �������� 
	//std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("CPlayer");
}

void CStageLevel_01::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
}

void CStageLevel_01::LevelChangeStart()
{
}

void CStageLevel_01::LevelChangeEnd()
{
}

void CStageLevel_01::ResourcesLoad()
{
}

void CStageLevel_01::ActorLoad()
{
}
