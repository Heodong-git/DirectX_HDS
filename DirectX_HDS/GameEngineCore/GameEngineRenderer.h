#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

class GameEngineRenderUnit
	: std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();

public:
	std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineMesh> Mesh;
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;
	GameEngineShaderResHelper ShaderResHelper;

	// 

public:
	void SetMesh(const std::string_view& _Name);
	void SetPipeLine(const std::string_view& _Name);
	void Render(float _DeltaTime);
};


// 설명 :
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

	// 파이프라인 세팅
	// 사용할 쉐이더, 쉐이더에서 어떤 텍스쳐를 사용할지, 샘플러, 상수버퍼는 어떤것을 사용했는지 알아야한다. 
	void SetPipeLine(const std::string_view& _Name, int _index = 0);

	// 메쉬 세팅
	void SetMesh(const std::string_view& _Name, int _index = 0);

	// 여기서 리턴된 파이프라인을 수정하면 이 파이프라인을 사용하는 모든 애들이 바뀌게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLine(int _index = 0);

	// 이걸 사용하게되면 이 랜더러의 유니트는 자신만의 클론 파이프라인을 가지게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLineClone(int _index = 0);

	inline GameEngineShaderResHelper& GetShaderResHelper(int _index = 0)
	{
		return Units[_index]->ShaderResHelper;
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

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	void RenderTransformUpdate(GameEngineCamera* _Camera);
};
