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

	// ������ ī�޶� �ʱ���ġ ����
	void CameraSetting();

	// ī�޶� �Ǻ� ����
	static std::vector<float4> m_CameraPivots;

protected:
	void Start() override;

private:
	bool PlayerDeathCheck();
	virtual void Reset() override;
};
