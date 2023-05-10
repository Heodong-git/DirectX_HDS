#pragma once
#include "CKatanaZero_Level.h"

// Ό³Έν :
class CStageLevel_02 : public CKatanaZero_Level
{
public:
	// constrcuter destructer
	CStageLevel_02();
	~CStageLevel_02();

	// delete Function
	CStageLevel_02(const CStageLevel_02& _Other) = delete;
	CStageLevel_02(CStageLevel_02&& _Other) noexcept = delete;
	CStageLevel_02& operator=(const CStageLevel_02& _Other) = delete;
	CStageLevel_02& operator=(CStageLevel_02&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;
};
