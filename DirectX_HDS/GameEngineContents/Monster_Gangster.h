#pragma once
#include "BaseActor.h"

// ∞ªΩ∫≈Õ 
class Monster_Gangster : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Gangster();
	~Monster_Gangster();

	// delete Function
	Monster_Gangster(const Monster_Gangster& _Other) = delete;
	Monster_Gangster(Monster_Gangster&& _Other) noexcept = delete;
	Monster_Gangster& operator=(const Monster_Gangster& _Other) = delete;
	Monster_Gangster& operator=(Monster_Gangster&& _Other) noexcept = delete;

protected:

private:

};
