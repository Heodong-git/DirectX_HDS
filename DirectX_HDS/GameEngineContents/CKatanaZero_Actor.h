#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���Ӿ��͵��� ���� 
class CRecordingInfo
{
public:
	float4 LocalScale = {};
	float4 LocalPos = {};
	float  MoveSpeed = 0.0f;
};



class CKatanaZero_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	CKatanaZero_Actor();
	~CKatanaZero_Actor();

	// delete Function
	CKatanaZero_Actor(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor(CKatanaZero_Actor&& _Other) noexcept = delete;
	CKatanaZero_Actor& operator=(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor& operator=(CKatanaZero_Actor&& _Other) noexcept = delete;

	// �ڽ��� ������ ���̺�,�ε��ϴ� ���.. �ε� 
	// ���� ������ �ִ� ������ �ٸ���... �� 
	// ���ͷ��ڵ����� Ŭ������ ���� ������ �ְ� �ϰ� �� Ŭ���� ������ ������ ���?
	inline std::shared_ptr<CRecordingInfo> GetRecordingInfo()
	{
		return m_RecordingInfo;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	// -------------------------recording info-------------------------------
	// ������� �ʿ��� ��ȭ�� �������� �Ʒ� �κп� �ۼ��ϰ�, �Լ��� �� �������� �����ϰ�, �ε��ϴ� �Լ��� ����? 
	std::shared_ptr<CRecordingInfo> m_RecordingInfo = nullptr;
};
