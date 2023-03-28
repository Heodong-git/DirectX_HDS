#pragma once
#include "CKatanaZero_Actor.h"

// ±Ÿ¿∞∏«
class CMonster_Grunt : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CMonster_Grunt();
	~CMonster_Grunt();

	// delete Function
	CMonster_Grunt(const CMonster_Grunt& _Other) = delete;
	CMonster_Grunt(CMonster_Grunt&& _Other) noexcept = delete;
	CMonster_Grunt& operator=(const CMonster_Grunt& _Other) = delete;
	CMonster_Grunt& operator=(CMonster_Grunt&& _Other) noexcept = delete;

protected:

private:

};
