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


	bool m_Appear = false;
};
