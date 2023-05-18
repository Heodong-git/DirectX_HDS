#pragma once
#include "BaseLevel.h"

// 설명 :
class ClubLevel_02 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_02();
	~ClubLevel_02();

	// delete Function
	ClubLevel_02(const ClubLevel_02& _Other) = delete;
	ClubLevel_02(ClubLevel_02&& _Other) noexcept = delete;
	ClubLevel_02& operator=(const ClubLevel_02& _Other) = delete;
	ClubLevel_02& operator=(ClubLevel_02&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	std::shared_ptr<class StageEditer> m_GUI = nullptr;

	// 디버그용 
	void DebugUpdate();
};
