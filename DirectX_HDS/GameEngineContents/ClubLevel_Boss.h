#pragma once
#include "BaseLevel.h"

// 설명 :
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

	bool m_Appear = false;

	// 몬스터들의 등장위치 4군데를 저장.. 음.. 어 음 아 음 허 흠
	
};
