#pragma once

// Ό³Έν :
class CStateMachine
{
public:
	// constrcuter destructer
	CStateMachine();
	~CStateMachine();

	// delete Function
	CStateMachine(const CStateMachine& _Other) = delete;
	CStateMachine(CStateMachine&& _Other) noexcept = delete;
	CStateMachine& operator=(const CStateMachine& _Other) = delete;
	CStateMachine& operator=(CStateMachine&& _Other) noexcept = delete;

protected:

private:

};
