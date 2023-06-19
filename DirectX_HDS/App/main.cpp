#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>


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
		ContentsCore::GameEnd /*{ 2300 , 0 }*/);
}

// - main 실행
// - GameEngineCore::Start 호출 ( 인자로 실행할 게임의 시작, 종료시 실행할 함수를 인자로 넣음 )
// - 코어의 Start 에서는 게임 실행 후 사용할 Level 을 생성
// - Level 에서는 게임 실행 후 해당 Level 에서 사용할 Actor 생성 ( MainCamera 는 반드시 생성한다 ) 
// - Actor 에서는 Actor 클래스가 사용할 객체들을 생성
// - Start의 모든 작업이 완료 되었다면 Loop 실행 , 레벨이 생성되지 않았다면 assert 
// - 정상적으로 생성되었다면 시간, 사운드 , 타임이벤트,  현재 레벨의 업데이트
// - 현재 레벨에서는 자신이 소유한 액터들의 업데이트를, 각 액터에서는 각 액터가 소유한 객체들을 업데이트한다.

// 이게 현재 까지의 프로젝트 구성

// 침습형 관리방식
// 스마트포인터가 레퍼런스 카운팅을 할 수 있는 부모클래스를 상속받은 클래스들만 관리하는 방식 