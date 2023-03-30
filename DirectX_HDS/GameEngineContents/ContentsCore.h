#pragma once

class ContentsCore
{
public:
	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static void GameStart();
	static void GameEnd();

protected:

private:
};

// 일단 내 게임의 액터, 레벨은 내 게임전용 액터레벨클래스를 만들고 
// 그 클래스가 엔진의 액터,레벨 클래스를 상속받고 게임에서 필요한 기능들을 만들어내고
// 그 게임전용 클래스를 상속받는 액터와 레벨들을 찍어낸다. 