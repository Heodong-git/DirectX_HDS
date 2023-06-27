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
	IDLE,			// 아이들 2
	RIFLE,			// 라이플 3
	GUN,			// 건(폭발탄) 4 
	ROLL,			// 회피(구르기) 5

	HURT,			 // 쳐맞
	RECOVER,		 // 쳐맞 후 ㅌㅌ 
	TRANSPARENCY,    // 투명 
	REAPPEAR,		 // 투명상태 이후, 재등장 스테이트, 재등장 이후, 특정시간 내로 다른 스테이트로 진입하도록 
	CHANGEPHASE,	 // 페이즈체인지, 맵에 익스플로전 이펙트생성 

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

	// 넥스트포스 체크
	void NextTransUpdate();
	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;
	const float4 m_DebugPivot = float4{ 30.0f, 42.0f };

	// 초기세팅
	void ComponentSetting();
	void LoadAndCreateAnimation();
	void LoadSound();

	// 렌더, 콜리전 
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// 사용할 이펙트 
	void CreateRifleEffect();
	std::shared_ptr<class HeadHunter_RifleEffect> m_Effect = nullptr;
	float4 m_RifleEffectPivot = float4{ 540.0f , 54.5f };

	float m_PhasePivot = -60.0f;

	// 기본스탯 
	// 총 3히트를 당하고, 카운트가 5가 되면 2페이즈로 전환, 맵을 부수는 효과를 주고, 아래로 이동한다. 
	int m_Phase1_HitCount = 3;
	int m_Phase2_HitCount = 4;
	float m_RollSpeed = 500.0f;
	bool m_Dir = false;

	// true = 오른쪽, false = 왼쪽 
	void DirCheck();
	void ChangeDir();

	float m_Ratio = 0.0f;
	// 히트되었을때 포물선로직을 사용하기 위한 변수
	float4 m_HitPos = {};
	float4 m_HitEndPos = {};
	float4 m_MiddlePos = {};
	float4 m_MainPos = {}; 

	// 몬스터 소환 위치
	std::vector<float4> m_SummonsPoss = std::vector<float4>();

	// 소환될 몬스터를 저장해둘 vector 
	// 어차피 지우는건 한번에 지우고 클리어 시킬꺼니까 벡터가 맞다.
	std::vector<std::shared_ptr<BaseActor>> m_SummonsMonsters = std::vector<std::shared_ptr<BaseActor>>();

	// 마인을 저장할 벡터, 
	std::vector<std::shared_ptr<class Remote_Mine>> m_Mines = std::vector<std::shared_ptr<class Remote_Mine>>();

	float m_IdleDuration = 0.25f;

	// 4초뒤에 
	float m_TransDuration = 3.0f;


	// 현재 페이즈 
	BossPhase m_CurPhase = BossPhase::FIRST;
	bool m_Summons = false; 
	bool m_SummonsEndCheck = false;


	size_t m_MineCount = 21;
	// 소환스킬, 
	void SummonsMonsters();

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
};
