#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

// test
#include <GameEngineBase/GameEngineString.h>

// 라이브러리 디렉터리 설정으로 인해 lib 파일 앞쪽에 상대경로가 포함되어 있는 것이고, 아래처럼 사용가능
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)	
{
	GameEngineCore::Start(hInstance,
		ContentsCore::GameStart,
		ContentsCore::GameEnd
	);
}

// - main 실행
// - GameEngineCore::Start 호출 ( 인자로 실행할 게임의 시작, 종료시 실행할 함수를 인자로 넣음 )
// - 코어의 Start 에서는 게임 실행 후 사용할 Level 을 생성
// - Level 에서는 게임 실행 후 해당 Level 에서 사용할 Actor 생성 
// - Actor 에서는 Actor 클래스가 사용할 녀석들 생성 , 로딩완료까지 반복 
// 
