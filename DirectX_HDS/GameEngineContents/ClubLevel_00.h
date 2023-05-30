#pragma once
#include "BaseLevel.h"

// ���� :
class ClubLevel_00 : public BaseLevel
{
public:
	// constrcuter destructer
	ClubLevel_00();
	~ClubLevel_00();

	// delete Function
	ClubLevel_00(const ClubLevel_00& _Other) = delete;
	ClubLevel_00(ClubLevel_00&& _Other) noexcept = delete;
	ClubLevel_00& operator=(const ClubLevel_00& _Other) = delete;
	ClubLevel_00& operator=(ClubLevel_00&& _Other) noexcept = delete;

	// �ʱ���ġ�� ���� 
	// �÷��̾ ����ϰ� �� ���Ŀ� ȣ��Ǵ� �Լ� 
	// �׳� �������̰� ���� �����ϴ°� �³�?? �ƴ��� �׳� ���¸� �ٲ㼭 �ٽ� �����ٳ����� �Ǵ°Ű��v���� 
	// �ϴ� �÷��̾ ������ 
	// �ϴ� �ۺ� 
	// virtual void LevelReset() override;

	float4& GetPlayerSetPos()
	{
		return m_PlayerSetPos;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

private:
	// ���� �ʱ���ġ
	// ������ �� �ȵǴϱ� �� ������ �־�, �ϴ� �ʿ��Ѿֵ� �����ΰ� 
	float4 m_PlayerSetPos = { -850 , -94 };

	// gui
	std::shared_ptr<class StageEditer> m_GUI = nullptr;

	// ����׿� 
	void DebugUpdate();
};
