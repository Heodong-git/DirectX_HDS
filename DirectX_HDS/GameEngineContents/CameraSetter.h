#pragma once
#include "BaseActor.h"

// 얘이름을 카메라세터로 바꿀까..? ㅇㅇ 얘를 카메라 세터로 바꾸고 
class CameraSetter : public BaseActor
{
public:
	static CameraSetter* MainCamSetter;

public:
	// constrcuter destructer
	CameraSetter();
	~CameraSetter();

	// delete Function
	CameraSetter(const CameraSetter& _Other) = delete;
	CameraSetter(CameraSetter&& _Other) noexcept = delete;
	CameraSetter& operator=(const CameraSetter& _Other) = delete;
	CameraSetter& operator=(CameraSetter&& _Other) noexcept = delete;


	void Update(float _DeltaTime);

	// 레벨별 카메라 초기위치세팅
	void CameraSetting();

	static std::vector<float4> m_CameraPivots;

protected:
	void Start() override;

private:
	bool PlayerDeathCheck();
};
