#include "CTestLevel.h"
#include "CPlayer.h"


CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Loading()
{
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("CPlayer");
}
