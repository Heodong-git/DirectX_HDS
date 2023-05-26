#pragma once
#include "BaseActor.h"


// ���� ������ ī�޶� �ƴѰŰ���.. 
// ���� :
class CameraMovement : public BaseActor
{
	friend class Player;
public:
	static CameraMovement* FollowCamera;

public:
	// constrcuter destructer
	CameraMovement();
	~CameraMovement();

	// delete Function
	CameraMovement(const CameraMovement& _Other) = delete;
	CameraMovement(CameraMovement&& _Other) noexcept = delete;
	CameraMovement& operator=(const CameraMovement& _Other) = delete;
	CameraMovement& operator=(CameraMovement&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineUIRenderer> g_SuccessRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_FailRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_BlackBoxRender;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Move(float _DeltaTime);
	bool RangeOverCheck(float _DeltaTime);
	bool PlayerDeathCheck();

	std::shared_ptr<class GameEngineCamera> m_MainCamera = nullptr;
	float m_MoveSpeed = 200.0f;
	
	// �»��, ����, ���ϴ� , ���ϴ� ������ 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
};
