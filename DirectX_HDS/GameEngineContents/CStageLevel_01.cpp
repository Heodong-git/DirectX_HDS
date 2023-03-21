#include "CStageLevel_01.h"
#include "CPlayer.h"

CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Loading()
{
	// 이제 shared_ptr 에 적응하자 
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("CPlayer");
}
