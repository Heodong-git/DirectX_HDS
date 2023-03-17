#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameStart()
{
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{

}