#pragma once
#include "BaseActor.h"

// 보스 페이즈
enum class BossPhase
{
	FIRST,		// 첫번째맵
	SECOND,		// 두번째맵
};

enum class BossState
{
	NONE,
	INTRO,			// 최초 조우시 
	IDLE,			
	RIFLE,			
	GUN,			// 삭제 할수도 
	GUN_SHOT,		// 마찬가지 

	ROLL,			// 회피모션 

	JUMP,			// 추가예정

	DASH,			// 공중상태에서의 대쉬임 
	DASH_END,		// 착지하면서 칼질 

	HURT,			 // 쳐맞
	RECOVER,		 // 쳐맞 후 ㅌㅌ 

	REAPPEAR,		 // 투명상태 이후, 재등장 스테이트, 재등장 이후, 특정시간 내로 다른 스테이트로 진입하도록 
	TRANSPARENCY,    // 투명 특정패턴 사용시 진입 

	// 레이저, 라이플패턴 

	SWEEP,			// 천장에서 라이플 180도돌리기 
	
	TELEPORTIN_CEILING,			// 천장진입 
	TELEPORTOUT_CEILING,
	TELEPORTIN_SWEEP,			// 라이플회전모션진입
	TELEPORTOUT_SWEEP,
	TELEPORTIN_RIFLE,			// 순간이동라이플모션진입
	TELEPORTOUT_RIFLE,
	TELEPORTIN_WALL,			// 벽 순간이동 

	JUMP_RIFLE,					// 회전 발사 이펙트 추가예정
	JUMP_RIFLE_LAND,

	CHANGEPHASE,				// 페이즈체인지, 맵에 익스플로전 이펙트생성 
	TURRET_SUMMONS,				// 터렛 소환

	MORIBUND,					// 빈사상태 
	NOHEAD,						// 이건 안만들수도

	RECORDING_PROGRESS,
	MAX,
};


// 설명 :
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

	// 현재스테이트반환 
	inline BossState GetCurState()
	{
		return m_CurState;
	}

	// 2페이즈의 히트카운트 반환 
	inline const int GetPhase2_HitCount()
	{
		return m_Phase2_HitCount;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// 초기세팅
	void ComponentSetting();
	void LoadAndCreateAnimation();
	void LoadSound();

	// 공중사격 관련 
	void RotaitionFireUpdate(float _DeltaTime);
	float m_RotaitionFireTime = 0.008f;
	int   m_RotaitionFireCount = 10;
	int   m_CurRotFireCount = 0;
	bool  m_RotaitionFire = false;

	// 페이즈변경
	inline void ChangePhase(BossPhase _Phase)
	{
		m_CurPhase = _Phase;
	}

	
	void SummonsSetting();
	// 지속업데이트 필요함수 
	void SummonsMonstersUpdate(float _DeltaTime);
	// 몬스터 소환 위치
	std::vector<float4> m_SummonsPoss = std::vector<float4>();
	std::vector<std::shared_ptr<BaseActor>> m_SummonsMonsters = std::vector<std::shared_ptr<BaseActor>>();

	void HitUpdate(float _DeltaTime);
	void DebugUpdate();
	void NextTransUpdate();
	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;
	const float4 m_DebugPivot = float4{ 30.0f, 42.0f };

	// 렌더, 콜리전 
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;

	// 삭제할수도 
	std::shared_ptr<class GameEngineSpritRenderer> m_HeadRender = nullptr;

	// 메인콜리전 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	// 공격콜리전 
	std::shared_ptr<class GameEngineCollision> m_AttCollision = nullptr;

	// 공격콜리전 온오프 
	void AttCollisionOn();
	void AttCollisionOff();

	// 이펙트 
	void CreateTpEffect();
	void CreateRifleEffect();
	void CreateSweepEffect();
	std::shared_ptr<class HeadHunter_RifleEffect> m_Effect = nullptr;
	std::shared_ptr<class HeadHunter_RifleEffect> m_SweepEffect = nullptr;
	float4 m_RifleEffectPivot = float4{ 540.0f , 54.5f };

	// true = 오른쪽, false = 왼쪽 
	void ChangeDir();		// 플레이어와 x축 계산해서 왼쪽,오른쪽 변경
	void DirCheck();		// 왼쪽오른쪽 구분해서 포지티브,네거티브스케일 적용

	// 리셋 
	void Reset();
	void ResetPhase();
	void ResetEffect();
	void ResetSummons();
	bool m_Dir = false;

	bool m_SetMine = false;
	// 마인을 저장할 벡터, 
	std::vector<std::shared_ptr<class Remote_Mine>> m_Mines = std::vector<std::shared_ptr<class Remote_Mine>>();
	size_t m_MineCount = 21;

	bool m_Summons = false;
	bool m_SummonsEndCheck = false;

	// 기본스탯, 1페이즈, 2페이즈의 히트카운트 
	int m_Phase1_HitCount = 3;
	int m_Phase2_HitCount = 5;
	float m_RollSpeed = 500.0f;

	float m_Ratio = 0.0f;
	
	// 히트시 베지에곡선사용에 필요한 변수  
	float4 m_HitPos = {};
	float4 m_HitEndPos = {};
	float4 m_MiddlePos = {};
	float4 m_MainPos = {}; 

	float4 m_GunShot_StandardPos = float4::Zero;

	// 마인이 전부 death 상태이고, 플레이어가 살아있다면 
	// 플레이어를 강제로 forcefall 상태로 변경한다. 
	bool PlayerLiveCheck();

	float m_IdleDuration = 0.25f;
	float m_TransDuration = 3.0f;
	float m_TurretSummons_Duration = 3.0f;
	float m_PhaseDuration = 0.0f;

	std::vector<float> m_vecFireAngle = std::vector<float>();
	size_t m_FireAngleCount = 18;
	size_t m_FireAngleCount_Reverse = 0;
	size_t m_CurFireAngleCount = 0;
	size_t m_CurFireAngleCount_Reverse = 0;
	void FireAngleInit();

	// 현재 페이즈 
	BossPhase m_CurPhase = BossPhase::FIRST;

	// world
	const float4 m_TeleportPos = float4{ -68.0f, 58.0f };
	const float4 m_DashPos = float4{ -68.0f, -205.0f };

	const float4 m_TeleportLeftWallPos = float4{ -485.0f,  -50.0f };
	const float4 m_TeleportRightWallPos = float4{ 485.0f,  -50.0f };

	// 소환스킬, 
	void SummonsMonsters();
	void CreateTurretWall();
	void CreateTurret();

	// 터렛관련
	// 터렛 소환위치, world 
	const float4 m_TurretWallPos = float4{ -491.0f , -87.0f };
	const float4 m_Turret_FirstPos = float4{ -451.0f , -127.0f };
	const float4 m_Turret_SecondPos = float4{ -451.0f, -27.0f };

	bool m_IsTurretSummons = false;

	std::shared_ptr<class Turret_Wall> m_TurretWall = nullptr;
	std::shared_ptr<class Turret> m_Turret_First = nullptr;
	std::shared_ptr<class Turret> m_Turret_Second = nullptr;
	
	// 천장레이저 
	bool m_IsDoubleSweep = false;
	const float m_SweepRotSpeed = 13.0f;
	std::vector<float4> m_vecCeilingPos = std::vector<float4>();
	void CeilingPointInit();
	const float4& CeilingPointShuffle();

	bool m_TpInStart = false;
	size_t m_TpCount = 0;
	float4 m_TpCeilingPos = float4{ 0.0f, 0.0f };

	float4 m_TpRifleLeftPos = float4{ 394.0f, -263.0f , };
	float4 m_TpRifleRightPos = float4{ -418.0f , -263.0f };

	// --------------------------------------- state -----------------------------------------
	// 상태값 변경
	void ChangeState(BossState _State);
	// 현재 상태값에 따른 업데이트 
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

	void GunShotStart();
	void GunShotUpdate(float _DeltaTime);
	void GunShotEnd();

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

	// 애매한건 그냥 다만들어 
	void TpSweepInStart();
	void TpSweepInUpdate(float _DeltaTime);
	void TpSweepInEnd();

	void SweepStart();
	void SweepUpdate(float _DeltaTime);
	void SweepEnd();

	// 애매한건 그냥 다만들어 
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

	void MoribundStart();
	void MoribundUpdate(float _DeltaTime);
	void MoribundEnd();

	void NoHeadStart();
	void NoHeadUpdate(float _DeltaTime);
	void NoHeadEnd();

	void RecordingProgressStart();
	void RecordingProgressUpdate(float _DeltaTime);
	void RecordingProgressEnd();
};
