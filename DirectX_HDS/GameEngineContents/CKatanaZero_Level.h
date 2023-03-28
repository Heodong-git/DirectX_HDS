#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 컨텐츠 구성시 레벨에서 사용할 필요한 기능 구현 예정
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
