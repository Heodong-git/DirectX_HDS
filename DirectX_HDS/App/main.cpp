#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>

// ���̺귯�� ���͸� �������� ���� lib ���� ���ʿ� ����ΰ� ���ԵǾ� �ִ� ���̰�
// �׷� ���� �Ʒ��� ���� ����� �����ϴ�. 
#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//GameEngineCore::Start(hInstance, );
}

// 3�� 17�� �ؾ����� ���
// 1. �ڵ� �����鼭 �ּ� �ٽ� �ϳ��ϳ� �޸鼭 üũ 
// 2. ���������, Rtti , �ѹ��� Ȯ���غ��鼭 ����.