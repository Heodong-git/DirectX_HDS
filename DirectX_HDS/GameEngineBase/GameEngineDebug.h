#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// 프로젝트에 필요한 디버그 기능들을 모아두고 사용하기 위해서 클래스 제작
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();
	static void LeakPointBreak(int _Point);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};

// 해당 매크로 사용시에는 에러가 발생한 부분에 메세지를 띄워서
// 어떠한 사유로 인해 오류가 발생되었는지 알게 해준다.
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);