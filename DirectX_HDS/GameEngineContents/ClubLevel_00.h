#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class ClubLevel_00 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_00();
	~ClubLevel_00();

	// delete Function
	ClubLevel_00(const ClubLevel_00& _Other) = delete;
	ClubLevel_00(ClubLevel_00&& _Other) noexcept = delete;
	ClubLevel_00& operator=(const ClubLevel_00& _Other) = delete;
	ClubLevel_00& operator=(ClubLevel_00&& _Other) noexcept = delete;

	float4& GetPlayerSetPos()
	{
		return m_PlayerSetPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	void GUISetting();
	float4 m_PlayerSetPos = { -850 , -94 };

	std::shared_ptr<class StageEditer> m_GUI = nullptr;
};
