#pragma once
#include "CKatanaZero_Actor.h"
// ���� :
class GameEngineRenderer;
class CTitleManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CTitleManager();
	~CTitleManager();

	// delete Function
	CTitleManager(const CTitleManager& _Other) = delete;
	CTitleManager(CTitleManager&& _Other) noexcept = delete;
	CTitleManager& operator=(const CTitleManager& _Other) = delete;
	CTitleManager& operator=(CTitleManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderer> m_BackGroundRenderer;
	// �������� ������Ʈ ����Ʈ�� �߰��� �ǰ�, ���� ����Ϸ��� ������ �ִ°� ���Ѱ�?
};
