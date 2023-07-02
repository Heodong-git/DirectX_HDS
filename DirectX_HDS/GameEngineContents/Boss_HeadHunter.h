#pragma once
#include "BaseActor.h"

enum class BossPhase
{
	FIRST,
	SECOND,
};

enum class BossState
{
	NONE,
	INTRO,
	IDLE,			// ���̵� 2
	RIFLE,			// ������ 3
	GUN,			// ��(����ź) 4 
	ROLL,			// ȸ��(������) 5
	JUMP,

	DASH,
	DASH_END,

	SWEEP,			// 12�� ���⿡�� ������ 180�������� 

	HURT,			 // �ĸ�
	RECOVER,		 // �ĸ� �� ���� 
	TRANSPARENCY,    // ���� 
	REAPPEAR,		 // ������� ����, ����� ������Ʈ, ����� ����, Ư���ð� ���� �ٸ� ������Ʈ�� �����ϵ��� 
	
	TELEPORTIN_CEILING,
	TELEPORTOUT_CEILING,
	TELEPORTIN_SWEEP,
	TELEPORTOUT_SWEEP,
	TELEPORTIN_RIFLE,
	TELEPORTOUT_RIFLE,

	TELEPORTIN_WALL,
	
	JUMP_RIFLE,
	JUMP_RIFLE_LAND,

	CHANGEPHASE,	 // ������ü����, �ʿ� �ͽ��÷��� ����Ʈ���� 
	TURRET_SUMMONS,  // �ͷ� ��ȯ 

	MAX,
};


// ���� :
class Boss_HeadHunter : public BaseActor
{
	friend class ClubLevel_Boss_01;
public:
	// constrcuter destructer
	Boss_HeadHunter();
	~Boss_HeadHunter();

	// delete Function
	Boss_HeadHunter(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter(Boss_HeadHunter&& _Other) noexcept = delete;
	Boss_HeadHunter& operator=(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter& operator=(Boss_HeadHunter&& _Other) noexcept = delete;

	inline BossState GetCurState()
	{
		return m_CurState;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	inline void ChangePhase(BossPhase _Phase)
	{
		m_CurPhase = _Phase;
	}

	void CreateTpEffect();

	void Reset();
	void HurtCheck(float _DeltaTime);
	void DebugUpdate();

	void SummonsMonstersUpdate(float _DeltaTime);

	// �ؽ�Ʈ���� üũ
	void NextTransUpdate();
	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;
	const float4 m_DebugPivot = float4{ 30.0f, 42.0f };

	// �ʱ⼼��
	void ComponentSetting();
	void LoadAndCreateAnimation();
	void LoadSound();

	// ����, �ݸ��� 
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;


	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_AttCollision = nullptr;

	void AttCollisionOn();
	void AttCollisionOff();

	// ����� ����Ʈ 
	void CreateRifleEffect();
	std::shared_ptr<class HeadHunter_RifleEffect> m_Effect = nullptr;
	std::shared_ptr<class HeadHunter_RifleEffect> m_SweepEffect = nullptr;
	float4 m_RifleEffectPivot = float4{ 540.0f , 54.5f };


	float m_PhasePivot = -60.0f;

	// �⺻���� 
	// �� 3��Ʈ�� ���ϰ�, ī��Ʈ�� 5�� �Ǹ� 2������� ��ȯ, ���� �μ��� ȿ���� �ְ�, �Ʒ��� �̵��Ѵ�. 
	int m_Phase1_HitCount = 3;
	int m_Phase2_HitCount = 5;
	float m_RollSpeed = 500.0f;
	bool m_Dir = false;

	// true = ������, false = ���� 
	void DirCheck();
	void ChangeDir();

	float m_Ratio = 0.0f;
	// ��Ʈ�Ǿ����� ������������ ����ϱ� ���� ����
	float4 m_HitPos = {};
	float4 m_HitEndPos = {};
	float4 m_MiddlePos = {};
	float4 m_MainPos = {}; 

	// ���� ��ȯ ��ġ
	std::vector<float4> m_SummonsPoss = std::vector<float4>();
	std::vector<std::shared_ptr<BaseActor>> m_SummonsMonsters = std::vector<std::shared_ptr<BaseActor>>();


	bool m_SetMine = false;
	// ������ ������ ����, 
	std::vector<std::shared_ptr<class Remote_Mine>> m_Mines = std::vector<std::shared_ptr<class Remote_Mine>>();
	

	// ������ ���� death �����̰�, �÷��̾ ����ִٸ� 
	// �÷��̾ ������ forcefall ���·� �����Ѵ�. 
	bool PlayerLiveCheck();

	float m_IdleDuration = 0.25f;

	// 4�ʵڿ� 
	float m_TransDuration = 3.0f;

	float m_TurretSummons_Duration = 3.0f;

	float m_PhaseDuration = 0.0f;

	// ���� ������ 
	BossPhase m_CurPhase = BossPhase::FIRST;
	bool m_Summons = false; 
	bool m_SummonsEndCheck = false;


	size_t m_MineCount = 21;

	// world
	const float4 m_TeleportPos = float4{ -68.0f, 58.0f };
	const float4 m_DashPos = float4{ -68.0f, -205.0f };

	const float4 m_TeleportLeftWallPos = float4{ -485.0f,  -50.0f };
	const float4 m_TeleportRightWallPos = float4{ 485.0f,  -50.0f };

	// ��ȯ��ų, 
	void SummonsMonsters();
	void SummonsTurrets();

	// �ͷ�����
	// �ͷ� ��ȯ��ġ, world 
	const float4 m_TurretWallPos = float4{ -491.0f , -87.0f };
	const float4 m_Turret_FirstPos = float4{ -451.0f , -127.0f };
	const float4 m_Turret_SecondPos = float4{ -451.0f, -27.0f };

	bool m_IsTurretSummons = false;

	std::shared_ptr<class Turret_Wall> m_TurretWall = nullptr;
	std::shared_ptr<class Turret> m_Turret_First = nullptr;
	std::shared_ptr<class Turret> m_Turret_Second = nullptr;
	
	bool m_IsDoubleSweep = false;

	// ceiling 
	std::vector<float4> m_vecCeilingPos = std::vector<float4>();
	void CeilingPointInit();
	const float4& CeilingPointShuffle();

	bool m_TpInStart = false;
	size_t m_TpCount = 0;
	float4 m_TpCeilingPos = float4{ 0.0f, 0.0f };

	float4 m_TpRifleLeftPos = float4{ 394.0f, -263.0f , };
	float4 m_TpRifleRightPos = float4{ -418.0f , -263.0f };

	// --------------------------------------- state -----------------------------------------
	// ���°� ����
	void ChangeState(BossState _State);
	// ���� ���°��� ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	BossState m_CurState = BossState::IDLE;
	BossState m_PrevState = BossState::NONE;
	BossState m_NextState = BossState::NONE;

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void RifleStart();
	void RifleUpdate(float _DeltaTime);
	void RifleEnd();

	void GunStart();
	void GunUpdate(float _DeltaTime);
	void GunEnd();

	void RollStart();
	void RollUpdate(float _DeltaTime);
	void RollEnd();

	void HurtStart();
	void HurtUpdate(float _DeltaTime);
	void HurtEnd();

	void RecoverStart();
	void RecoverUpdate(float _DeltaTime);
	void RecoverEnd();

	void TransparencyStart();
	void TransparencyUpdate(float _DeltaTime);
	void TransparencyEnd();
	
	void ReAppearStart();
	void ReAppearUpdate(float _DeltaTime);
	void ReAppearEnd();

	void ChangePhaseStart();
	void ChangePhaseUpdate(float _DeltaTime);
	void ChangePhaseEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	// �ָ��Ѱ� �׳� �ٸ���� 
	void TpSweepInStart();
	void TpSweepInUpdate(float _DeltaTime);
	void TpSweepInEnd();

	void SweepStart();
	void SweepUpdate(float _DeltaTime);
	void SweepEnd();

	// �ָ��Ѱ� �׳� �ٸ���� 
	void TpSweepOutStart();
	void TpSweepOutUpdate(float _DeltaTime);
	void TpSweepOutEnd();

	void TurretSummonsStart();
	void TurretSummonsUpdate(float _DeltaTime);
	void TurretSummonsEnd();

	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	void DashEndStart();
	void DashEndUpdate(float _DeltaTime);
	void DashEndEnd();

	void TpInCeilingStart();
	void TpInCeilingUpdate(float _DeltaTime);
	void TpInCeilingEnd();

	void TpOutCeilingStart();
	void TpOutCeilingUpdate(float _DeltaTime);
	void TpOutCeilingEnd();

	void TpInRifleStart();
	void TpInRifleUpdate(float _DeltaTime);
	void TpInRifleEnd();

	void TpOutRifleStart();
	void TpOutRifleUpdate(float _DeltaTime);
	void TpOutRifleEnd();

	void TpInWallStart();
	void TpInWallUpdate(float _DeltaTime);
	void TpInWallEnd();

	void JumpRifleStart();
	void JumpRifleUpdate(float _DeltaTime);
	void JumpRifleEnd();

	void JumpRifleLandStart();
	void JumpRifleLandUpdate(float _DeltaTime);
	void JumpRifleLandEnd();
};
