#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// ���� :
class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
	friend class GameEngineRenderUnit;

public:
	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _Name, const std::string_view& _VtxName, const std::string_view& _IdxName)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResource::Create(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if ((nullptr == Res->VertexBufferPtr) || (nullptr == Res->IndexBufferPtr))
		{
			MsgAssert("�Ž��� ����µ� �����߽��ϴ�.");
		}

		return Res;
	}

	std::shared_ptr<GameEngineVertexBuffer> GetVertexBuffer()
	{
		return VertexBufferPtr;
	}

	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _TOPOLOGY)
	{
		TOPOLOGY = _TOPOLOGY;
	}

	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

protected:
	void Setting() override;

	void InputAssembler1();
	void InputAssembler2();

private:
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<GameEngineIndexBuffer> IndexBufferPtr;
};


// ����Ʈ���� ������
// Vertexs <-- ����, �Ǵ� ��ġ�� �ǹ��ϴ� ���� 
// �簢���� �׸��ٰ� ġ�� 4���� ���� ǥ���Ѵٰ� �� �� ��..��? 

// ������ ���ؽ��� ��ġ�� ���ð����̶�� �Ѵ�. 
// ��κ��� ��� �޽��� 1ũ��� �ؼ� ���� �� �ֵ��� �����. �ƴѰ��� ���� 

// �޽� ȸ����Ű��
// Angle * �� <--- ȸ���ӵ�(?) 
// �غ��ؾ��� �� 
// 1. �޽��� �� ���ؽ�
// 2. ���ؽ��� ������ POINT �迭 <-- �׸��� �Լ��� �ʿ�, ��ġ�� ����ȯ�Ͽ� ����
// 3. ũ��, ����, �̵����� ���� <-- �ϱ����� ������ ������
// 4. ����Ʈ�迭�� �־��ְ� Polygon <--- �Լ��� �׷��ش�. 
// ���� ���ؽ��� �� 1�� ũ�� (0.5,0.5) �� �����ϰ� * Scale �� ũ�⸦ �÷��ش�. 
// ���ȸ�� ������ �ƴ����� ��κ��� �׷���. 
// ũ��, ����, �̵� //////     ����, �θ��� ..? ������
// �޽��� �̵���Ű�� ���� �����ϴ� ������ ���ð���(���ý����̽�) 
// �̵� ��Ų �� ��µǾ� �������� ������ �������(���彺���̽�) ��� �մϴ�. 
