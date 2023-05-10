#pragma once
#include "CKatanaZero_Actor.h"

class CPlayManager
{
public:
	enum class LEVELTYPE
	{
		NONE,
		STAGE_01,
		STAGE_02,
	};

public:
	static CPlayManager* m_Inst;

	// 사실 할필요 없는거같은데?
	static CPlayManager* GetInst()
	{
		if (nullptr == m_Inst)
		{
			m_Inst = new CPlayManager();
		}

		return m_Inst;
	}

	static void DestroyInst()
	{
		if (nullptr != m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
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

	static void SetBattery(std::shared_ptr<class Battery>& _Battery)
	{
 		m_Battery = _Battery;
	}

	static void SetInven(std::shared_ptr<class Inven>& _Inven)
	{
		m_Inven = _Inven;
	}

	static void SetTimer(std::shared_ptr<class CTimer>& _Timer)
	{
		m_Timer = _Timer;
	}

	static void SetHud(std::shared_ptr<class Hud>& _Hud)
	{
		m_Hud = _Hud;
	}

	static void SetPlayer(std::shared_ptr<class CPlayer>& _Player)
	{
		m_Player = _Player;
	}

	static std::shared_ptr<class CPlayer>& GetPlayer()
	{
		return m_Player;
	}
	
	static void SetLevelType(LEVELTYPE _Type)
	{
		m_LevelType = _Type;
	}

	static LEVELTYPE GetLevelType()
	{
		return m_LevelType;
	}

	static void CreateRender();
	static void Update(float _DeltaTime);
	void CameraSetting();

	float4 GetCameraPivot()
	{
		return m_CameraPivot;
	}
protected:


private:
	float4 m_CameraPivot = {};
	static LEVELTYPE m_LevelType;
	static std::shared_ptr<class CTimer> m_Timer;
	static std::shared_ptr<class Battery> m_Battery;
	static std::shared_ptr<class Inven> m_Inven;
	static std::shared_ptr<class Hud> m_Hud;
	static std::shared_ptr<class CPlayer> m_Player;
};
