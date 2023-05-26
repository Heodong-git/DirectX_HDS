#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include "EngineContentsRenderingStruct.h"
#include <map>


// enable_shared_from_this
// shared_ptr 을 사용하여 객체를 공유하는 경우 유용하게 사용할 수 있다.
// 상속받은 클래스가 shared ptr을 사용하여 공유되는 객체를 만들때 사용된다. 
// 이 클래스를 상속받았을 경우, shared_from_this() 멤버함수를 호출하여 
// 해당 객체를 가리키는 shared_ptr을 얻을 수 있다. 
// shared_from_this() 를 호출하면 해당 객체를 가리키는 shared ptr 을 반환받는다. 
// 이는 해당 객체가 이미 shared ptr에 의해 소유되고 있어야 가능하기 때문에 
// 그렇지 않다면 std::bad_weak_ptr 이라는 예외가 발생한다. 
// 따라서 이 클래스를 사용하면 참조계수를 증가시키지 않고도 객체를 참조하는 shared ptr을 생성할 수 있다. 
// 메모리 누수를 방지하는데에 도움이 된다. 

// 애니메이션정보를 저장할 클래스 
class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	// GameEngineSpriteRenderer 클래스에서는
	// AnimationInfo 클래스 내부에 접근이 가능하다. 
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;			  // 애니메이션 정보를 가진 부모 클래스의 포인터

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;	  // 연속된 텍스쳐를 저장할 Sprite 클래스 

	bool IsEndValue = false;							  // 현재 애니메이션이 (최초로) 마지막프레임에 도달했는지를 체크할 변수

	void Reset();										  // 현재 진행되고 있는 애니메이션의 정보를 초기화

	void Update(float _DeltaTime);

	const SpriteInfo& CurSpriteInfo();					  // 현재 프레임의 스프라이트 정보 반환

	inline void PauseOn()
	{
		IsPauseValue = true;
	}

	inline void PauseOff()
	{
		IsPauseValue = false;
	}

public:
	size_t CurFrame = 0;				  // 현재프레임값
	size_t StartFrame = -1;				  // 애니메이션의 시작 프레임값
	size_t EndFrame = -1;				  // 애니메이션의 종료 프레임값
	float CurTime = 0.0f;				  // 프레임의 진행시간
	float Inter = 0.1f;					  // 프레임 사이의 간격 
	bool Loop = true;					  // 저장된 애니메이션의 반복 여부 
	bool ScaleToTexture = false;		  // 애니메이션의 크기(텍스쳐의 크기) 를 실제 저장된 텍스쳐의 크기와 동일하게 할 건지의 여부 
	bool IsPauseValue = false;			  // 애니메이션의 정지여부

	std::vector<size_t> FrameIndex = std::vector<size_t>();			// 
	std::vector<float>  FrameTime = std::vector<float>();			// 프레임당 걸리는 시간 저장 ( 프레임사이의 간격 ) 

	std::map<size_t, std::function<void()>> UpdateEventFunction;	// 업데이트 이벤트 함수를 저장할 map
	std::map<size_t, std::function<void()>> StartEventFunction;		// 프레임이 실행될 때 한번만 호출될 함수를 저장할 map 

	bool IsEnd();						  // 현재 애니메이션이 최초로 마지막 프레임에 도달했는지? , 최초 한번만 호출됨
};


// 애니메이션 함수호출시 전달될 변수들의 class 
class AnimationParameter
{
public:
	std::string_view AnimationName = "";			 // 애니메이션이름 
	std::string_view SpriteName = "";				 // 저장할 스프라이트 이름
	size_t Start = static_cast<size_t>(-1);			 // 시작 프레임값
	size_t End = static_cast<size_t>(-1);			 // 종료 프레임값
	float FrameInter = 0.1f;						 // 프레임 사이의 간격 
	bool Loop = true;								 // 애니메이션의 반복여부
	bool ScaleToTexture = false;					 // 크기를 텍스쳐와 동일하게 할건지?
	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float>  FrameTime = std::vector<float>();
};

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	// 이미지 크기대로 세팅
	void SetScaleToTexture(const std::string_view& _Name);

	// 이미지만 세팅
	void SetTexture(const std::string_view& _Name);

	// 이미지 세팅시 크기의 비율 조정
	void SetScaleRatio(float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	// 세팅되어있는 비율 반환 
	inline float GetScaleRatio() const
	{
		return ScaleRatio;
	}

	// X축 뒤집기
	void SetFlipX();
	// Y축 뒤집기
	void SetFlipY();

	// 애니메이션을 찾아온다. 
	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	// 애니메이션을 생성한다. 
	std::shared_ptr<AnimationInfo> CreateAnimation(const AnimationParameter& _Paramter);

	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	// Force 가 true 인 경우 , 현재 재생중인 애니메이션으로 변경하더라도 강제로 변경한다. 
	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

	void SetAtlasConstantBuffer();

	void SetColorConstantBuffer();

	// 애니메이션의 출력이 종료되었는지 ( 마지막 프레임에 도달 했는지 ) 
	bool IsAnimationEnd()
	{
		return CurAnimation->IsEnd();
	}

	size_t GetCurrentFrame()
	{
		return CurAnimation->FrameIndex[CurAnimation->CurFrame];
	}
	
	float4 GetAtlasData()
	{
		return AtlasData;
	}

	void SetSprite(const std::string_view& _SpriteName, size_t _Frame = 0);

	void SetFrame(size_t _Frame);

	void SetAnimPauseOn()
	{
		CurAnimation->PauseOn();
	}

	void SetAnimPauseOff()
	{
		CurAnimation->PauseOff();
	}

	ColorOption ColorOptionValue = {};

	// 애니메이션에 업데이트해야하는 함수 추가 
	void SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	// 애니메이션의 원하는 프레임에 한번만 호출되는 함수추가
	void SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	// 머지 얘는 헤더에없는데
	std::string GetTexName();

protected:

	void SpriteRenderInit();

	// 상속받은 클래스에서 사용가능하도록 
	float4 AtlasData;

private:
	void Update(float _Delta) override;

	void Render(float _Delta) override;

	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;

	std::shared_ptr<AnimationInfo> CurAnimation;

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;
	size_t Frame = -1;

	float ScaleRatio = 1.0f;

	void Start() override;
};

