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

	void SetVertexBuffer(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);

	// ������������ �ʸ�弼��
	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		FILL_MODE = _Value;
	}

	void Render();

protected:

private:
	// �� ������ ���� ���� �غ�
	void InputAssembler1();
	// ������ ���� ����, ������ 3D�� �ԷµǾ� �ִ� ��ǥ�� 2D�� ��ȯ�ϴ� �۾�
	// ��ǲ����� �ܰ迡�� ��µǴ� ������Ƽ�꿡 ���� ���� 
	void VertexShader();
	// ������ ������ ���� � ������ �׸��� ���ϰ� �����Ѵ�. 
	void InputAssembler2();

	// ������� ������Ʈ�����̴� ������ lod (�������������) �� ���õ� �������� �� ������Ʈ������ ��� ����
	void HullShader();
	void Tessellator();
	void DomainShader();
	void GeometryShaeder();

	// ***�߿� 
	// �������� w������, ī�޶������ ����� pixel �߶󳻱�, viewport ����, ��� �ȼ��鿡 ���� pixelshader ȣ��
	void Rasterizer();
	// �� pixel�� ������ ����, pixel ��µ����͸� ������ ��µ� ������ �����Ѵ�.
	void PixelShader();
	// pixel ���̴����� ��µ� pixel ���� ����Ÿ�ٿ� �׸��� �۾��� �����Ѵ�. 
	void OutputMerger();

	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// ������ ���������ο��� ����� �����͸� �����Ѵ�. 
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;

};

