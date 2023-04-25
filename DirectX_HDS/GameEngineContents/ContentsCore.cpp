#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "CTestLevel.h"
#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include "CStageLevel_01.h"
#include "CStageLevel_02.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameStart()
{
	// �������� �� ����ü���� , ������ �̸��� �־����� �ʴ´ٸ�
	// Ŭ���� �̸��� ������ �̸����� ���� ����
	GameEngineCore::CreateLevel<CTitleLevel>();
	GameEngineCore::CreateLevel<CStageLevel_01>();
	GameEngineCore::CreateLevel<CStageLevel_02>();

	GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("CTestLevel");
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{

}