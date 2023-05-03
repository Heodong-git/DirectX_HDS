#pragma once
#include "CKatanaZero_Actor.h"

// 설명 : 
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CreateRender();

	// 몇개 안들고 있는데 전부 그냥 들고 있는게 맞는거같기도?? 
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGroundRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_HUDRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_InvenRender = nullptr;
	
	// 부모자식구조가 업데이트 되면 게이지 렌더러를 추가로 달아서??  
	std::shared_ptr<class GameEngineSpriteRenderer> m_TimerRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TimerGageRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_BatteryRender = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseLRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseRRender = nullptr;

	

};
