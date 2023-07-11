#pragma once
#include "BaseActor.h"

// ���� :
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

	// �������� Ŭ���� ����, ����, Ŭ���� ����, ���콺 Ŭ�� üũ�� �ݸ���
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

	// �»��, ����, ���ϴ� , ���ϴ� ������ 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
	virtual void Reset() override;
};
