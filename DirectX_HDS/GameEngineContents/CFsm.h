#pragma once

enum class ESTATE
{
	NONE,   // 0
	IDLE,	// 1
	MOVE,	// 2
	JUMP,	// 3
	SLASH,	// 4
};

class CState
{
	friend class CFsm;
private:
	std::function<void()> Enter = nullptr;
	std::function<void(float)> Update = nullptr;
	std::function<void()> Exit = nullptr;
};

// 설명 :
class CFsm
{
public:
	// constrcuter destructer
	CFsm();
	~CFsm();

	// delete Function
	CFsm(const CFsm& _Other) = delete;
	CFsm(CFsm&& _Other) noexcept = delete;
	CFsm& operator=(const CFsm& _Other) = delete;
	CFsm& operator=(CFsm&& _Other) noexcept = delete;

	// 상태 추가 함수
	void AddState(ESTATE _State,
		std::function<void()> _Enter,
		std::function<void(float)>_Update,
		std::function<void()> _Exit)
	{
		if (nullptr == _Enter || nullptr == _Update || nullptr == _Exit)
		{
			MsgAssert("Enter, Update, Exit 세개의 함수중 한가지의 함수가 nullptr 입니다.");
			return;
		}

		CState NewState;
		NewState.Enter = _Enter;
		NewState.Update = _Update;
		NewState.Exit = _Exit;
		m_States.insert(std::make_pair(_State, NewState));

	}

	// 상태 변경 함수
	void ChangeState(ESTATE _State)
	{
		if (ESTATE::NONE == _State)
		{
			MsgAssert("제대로된 State를 넣어주지 않았습니다.");
			return;
		}

		// 현재스테이트가 NONE 이 아니고, 현재 저장된 스테이트의 Exit 함수가 null 이 아니라면. 
		if (m_CurState != ESTATE::NONE && m_States[m_CurState].Exit != nullptr)
		{
			// 현재 저장된 스테이트의 Exit 함수 호출.
			m_States[m_CurState].Exit();
		}

		// 현재 상태를 다음 상태로 변경한다. 
		m_CurState = _State;

		// 현재 상태의 Enter 함수가 nullptr 이 아니라면
		if (m_States[m_CurState].Enter != nullptr)
		{
			// 현재 상태의 Enter 함수 호출 
			m_States[m_CurState].Enter();
		}
	}

	// 상태 업데이트 함수
	void UpdateState(float _DeltaTime)
	{
		if (m_CurState != ESTATE::NONE)
		{
			MsgAssert("현재 상태가 NONE 입니다. 상태값을 확인하세요. ");
			return;
		}

		// NONE이 아니었고, 업데이트 함수가 nullptr 이 아니라면 그 스테이트의 Update 호출.
		if (m_States[m_CurState].Update != nullptr)
		{
			m_States[m_CurState].Update(_DeltaTime);
		}
	}

protected:

private:
	std::map<ESTATE, CState> m_States = std::map<ESTATE, CState>();
	ESTATE m_CurState = ESTATE::IDLE;
};
