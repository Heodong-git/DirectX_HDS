#pragma once
#include "CKatanaZero_Level.h"

// Ό³Έν :
class CStageLevel_01 : public CKatanaZero_Level
{
public:
	// constrcuter destructer
	CStageLevel_01();
	~CStageLevel_01();

	// delete Function
	CStageLevel_01(const CStageLevel_01& _Other) = delete;
	CStageLevel_01(CStageLevel_01&& _Other) noexcept = delete;
	CStageLevel_01& operator=(const CStageLevel_01& _Other) = delete;
	CStageLevel_01& operator=(CStageLevel_01&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;
};
