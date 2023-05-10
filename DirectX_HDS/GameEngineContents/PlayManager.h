#pragma once
#include "BaseActor.h"

class PlayManager
{
public:
	enum class LevelName
	{
		NONE,
		CLUB,
		CLUBBOSS,
	};

public:
	static PlayManager* m_Inst;

	// 사실 할필요 없는거같은데?
	static PlayManager* GetInst()
	{
		if (nullptr == m_Inst)
		{
			m_Inst = new PlayManager();
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
	PlayManager();
	~PlayManager();

	// delete Function
	PlayManager(const PlayManager& _Other) = delete;
	PlayManager(PlayManager&& _Other) noexcept = delete;
	PlayManager& operator=(const PlayManager& _Other) = delete;
	PlayManager& operator=(PlayManager&& _Other) noexcept = delete;

	static void SetBattery(std::shared_ptr<class Battery>& _Battery)
	{
 		m_Battery = _Battery;
	}

	static void SetInven(std::shared_ptr<class Inven>& _Inven)
	{
		m_Inven = _Inven;
	}

	static void SetTimer(std::shared_ptr<class Timer>& _Timer)
	{
		m_Timer = _Timer;
	}

	static void SetHud(std::shared_ptr<class Hud>& _Hud)
	{
		m_Hud = _Hud;
	}

	static void SetPlayer(std::shared_ptr<class Player>& _Player)
	{
		m_Player = _Player;
	}

	static std::shared_ptr<class Player>& GetPlayer()
	{
		return m_Player;
	}
	
	static void SetLevelType(LevelName _Name)
	{
		m_LevelName = _Name;
	}

	static LevelName GetLevelName()
	{
		return m_LevelName;
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
	static LevelName m_LevelName;
	static std::shared_ptr<class Timer> m_Timer;
	static std::shared_ptr<class Battery> m_Battery;
	static std::shared_ptr<class Inven> m_Inven;
	static std::shared_ptr<class Hud> m_Hud;
	static std::shared_ptr<class Player> m_Player;
};
