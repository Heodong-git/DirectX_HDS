#include "TitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{
	// ������ �� �갡 ����, Ÿ��Ʋ������ �����Ǹ� ������ �� �༮���� ���⼭ �����. 
	// TimeEvent.AddEvent(5.0f, std::bind(&TitleLevel::TestMsg, this), true);

	// ���� ����
	// �̸��� ���� �Լ��� ������ ����.
	std::function<void()> Test = []
	{
		MsgTextBox("�̺�Ʈ ���� �۵�");
	};

	TimeEvent.AddEvent(1.0f, Test, true);
}

