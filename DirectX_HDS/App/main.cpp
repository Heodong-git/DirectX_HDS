#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>

// 라이브러리 디렉터리 설정으로 인해 lib 파일 앞쪽에 상대경로가 포함되어 있는 것이고
// 그로 인해 아래와 같이 사용이 가능하다. 
#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//GameEngineCore::Start(hInstance, );
}

// 3월 17일 해야할일 목록
// 1. 코드 읽으면서 주석 다시 하나하나 달면서 체크 
// 2. 파일입출력, Rtti , 한번씩 확인해보면서 공부.