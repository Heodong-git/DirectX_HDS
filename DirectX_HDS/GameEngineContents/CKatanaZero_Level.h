#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ������ ������ �������� ����� �ʿ��� ��� ���� ����
class CKatanaZero_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	CKatanaZero_Level();
	~CKatanaZero_Level();

	// delete Function
	CKatanaZero_Level(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level(CKatanaZero_Level&& _Other) noexcept = delete;
	CKatanaZero_Level& operator=(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level& operator=(CKatanaZero_Level&& _Other) noexcept = delete;

protected:

private:

};

// īŸ�����δ� ������������ ����ð��� ������ �ְ�.
// ��. ������ ������Ʈ�� ������ ���� ����ϴ� ��ɰ� �װ� �����ϴ� ���, ����� ������ �ε��ϴ� ���