#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// ���� �������� ���� ������� ����� �� Ŭ������ �̰�
class GameEngineRenderUnit
{
public:
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe;
	GameEngineShaderResHelper ShaderResHelper;

public:
	void SetPipeLine(const std::string_view& _Name);
	void Render(float _DeltaTime);
};

// ���� :
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// ���������� ����
	// ����� ���̴�, ���̴����� � �ؽ��ĸ� �������, ���÷�, ������۴� ����� ����ߴ��� �˾ƾ��Ѵ�. 
	void SetPipeLine(const std::string_view& _Name);

	inline GameEngineShaderResHelper& GetShaderResHelper()
	{
		return ShaderResHelper;
	}

	void CameraCullingOn()
	{
		IsCameraCulling = true;
	}

	// Z sort 
	void CalSortZ(class GameEngineCamera* _Camera);

protected:
	void Start();
	void Render(float _Delta) override;
	void PushCameraRender(int _CameraOrder);

private:
	bool IsCameraCulling = false;

	float CalZ = 0.0f;

	// ���������ΰ� ���̴����ҽ����۰� �������� �������� �Ǵ� ������� ����
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe = nullptr;
	GameEngineShaderResHelper ShaderResHelper;

	void RenderTransformUpdate(GameEngineCamera* _Camera);
};
