#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_03 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_03();
	~ClubLevel_03();

	// delete Function
	ClubLevel_03(const ClubLevel_03& _Other) = delete;
	ClubLevel_03(ClubLevel_03&& _Other) noexcept = delete;
	ClubLevel_03& operator=(const ClubLevel_03& _Other) = delete;
	ClubLevel_03& operator=(ClubLevel_03&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

	virtual void KeyUpdate() override;
	virtual void CreateKey() override;

	void CreateObjAndInit(); 

	virtual void GUISetting() override;
	std::shared_ptr<class StageEditer> m_GUI = nullptr;
};
