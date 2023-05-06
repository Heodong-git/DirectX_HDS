#include "PrecompileHeader.h"
#include "CStageLevel_01.h"

#include "CKatanaZero_Level.h"
#include "CPlayer.h"
#include "CCursor.h"
#include "CBattery.h"
#include "CInven.h"
#include "CPlayManager.h"

CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Start()
{
	CKatanaZero_Level::Start();
	ResourcesLoad();
	ActorLoad();
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
