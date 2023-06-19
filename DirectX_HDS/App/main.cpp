#include "PrecompileHeader.h"
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
		ContentsCore::GameEnd /*{ 2300 , 0 }*/);
}

// - main ����
// - GameEngineCore::Start ȣ�� ( ���ڷ� ������ ������ ����, ����� ������ �Լ��� ���ڷ� ���� )
// - �ھ��� Start ������ ���� ���� �� ����� Level �� ����
// - Level ������ ���� ���� �� �ش� Level ���� ����� Actor ���� ( MainCamera �� �ݵ�� �����Ѵ� ) 
// - Actor ������ Actor Ŭ������ ����� ��ü���� ����
// - Start�� ��� �۾��� �Ϸ� �Ǿ��ٸ� Loop ���� , ������ �������� �ʾҴٸ� assert 
// - ���������� �����Ǿ��ٸ� �ð�, ���� , Ÿ���̺�Ʈ,  ���� ������ ������Ʈ
// - ���� ���������� �ڽ��� ������ ���͵��� ������Ʈ��, �� ���Ϳ����� �� ���Ͱ� ������ ��ü���� ������Ʈ�Ѵ�.

// �̰� ���� ������ ������Ʈ ����

// ħ���� �������
// ����Ʈ�����Ͱ� ���۷��� ī������ �� �� �ִ� �θ�Ŭ������ ��ӹ��� Ŭ�����鸸 �����ϴ� ��� 