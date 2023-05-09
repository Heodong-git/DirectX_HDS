#pragma once
#include "CKatanaZero_Actor.h"

class CPlayManager
{
public:
	static CPlayManager* m_Inst;

	static CPlayManager* GetInst()
	{
		return m_Inst;
	}
public:
	// constrcuter destructer
	CPlayManager();
	~CPlayManager();

	// delete Function
	CPlayManager(const CPlayManager& _Other) = delete;
	CPlayManager(CPlayManager&& _Other) noexcept = delete;
	CPlayManager& operator=(const CPlayManager& _Other) = delete;
	CPlayManager& operator=(CPlayManager&& _Other) noexcept = delete;

	static void SetBattery(std::shared_ptr<class CBattery>& _Battery)
	{
 		m_Battery = _Battery;
	}

	static void SetInven(std::shared_ptr<class CInven>& _Inven)
	{
		m_Inven = _Inven;
	}

	static void SetTimer(std::shared_ptr<class CTimer>& _Timer)
	{
		m_Timer = _Timer;
	}

	static void SetHud(std::shared_ptr<class CHud>& _Hud)
	{
		m_Hud = _Hud;
	}
	
	void CreateRender();
	
protected:
private:

	// Ÿ�̸�
	static std::shared_ptr<class CTimer> m_Timer;
	// ���͸� 
	static std::shared_ptr<class CBattery> m_Battery;
	// �κ��丮 
	static std::shared_ptr<class CInven> m_Inven;
	// HUD
	static std::shared_ptr<class CHud> m_Hud;
};
