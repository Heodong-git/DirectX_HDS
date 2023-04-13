#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// Ό³Έν :
class GameEngineIndexBuffer : public GameEngineResource<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete Function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

	template<typename IndexType>
	static void Create(const std::string_view& _Name, const std::vector<IndexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResource::Create(_Name);

		Res->Create(&_Vertexs[0], sizeof(IndexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

protected:

private:
	void Create(const void* _Data, UINT _IndexSize, UINT _IndexCount);

	DXGI_FORMAT Format;

	UINT Offset;
	UINT IndexSize;
	UINT IndexCount;
	UINT VertexCount;
};

