#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class CStageLevel_01 : public GameEngineLevel
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
	void Loading() override;

private:

};
