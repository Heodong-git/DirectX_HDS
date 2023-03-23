#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

// test
#include <GameEngineBase/GameEngineString.h>

// ���̺귯�� ���͸� �������� ���� lib ���� ���ʿ� ����ΰ� ���ԵǾ� �ִ� ���̰�, �Ʒ�ó�� ��밡��
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

// - main ����
// - GameEngineCore::Start ȣ�� ( ���ڷ� ������ ������ ����, ����� ������ �Լ��� ���ڷ� ���� )
// - �ھ��� Start ������ ���� ���� �� ����� Level �� ����
// - Level ������ ���� ���� �� �ش� Level ���� ����� Actor ���� 
// - Actor ������ Actor Ŭ������ ����� �༮�� ���� , �ε��Ϸ���� �ݺ� 
// 
