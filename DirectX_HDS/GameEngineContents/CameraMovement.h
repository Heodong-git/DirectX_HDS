#pragma once
#include "BaseActor.h"


// 뭔가 역할이 카메라가 아닌거같아.. 
// 지금 스테이지 미클리어시 화면에 텍스트 띄우기 + 레벨 리셋 호출을 하고 있는데 얘가 사실상 매니저가 아닌가.. 
// 설명 :
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
	static std::shared_ptr<class GameEngineCollision> g_MouseCheckCollision;

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
	
	// 좌상단, 우상단, 좌하단 , 우하단 순서로 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
};
