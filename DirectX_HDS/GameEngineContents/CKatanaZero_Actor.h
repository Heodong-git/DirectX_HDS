#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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


protected:
	// 굳이 이럴거 없이 그냥 멤버변수를 가져다 써도 되지만 가독성이 이게 더 좋은 것 같음.
	inline void SetAngle(float _Angle)
	{
		m_Angle = _Angle;
	}

	inline float GetAngle() const
	{
		return m_Angle;
	}

private:
	float m_Angle = 0.0f;
};
