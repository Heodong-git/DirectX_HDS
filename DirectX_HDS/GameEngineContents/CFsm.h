#pragma once

// Ό³Έν :
class CFsm
{
public:
	// constrcuter destructer
	CFsm();
	~CFsm();

	// delete Function
	CFsm(const CFsm& _Other) = delete;
	CFsm(CFsm&& _Other) noexcept = delete;
	CFsm& operator=(const CFsm& _Other) = delete;
	CFsm& operator=(CFsm&& _Other) noexcept = delete;

protected:

private:

};
