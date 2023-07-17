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

	void CreateHeadHunter();
	inline const bool IsAppear()
	{
		return m_Appear;
	}

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
	std::shared_ptr<class Platform> m_LevelChangePlatform = nullptr;
	void LevelChangeUpdate();

	bool m_Appear = false;	
	GameEngineSoundPlayer m_BGMPlayer;
};
