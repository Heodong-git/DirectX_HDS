#pragma once
#include "BaseActor.h"

// 설명 :
class LaserSwitch : public BaseActor
{
public:
	// constrcuter destructer
	LaserSwitch();
	~LaserSwitch();

	// delete Function
	LaserSwitch(const LaserSwitch& _Other) = delete;
	LaserSwitch(LaserSwitch&& _Other) noexcept = delete;
	LaserSwitch& operator=(const LaserSwitch& _Other) = delete;
	LaserSwitch& operator=(LaserSwitch&& _Other) noexcept = delete;

	// push laser 
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 플레이어가 충돌중인 상태에서 특정 키 입력시 스위치 온오프 
	bool m_IsOn = true;
	// 스위치
	void LaserSwitchButton()
	{
		m_IsOn = !m_IsOn;
	}

	// 리셋 
	virtual void Reset() override;

	void DebugUpdate();

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 리소스 로드및생성
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_SwitchRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::vector<std::shared_ptr<class Laser>> m_Lasers = std::vector<std::shared_ptr<class Laser>>();

};
