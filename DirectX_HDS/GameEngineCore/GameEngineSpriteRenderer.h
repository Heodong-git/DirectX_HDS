#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include <map>

// �ִϸ��̼� ����
class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;
	std::shared_ptr<GameEngineSprite> Sprite = nullptr;

	// �ִϸ��̼��� ����� �������� true 
	bool IsEndValue = false;

	void Reset();
	void Update(float _DeltaTime);

	// ������������ �ؽ��� ��ȯ 
	std::shared_ptr<GameEngineTexture> CurFrameTexture();

public:
	size_t CurFrame = 0;		// ���� �����Ӱ� 
	size_t StartFrame = -1;		// ���� �����Ӱ�
	size_t EndFrame = -1;		// ���� �����Ӱ�
	float CurTime = 0.0f;		// 
	float Inter = 0.1f;			// 
	bool Loop = true;			// �ݺ����� 

	bool IsEnd();				// �ִϸ��̼��� ����Ǿ��ٸ� 
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

	// �ؽ����� ũ��״�� ����
	void SetScaleToTexture(const std::string_view& _Name);
	void SetTexture(const std::string_view& _Name);

	void SetFlipX();
	void SetFlipY();

	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	std::shared_ptr<AnimationInfo> CreateAnimation(const std::string_view& _Name,
		const std::string_view& _SpriteName,
		float _FrameInter = 0.1f,			   // �����Ӵ� ���� 
		int _Start = -1,
		int _End = -1,
		bool _Loop = true);

	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

protected:

private:
	void Render(float _Delta) override;

	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;

	std::shared_ptr<AnimationInfo> CurAnimation = nullptr;

	void Start() override;
};

