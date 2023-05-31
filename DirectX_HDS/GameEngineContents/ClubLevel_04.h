#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_04 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_04();
	~ClubLevel_04();

	// delete Function
	ClubLevel_04(const ClubLevel_04& _Other) = delete;
	ClubLevel_04(ClubLevel_04&& _Other) noexcept = delete;
	ClubLevel_04& operator=(const ClubLevel_04& _Other) = delete;
	ClubLevel_04& operator=(ClubLevel_04&& _Other) noexcept = delete;

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
