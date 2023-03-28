#pragma once
#include "CKatanaZero_Actor.h"

// ∞ªΩ∫≈Õ 
class CMonster_Gangster : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CMonster_Gangster();
	~CMonster_Gangster();

	// delete Function
	CMonster_Gangster(const CMonster_Gangster& _Other) = delete;
	CMonster_Gangster(CMonster_Gangster&& _Other) noexcept = delete;
	CMonster_Gangster& operator=(const CMonster_Gangster& _Other) = delete;
	CMonster_Gangster& operator=(CMonster_Gangster&& _Other) noexcept = delete;

protected:

private:

};
