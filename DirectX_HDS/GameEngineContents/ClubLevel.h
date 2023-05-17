#pragma once
#include "BaseLevel.h"

// 설명 :
class ClubLevel : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel();
	~ClubLevel();

	// delete Function
	ClubLevel(const ClubLevel& _Other) = delete;
	ClubLevel(ClubLevel&& _Other) noexcept = delete;
	ClubLevel& operator=(const ClubLevel& _Other) = delete;
	ClubLevel& operator=(ClubLevel&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	std::shared_ptr<class StageEditer> m_GUI = nullptr;
	std::shared_ptr<class Map> m_Club_Map = nullptr;

	// 디버그용 
	void DebugUpdate();
	void ChangeMap();
	void ChangeColMap();
};
