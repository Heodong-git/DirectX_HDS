#pragma once
#include "BaseLevel.h"

// 설명 :
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

	// 초기위치로 리셋 
	// 플레이어가 사망하고 난 이후에 호출되는 함수 
	// 그냥 전부죽이고 새로 생성하는게 맞나?? 아니지 그냥 상태만 바꿔서 다시 가져다놓으면 되는거가틍ㄷ네 
	// 일단 플레이어만 생각해 
	// 일단 퍼블릭 
	virtual void LevelReset() override;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	// 액터 초기위치
	float4 PlayerSetPos = { -850 , -94 };

	// gui
	std::shared_ptr<class StageEditer> m_GUI = nullptr;

	// 디버그용 
	void DebugUpdate();
};
