#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Boss_HeadHunter : public BaseActor
{
public:
	// constrcuter destructer
	Boss_HeadHunter();
	~Boss_HeadHunter();

	// delete Function
	Boss_HeadHunter(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter(Boss_HeadHunter&& _Other) noexcept = delete;
	Boss_HeadHunter& operator=(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter& operator=(Boss_HeadHunter&& _Other) noexcept = delete;

protected:

private:

};
