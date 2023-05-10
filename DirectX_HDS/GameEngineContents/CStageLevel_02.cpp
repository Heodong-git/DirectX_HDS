#include "PrecompileHeader.h"
#include "CStageLevel_02.h"

#include <GameEnginePlatform/GameEngineInput.h>

CStageLevel_02::CStageLevel_02()
{
}

CStageLevel_02::~CStageLevel_02()
{
}

void CStageLevel_02::Start()
{
	CKatanaZero_Level::Start();

	if (false == GameEngineInput::IsKey("Stage02_ChangeLevel_Title"))
	{
		GameEngineInput::CreateKey("Stage02_ChangeLevel_Title", VK_F1);
	}

	ResourcesLoad();
	ActorLoad();
}

void CStageLevel_02::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
}

void CStageLevel_02::LevelChangeStart()
{
}

void CStageLevel_02::LevelChangeEnd()
{
}

void CStageLevel_02::ResourcesLoad()
{
}

void CStageLevel_02::ActorLoad()
{
}
