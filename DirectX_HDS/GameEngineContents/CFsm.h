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

// ���� :
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

	// ���� �߰� �Լ�
	void AddState(ESTATE _State,
		std::function<void()> _Enter,
		std::function<void(float)>_Update,
		std::function<void()> _Exit)
	{
		if (nullptr == _Enter || nullptr == _Update || nullptr == _Exit)
		{
			MsgAssert("Enter, Update, Exit ������ �Լ��� �Ѱ����� �Լ��� nullptr �Դϴ�.");
			return;
		}

		CState NewState;
		NewState.Enter = _Enter;
		NewState.Update = _Update;
		NewState.Exit = _Exit;
		m_States.insert(std::make_pair(_State, NewState));

	}

	// ���� ���� �Լ�
	void ChangeState(ESTATE _State)
	{
		if (ESTATE::NONE == _State)
		{
			MsgAssert("����ε� State�� �־����� �ʾҽ��ϴ�.");
			return;
		}

		// ���罺����Ʈ�� NONE �� �ƴϰ�, ���� ����� ������Ʈ�� Exit �Լ��� null �� �ƴ϶��. 
		if (m_CurState != ESTATE::NONE && m_States[m_CurState].Exit != nullptr)
		{
			// ���� ����� ������Ʈ�� Exit �Լ� ȣ��.
			m_States[m_CurState].Exit();
		}

		// ���� ���¸� ���� ���·� �����Ѵ�. 
		m_CurState = _State;

		// ���� ������ Enter �Լ��� nullptr �� �ƴ϶��
		if (m_States[m_CurState].Enter != nullptr)
		{
			// ���� ������ Enter �Լ� ȣ�� 
			m_States[m_CurState].Enter();
		}
	}

	// ���� ������Ʈ �Լ�
	void UpdateState(float _DeltaTime)
	{
		if (m_CurState != ESTATE::NONE)
		{
			MsgAssert("���� ���°� NONE �Դϴ�. ���°��� Ȯ���ϼ���. ");
			return;
		}

		// NONE�� �ƴϾ���, ������Ʈ �Լ��� nullptr �� �ƴ϶�� �� ������Ʈ�� Update ȣ��.
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
