#pragma once
#include "BaseLevel.h"

// ���� :
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


protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	// gui
	std::shared_ptr<class StageEditer> m_GUI = nullptr;

	// �������� ���ѽð�
	// ���������� ���۵Ǹ� �𿩳����� 
	float m_LimitTime = 110.0f;

	// ���� �ʱ���ġ
	float4 PlayerSetPos = { -850 , -94 };

	// ����׿� 
	void DebugUpdate();
};
