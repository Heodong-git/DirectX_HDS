#pragma once
#include "CKatanaZero_Level.h"

// ���� :
class CTitleLevel : public CKatanaZero_Level
{
public:
	// constrcuter destructer
	CTitleLevel();
	~CTitleLevel();

	// delete Function
	CTitleLevel(const CTitleLevel& _Other) = delete;
	CTitleLevel(CTitleLevel&& _Other) noexcept = delete;
	CTitleLevel& operator=(const CTitleLevel& _Other) = delete;
	CTitleLevel& operator=(CTitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<class CTitleUIManager> m_UIManager = nullptr;
};

