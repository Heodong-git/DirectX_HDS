#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubBossLevel : public BaseLevel
{
public:
	// constrcuter destructer
	ClubBossLevel();
	~ClubBossLevel();

	// delete Function
	ClubBossLevel(const ClubBossLevel& _Other) = delete;
	ClubBossLevel(ClubBossLevel&& _Other) noexcept = delete;
	ClubBossLevel& operator=(const ClubBossLevel& _Other) = delete;
	ClubBossLevel& operator=(ClubBossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;
};
