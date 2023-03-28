#pragma once
#include "CKatanaZero_Level.h"

// Ό³Έν :
class CTestLevel : public CKatanaZero_Level
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
