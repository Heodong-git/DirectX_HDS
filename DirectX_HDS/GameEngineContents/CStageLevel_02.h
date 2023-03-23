#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CStageLevel_02 : public GameEngineLevel
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
	void Loading() override;

private:

};
