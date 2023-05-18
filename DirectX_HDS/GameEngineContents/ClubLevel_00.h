#pragma once
#include "BaseLevel.h"

// 설명 :
class ClubLevel_00 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_00();
	~ClubLevel_00();

	// delete Function
	ClubLevel_00(const ClubLevel_00& _Other) = delete;
	ClubLevel_00(ClubLevel_00&& _Other) noexcept = delete;
	ClubLevel_00& operator=(const ClubLevel_00& _Other) = delete;
	ClubLevel_00& operator=(ClubLevel_00&& _Other) noexcept = delete;


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
