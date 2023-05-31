#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_01 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_01();
	~ClubLevel_01();

	// delete Function
	ClubLevel_01(const ClubLevel_01& _Other) = delete;
	ClubLevel_01(ClubLevel_01&& _Other) noexcept = delete;
	ClubLevel_01& operator=(const ClubLevel_01& _Other) = delete;
	ClubLevel_01& operator=(ClubLevel_01&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

	void CreateObjAndInit();

	virtual void KeyUpdate() override;
	virtual void CreateKey() override;

	virtual void GUISetting() override;
	std::shared_ptr<class StageEditer> m_GUI = nullptr;
};
