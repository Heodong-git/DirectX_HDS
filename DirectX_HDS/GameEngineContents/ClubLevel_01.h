#pragma once
#include "BaseLevel.h"

// 설명 :
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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	std::shared_ptr<class StageEditer> m_GUI = nullptr;

	// 디버그용 
	void DebugUpdate();
};
