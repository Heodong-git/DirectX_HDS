#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_Boss : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_Boss();
	~ClubLevel_Boss();

	// delete Function
	ClubLevel_Boss(const ClubLevel_Boss& _Other) = delete;
	ClubLevel_Boss(ClubLevel_Boss&& _Other) noexcept = delete;
	ClubLevel_Boss& operator=(const ClubLevel_Boss& _Other) = delete;
	ClubLevel_Boss& operator=(ClubLevel_Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;
};
