#pragma once
#include "BaseActor.h"

class PlayManager : public BaseActor
{
public:
	enum class LevelName
	{
		NONE,
		CLUB,
		CLUBBOSS,
	};

public:
	static PlayManager* MainManager;

public:
	// constrcuter destructer
	PlayManager();
	~PlayManager();

	// delete Function
	PlayManager(const PlayManager& _Other) = delete;
	PlayManager(PlayManager&& _Other) noexcept = delete;
	PlayManager& operator=(const PlayManager& _Other) = delete;
	PlayManager& operator=(PlayManager&& _Other) noexcept = delete;

	static void SetLevelType(LevelName _Name)
	{
		m_LevelName = _Name;
	}

	static LevelName GetLevelName()
	{
		return m_LevelName;
	}

	void Update(float _DeltaTime);

	// 레벨별 카메라 초기위치세팅
	void CameraSetting();

	float4 GetCameraPivot()
	{
		return m_CameraPivot;
	}

protected:


private:
	float4 m_CameraPivot = {};
	static LevelName m_LevelName;
};
