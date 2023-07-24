#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_Boss_01 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_Boss_01();
	~ClubLevel_Boss_01();

	// delete Function
	ClubLevel_Boss_01(const ClubLevel_Boss_01& _Other) = delete;
	ClubLevel_Boss_01(ClubLevel_Boss_01&& _Other) noexcept = delete;
	ClubLevel_Boss_01& operator=(const ClubLevel_Boss_01& _Other) = delete;
	ClubLevel_Boss_01& operator=(ClubLevel_Boss_01&& _Other) noexcept = delete;

	void CreateHeadHunter();
	inline const bool IsAppear()
	{
		return m_Appear;
	}

	std::shared_ptr<class Boss_HeadHunter> GetBossPtr()
	{
		return m_HeadHunter;
	}

	void BGMOff()
	{
		m_BGMPlayer.Stop();
	}

	const inline bool IsEnding() const
	{
		return m_GameEnd;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	void LevelStartCheck();

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

	void CreateObjAndInit();

	virtual void KeyUpdate() override;
	virtual void CreateKey() override;

	virtual void GUISetting() override;

	std::shared_ptr<class StageEditer> m_GUI = nullptr;
	std::shared_ptr<class Platform> m_ColCheckObj = nullptr;
	std::shared_ptr<class Boss_HeadHunter> m_HeadHunter = nullptr;

	bool m_Appear = false;
	GameEngineSoundPlayer m_BGMPlayer;

	float m_Duration = 3.5f;
	bool m_GameEnd = false;
	bool m_RealEnd = false;
	void GameEngineCheck(float _DeltaTime);
};
