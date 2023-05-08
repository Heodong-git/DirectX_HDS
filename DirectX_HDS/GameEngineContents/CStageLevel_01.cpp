#include "PrecompileHeader.h"
#include "CStageLevel_01.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include "CStageEditer.h"

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
	//if (nullptr == m_GUI)
	//{
	//	GameEngineGUI::GUIWindowCreate<CStageEditer>("Stage_Editer");
	//	m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	//}
	//
	//// 그래도 nullptr 이면 assert 
	//if (nullptr == m_GUI)
	//{
	//	MsgAssert("GUI Window가 nullptr 입니다.")
	//	return;
	//}
	m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();
}

void CStageLevel_01::LevelChangeEnd()
{
	m_GUI->Off();
}

void CStageLevel_01::ResourcesLoad()
{
}

void CStageLevel_01::ActorLoad()
{
	
}
