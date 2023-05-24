#pragma once
#include "BaseActor.h"

enum class CameraMode
{
	
};

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
	bool RangeOverCheck();

	std::shared_ptr<class GameEngineCamera> m_MainCamera = nullptr;

	// 카메라의 이동가능범위를 어떻게 저장할거니?? 
	// map <맵의 번호 , 좌상단 좌하단 우상단 우하단> 
};
