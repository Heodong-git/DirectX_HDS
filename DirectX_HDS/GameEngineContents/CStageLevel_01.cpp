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
	// ���� shared_ptr �� �������� 
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("CPlayer");
}
