#pragma once
#include "GameEngineResource.h"

// 설명 : 임시클래스, 적응될 때 까지 사용 
class GameEngineRenderingPipeLine : public GameEngineResource<GameEngineRenderingPipeLine>
{
public:
	// constrcuter destructer
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineRenderingPipeLine> Create(const std::string_view& _Name)
	{
		std::shared_ptr<class GameEngineRenderingPipeLine> NewRes = GameEngineResource<GameEngineRenderingPipeLine>::Create(_Name);
		return NewRes;
	}

	inline  std::shared_ptr<class GameEngineVertexShader> GetVertexShader()
	{
		return VertexShaderPtr;
	}

	inline  std::shared_ptr<class GameEnginePixelShader> GetPixelShader()
	{
		return PixelShaderPtr;
	}

	/*void SetVertexBuffer(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);*/
	void SetVertexShader(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);
	void SetBlendState(const std::string_view& _Value);
	void SetDepthState(const std::string_view& _Value);

	// 파이프라인의 필모드세팅
	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		FILL_MODE = _Value;
	}

	void RenderingPipeLineSetting();
	void Render();

	std::shared_ptr<GameEngineRenderingPipeLine> Clone();

	bool IsClone()
	{
		return IsCloneValue;
	}

protected:

private:
	bool IsCloneValue = false;
	// 각 정점에 대한 정보 준비
	//void InputAssembler1();
	// 정점에 대한 연산, 가상의 3D로 입력되어 있는 좌표를 2D로 변환하는 작업
	// 1. 버텍스의 로컬좌표계를 월드좌표계로 변환
	// 2. 카메라 행렬과의 곱을 통해 카메라의 중심점에서 얼만큼 떨어져 있는지를 표현
	// 3. 프로젝션 행렬을 곱해줌으로써 원근감 부여  
	void VertexShader();
	// 정점의 정보를 토대로 어떤 순서로 그릴지 정하고 조립한다. 
	//void InputAssembler2();

	// 여기부터 지오메트리쉐이더 까지는 테셀레이션
	// lod (레벨오브디테일) 과 관련된 내용으로 현 프로젝트에서는 없어도 무관
	void HullShader();
	void Tessellator();
	void DomainShader();
	void GeometryShaeder();

	// ***중요 
	// 1. 원근투영 w나누기 
	// 2. 카메라범위를 벗어나는 pixel 잘라내기
	// 3. viewport 곱셈? 
	// 4. 모든 픽셀들에 대한 pixelshader 호출
	// 3d 오브젝트는 이 과정들을 거쳐서 모니터에 보이도록 픽셀이 되었는데, 이 과정을 래스터화 라고 한다. 
	void Rasterizer();
	// 각 pixel의 데이터 생성, pixel 출력데이터를 결합해 출력될 색상을 결정한다.
	// 조명,텍스쳐,그림자, 각종 특수효과등을 연산하게 된다. 
	void PixelShader();
	// pixel 셰이더에서 출력된 각각의 pixel 값을 렌더타겟에 그리는 작업을 수행한다. 
	void OutputMerger();

	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// 렌더링 파이프라인에서 사용할 데이터를 저장한다. 
	//std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthState> DepthStatePtr;
};

