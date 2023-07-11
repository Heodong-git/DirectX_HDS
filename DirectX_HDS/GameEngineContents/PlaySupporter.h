#pragma once
#include "BaseActor.h"

// 설명 :
class PlaySupporter : public BaseActor
{
	friend class Player;
public:
	static PlaySupporter* MainSupporter;
public:
	// constrcuter destructer
	PlaySupporter();
	~PlaySupporter();

	// delete Function
	PlaySupporter(const PlaySupporter& _Other) = delete;
	PlaySupporter(PlaySupporter&& _Other) noexcept = delete;
	PlaySupporter& operator=(const PlaySupporter& _Other) = delete;
	PlaySupporter& operator=(PlaySupporter&& _Other) noexcept = delete;

	// 스테이지 클리어 실패, 투명, 클리어 성공, 마우스 클릭 체크용 콜리전
	static std::shared_ptr<class GameEngineUIRenderer> g_FailRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_BlackBoxRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_ClearRender;

	void ResetButtonOn();
	void CameraZoomEffect(const float _Ratio);
	void CameraShake(float _DeltaTime);


	virtual void ForcedReset() override;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	void CameraMovement(float _DeltaTime);
	
	bool PlayerDeathCheck();
	void LevelResetCheck();

	std::shared_ptr<class GameEngineCamera> m_MainCamera = nullptr;
	const float m_MoveSpeed = 500.0f;
	
	void ComponentSetting();
	void SaveCameraRange();
	void LoadResources();

	// 좌상단, 우상단, 좌하단 , 우하단 순서로 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
	virtual void Reset() override;
};
