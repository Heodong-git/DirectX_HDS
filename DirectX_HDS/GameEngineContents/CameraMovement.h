#pragma once
#include "BaseActor.h"

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Move(float _DeltaTime);
	bool RangeOverCheck(float _DeltaTime);

	std::shared_ptr<class GameEngineCamera> m_MainCamera = nullptr;
	float m_MoveSpeed = 200.0f;
	
	// 좌상단, 우상단, 좌하단 , 우하단 순서로 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
};
