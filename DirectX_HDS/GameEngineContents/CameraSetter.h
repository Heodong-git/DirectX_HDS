#pragma once
#include "BaseActor.h"

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

	// 레벨별 카메라 초기위치 세팅
	void CameraSetting();

	// 카메라 피봇 저장
	static std::vector<float4> m_CameraPivots;

protected:
	void Start() override;

private:
	bool PlayerDeathCheck();
	virtual void Reset() override;
};
