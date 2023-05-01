#pragma once
#include "CKatanaZero_Actor.h"

// ���� : �÷��̷������� ���͵��� �����͸� �����صΰ� 
// ������ �����͸� ������� �����, ����ؼ� ����ϴ� ����. 
class GameEngineRenderer;
class CRecordingManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CRecordingManager();
	~CRecordingManager();

	// delete Function
	CRecordingManager(const CRecordingManager& _Other) = delete;
	CRecordingManager(CRecordingManager&& _Other) noexcept = delete;
	CRecordingManager& operator=(const CRecordingManager& _Other) = delete;
	CRecordingManager& operator=(CRecordingManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// �� �ʸ��� ���� ������ ������ ������ �����ϴ� ���
	// �����ؾ��� ����
	// 1. ��ġ . �ϴ� �̰Ÿ������� �غ���
	std::vector<float4> m_vecRecordingInfo;
};
