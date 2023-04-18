#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// ���� : ���������� �ȿ��� ����Ǵ� ���α׷��� ���� ���̴��� ��� ������ �����ϴµ� ���ȴ�. 
class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:

	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	// ������ ũ��, �̸�, Desc�� ���ڷ� �ް� 
	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		// ������ ũ���� ���۰� ���ٸ� ����
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			ConstantBufferRes[_Byte];
			// �� ũ���� ������۰� �������� �ʴ´�.
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		// end == ��°� �����Ͱ� ����.
		// end != ��°� �����Ͱ� �ִٴ°ǵ�??? �ƾƾƾ�
		// ���� ũ���� �����߿� �ش��ϴ� �̸����� �����Ͱ� �ִٸ� �༮�� ��ȯ�ϰ�
		// ���ٸ� �����Ͽ� �߰��� ��, �� �����͸� ��ȯ�Ѵ�. �̰ű��� 
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			return ConstantBufferRes[_Byte][UpperName];
		}

		// �����Ͱ� ���ٸ� ���۸� ���� �� 
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed();
		// ���ڷ� ���� string �� Ű������ �Ͽ� ���� �� 
		ConstantBufferRes[_Byte][UpperName] = Buffer;
		// ���ҽ�����
		Buffer->ResCreate(_BufferDesc);
		// ���۹�ȯ
		return Buffer;
	}

	static void ResourcesClear();

protected:
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc);

private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;
};

