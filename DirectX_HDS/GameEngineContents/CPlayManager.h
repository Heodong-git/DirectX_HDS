#pragma once
#include "CKatanaZero_Actor.h"

class CPlayManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CPlayManager();
	~CPlayManager();

	// delete Function
	CPlayManager(const CPlayManager& _Other) = delete;
	CPlayManager(CPlayManager&& _Other) noexcept = delete;
	CPlayManager& operator=(const CPlayManager& _Other) = delete;
	CPlayManager& operator=(CPlayManager&& _Other) noexcept = delete;

	void SetBattery(std::shared_ptr<class CBattery>& _Battery)
	{
		m_Battery = _Battery;
	}

	void SetInven(std::shared_ptr<class CInven>& _Inven)
	{
		m_Inven = _Inven;
	}

	void SetTimer(std::shared_ptr<class CTimer>& _Timer)
	{
		m_Timer = _Timer;
	}
	
	void CreateRender();
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	// 타이머
	std::shared_ptr<class CTimer> m_Timer = nullptr;
	// 배터리 
	std::shared_ptr<class CBattery> m_Battery = nullptr;
	// 인벤토리 
	std::shared_ptr<class CInven> m_Inven = nullptr;
	// HUD

	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGroundRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_HUDRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseLRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseRRender = nullptr;
};
