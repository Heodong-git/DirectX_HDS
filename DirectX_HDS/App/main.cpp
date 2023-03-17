#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

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







// 3�� 17�� �ؾ����� ���
// 1. �ڵ� �����鼭 �ּ� �ٽ� �ϳ��ϳ� �޸鼭 üũ 
// 2. ���������, Rtti <--- typeinfo , �ѹ��� Ȯ���غ��鼭 ����.
// �Ϸ� 