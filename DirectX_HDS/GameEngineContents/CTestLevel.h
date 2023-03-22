#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class CTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CTestLevel();
	~CTestLevel();

	// delete Function
	CTestLevel(const CTestLevel& _Other) = delete;
	CTestLevel(CTestLevel&& _Other) noexcept = delete;
	CTestLevel& operator=(const CTestLevel& _Other) = delete;
	CTestLevel& operator=(CTestLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;

private:

};
