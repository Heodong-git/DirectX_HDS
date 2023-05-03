#pragma once
#include "CKatanaZero_Actor.h"

// ���� : 
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

	// � �ȵ�� �ִµ� ���� �׳� ��� �ִ°� �´°Ű��⵵?? 
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGroundRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_HUDRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_InvenRender = nullptr;
	
	// �θ��ڽı����� ������Ʈ �Ǹ� ������ �������� �߰��� �޾Ƽ�??  
	std::shared_ptr<class GameEngineSpriteRenderer> m_TimerRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TimerGageRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_BatteryRender = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseLRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_MouseRRender = nullptr;

	

};
