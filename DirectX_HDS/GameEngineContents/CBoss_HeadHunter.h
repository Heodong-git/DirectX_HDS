#pragma once

// ���� :
class CBoss_HeadHunter
{
public:
	// constrcuter destructer
	CBoss_HeadHunter();
	~CBoss_HeadHunter();

	// delete Function
	CBoss_HeadHunter(const CBoss_HeadHunter& _Other) = delete;
	CBoss_HeadHunter(CBoss_HeadHunter&& _Other) noexcept = delete;
	CBoss_HeadHunter& operator=(const CBoss_HeadHunter& _Other) = delete;
	CBoss_HeadHunter& operator=(CBoss_HeadHunter&& _Other) noexcept = delete;

protected:

private:

};
