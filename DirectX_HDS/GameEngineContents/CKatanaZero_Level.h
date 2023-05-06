#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class ELEVEL_STATE
{
	WAIT,
	PLAY,
};

class CKatanaZero_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	CKatanaZero_Level();
	~CKatanaZero_Level();

	// delete Function
	CKatanaZero_Level(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level(CKatanaZero_Level&& _Other) noexcept = delete;
	CKatanaZero_Level& operator=(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level& operator=(CKatanaZero_Level&& _Other) noexcept = delete;

	// Level을 만들때 녹화가 필요없는 레벨은 이걸 호출해서 false로 만든다. 
	inline void RecodingOff()
	{
		m_Recording = false;
	}

	inline bool GetRecordUse()
	{
		return m_Recording;
	}

	inline bool IsTimeOver() const
	{
		return m_TimeOver;
	}

	std::shared_ptr<class CBoss_HeadHunter> GetBoss()
	{
		return m_Boss;
	}

	std::shared_ptr<class CPlayer> GetPlayer()
	{
		return m_Player;
	}

	void SetPlayer(std::shared_ptr<class CPlayer>& _Player)
	{
		m_Player = _Player;
	}

	void SetBoss(std::shared_ptr<class CBoss_HeadHunter>& _Boss)
	{
		m_Boss = _Boss;
	}

	void SetCursor(std::shared_ptr<class CCursor>& _Cursor)
	{
		m_Cursor = _Cursor;
	}

	std::shared_ptr<class CCursor>& GetCursor()
	{
		return m_Cursor;
	}

	ELEVEL_STATE GetCurState()
	{
		return m_CurState;
	}
protected:
	// 녹화하고 역재생 해야하는 레벨에서만 재정의한 Start에서 얘를 호출하면 되게 하려고 했는데
	// 그냥 다호출하거나 오버라이딩으로 처리하고, recording == true 인 레벨에서만 녹화 
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override {};
	void LevelChangeEnd() override {};

private:
	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅을 한다. 
	virtual void CameraLoad();

	float4 m_CurMouseLocalPos = {};

	std::shared_ptr<class CPlayer> m_Player = nullptr;
	std::shared_ptr<class CBoss_HeadHunter> m_Boss = nullptr;
	std::shared_ptr<class CCursor> m_Cursor = nullptr;

	ELEVEL_STATE m_CurState = ELEVEL_STATE::WAIT;

	bool m_Recording = true;
	bool m_TimeOver = false;


};