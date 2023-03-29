#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CKatanaZero_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	CKatanaZero_Actor();
	~CKatanaZero_Actor();

	// delete Function
	CKatanaZero_Actor(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor(CKatanaZero_Actor&& _Other) noexcept = delete;
	CKatanaZero_Actor& operator=(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor& operator=(CKatanaZero_Actor&& _Other) noexcept = delete;

protected:

private:

};
