#include "PrecompileHeader.h"
#include "CStageLevel_01.h"
#include "CPlayer.h"

CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Start()
{
	// 이제 shared_ptr 에 적응하자 
	//std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("CPlayer");
}

void CStageLevel_01::ResourcesLoad()
{
}

void CStageLevel_01::ActorLoad()
{
}
