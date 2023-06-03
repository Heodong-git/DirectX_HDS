#pragma once
#include "GameEngineResource.h"

// ���� : �ӽ�Ŭ����, ������ �� ���� ��� 
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

	// ������������ �ʸ�弼��
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
	// �� ������ ���� ���� �غ�
	//void InputAssembler1();
	// ������ ���� ����, ������ 3D�� �ԷµǾ� �ִ� ��ǥ�� 2D�� ��ȯ�ϴ� �۾�
	// 1. ���ؽ��� ������ǥ�踦 ������ǥ��� ��ȯ
	// 2. ī�޶� ��İ��� ���� ���� ī�޶��� �߽������� ��ŭ ������ �ִ����� ǥ��
	// 3. �������� ����� ���������ν� ���ٰ� �ο�  
	void VertexShader();
	// ������ ������ ���� � ������ �׸��� ���ϰ� �����Ѵ�. 
	//void InputAssembler2();

	// ������� ������Ʈ�����̴� ������ �׼����̼�
	// lod (�������������) �� ���õ� �������� �� ������Ʈ������ ��� ����
	void HullShader();
	void Tessellator();
	void DomainShader();
	void GeometryShaeder();

	// ***�߿� 
	// 1. �������� w������ 
	// 2. ī�޶������ ����� pixel �߶󳻱�
	// 3. viewport ����? 
	// 4. ��� �ȼ��鿡 ���� pixelshader ȣ��
	// 3d ������Ʈ�� �� �������� ���ļ� ����Ϳ� ���̵��� �ȼ��� �Ǿ��µ�, �� ������ ������ȭ ��� �Ѵ�. 
	void Rasterizer();
	// �� pixel�� ������ ����, pixel ��µ����͸� ������ ��µ� ������ �����Ѵ�.
	// ����,�ؽ���,�׸���, ���� Ư��ȿ������ �����ϰ� �ȴ�. 
	void PixelShader();
	// pixel ���̴����� ��µ� ������ pixel ���� ����Ÿ�ٿ� �׸��� �۾��� �����Ѵ�. 
	void OutputMerger();

	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// ������ ���������ο��� ����� �����͸� �����Ѵ�. 
	//std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthState> DepthStatePtr;
};

