#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include "EngineContentsRenderingStruct.h"
#include <map>


// enable_shared_from_this
// shared_ptr �� ����Ͽ� ��ü�� �����ϴ� ��� �����ϰ� ����� �� �ִ�.
// ��ӹ��� Ŭ������ shared ptr�� ����Ͽ� �����Ǵ� ��ü�� ���鶧 ���ȴ�. 
// �� Ŭ������ ��ӹ޾��� ���, shared_from_this() ����Լ��� ȣ���Ͽ� 
// �ش� ��ü�� ����Ű�� shared_ptr�� ���� �� �ִ�. 
// shared_from_this() �� ȣ���ϸ� �ش� ��ü�� ����Ű�� shared ptr �� ��ȯ�޴´�. 
// �̴� �ش� ��ü�� �̹� shared ptr�� ���� �����ǰ� �־�� �����ϱ� ������ 
// �׷��� �ʴٸ� std::bad_weak_ptr �̶�� ���ܰ� �߻��Ѵ�. 
// ���� �� Ŭ������ ����ϸ� ��������� ������Ű�� �ʰ� ��ü�� �����ϴ� shared ptr�� ������ �� �ִ�. 
// �޸� ������ �����ϴµ��� ������ �ȴ�. 

// �ִϸ��̼������� ������ Ŭ���� 
class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	// GameEngineSpriteRenderer Ŭ����������
	// AnimationInfo Ŭ���� ���ο� ������ �����ϴ�. 
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;			  // �ִϸ��̼� ������ ���� �θ� Ŭ������ ������

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;	  // ���ӵ� �ؽ��ĸ� ������ Sprite Ŭ���� 

	bool IsEndValue = false;							  // ���� �ִϸ��̼��� (���ʷ�) �����������ӿ� �����ߴ����� üũ�� ����

	void Reset();										  // ���� ����ǰ� �ִ� �ִϸ��̼��� ������ �ʱ�ȭ

	void Update(float _DeltaTime);

	const SpriteInfo& CurSpriteInfo();					  // ���� �������� ��������Ʈ ���� ��ȯ

	inline void PauseOn()
	{
		IsPauseValue = true;
	}

	inline void PauseOff()
	{
		IsPauseValue = false;
	}

public:
	size_t CurFrame = 0;				  // ���������Ӱ�
	size_t StartFrame = -1;				  // �ִϸ��̼��� ���� �����Ӱ�
	size_t EndFrame = -1;				  // �ִϸ��̼��� ���� �����Ӱ�
	float CurTime = 0.0f;				  // �������� ����ð�
	float Inter = 0.1f;					  // ������ ������ ���� 
	bool Loop = true;					  // ����� �ִϸ��̼��� �ݺ� ���� 
	bool ScaleToTexture = false;		  // �ִϸ��̼��� ũ��(�ؽ����� ũ��) �� ���� ����� �ؽ����� ũ��� �����ϰ� �� ������ ���� 
	bool IsPauseValue = false;			  // �ִϸ��̼��� ��������

	std::vector<size_t> FrameIndex = std::vector<size_t>();			// 
	std::vector<float>  FrameTime = std::vector<float>();			// �����Ӵ� �ɸ��� �ð� ���� ( �����ӻ����� ���� ) 

	std::map<size_t, std::function<void()>> UpdateEventFunction;	// ������Ʈ �̺�Ʈ �Լ��� ������ map
	std::map<size_t, std::function<void()>> StartEventFunction;		// �������� ����� �� �ѹ��� ȣ��� �Լ��� ������ map 

	bool IsEnd();						  // ���� �ִϸ��̼��� ���ʷ� ������ �����ӿ� �����ߴ���? , ���� �ѹ��� ȣ���
};


// �ִϸ��̼� �Լ�ȣ��� ���޵� �������� class 
class AnimationParameter
{
public:
	std::string_view AnimationName = "";			 // �ִϸ��̼��̸� 
	std::string_view SpriteName = "";				 // ������ ��������Ʈ �̸�
	size_t Start = static_cast<size_t>(-1);			 // ���� �����Ӱ�
	size_t End = static_cast<size_t>(-1);			 // ���� �����Ӱ�
	float FrameInter = 0.1f;						 // ������ ������ ���� 
	bool Loop = true;								 // �ִϸ��̼��� �ݺ�����
	bool ScaleToTexture = false;					 // ũ�⸦ �ؽ��Ŀ� �����ϰ� �Ұ���?
	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float>  FrameTime = std::vector<float>();
};

// ���� :
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

	// �̹��� ũ���� ����
	void SetScaleToTexture(const std::string_view& _Name);

	// �̹����� ����
	void SetTexture(const std::string_view& _Name);

	// �̹��� ���ý� ũ���� ���� ����
	void SetScaleRatio(float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	// ���õǾ��ִ� ���� ��ȯ 
	inline float GetScaleRatio() const
	{
		return ScaleRatio;
	}

	// X�� ������
	void SetFlipX();
	// Y�� ������
	void SetFlipY();

	// �ִϸ��̼��� ã�ƿ´�. 
	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	// �ִϸ��̼��� �����Ѵ�. 
	std::shared_ptr<AnimationInfo> CreateAnimation(const AnimationParameter& _Paramter);

	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	// Force �� true �� ��� , ���� ������� �ִϸ��̼����� �����ϴ��� ������ �����Ѵ�. 
	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

	void SetAtlasConstantBuffer();

	void SetColorConstantBuffer();

	// �ִϸ��̼��� ����� ����Ǿ����� ( ������ �����ӿ� ���� �ߴ��� ) 
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

	// �ִϸ��̼ǿ� ������Ʈ�ؾ��ϴ� �Լ� �߰� 
	void SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	// �ִϸ��̼��� ���ϴ� �����ӿ� �ѹ��� ȣ��Ǵ� �Լ��߰�
	void SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	// ���� ��� ��������µ�
	std::string GetTexName();

protected:

	void SpriteRenderInit();

	// ��ӹ��� Ŭ�������� ��밡���ϵ��� 
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

