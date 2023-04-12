#pragma once
#include "GameEngineResource.h"

// 설명 :
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

	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	// Lod라는 개념이 있는데
	// 레벨 오브 디테일이라는 개념으로 버텍스버퍼 + 인덱스버퍼(매쉬)를 단계에 따라서 n개 만든다
	// 5개 만들었다고 치고
	// 100개
	// 1000개
	// 4000개
	// 8000개
	// 10000개
	// 캐릭터가 멀리 있어서 자세히 봎
	// void HullShader(); 버텍스를 쪼개기 위한 표시를 새기고
	// void Tessellator(); 쪼갠다.
	// 
	// 
	// void DomainShader(); 입자처리
	// void GeometryShaeder(); 버텍스 생성.
	//                         인스턴싱

	// 이건 진짜 미친듯이 중요합니다.
	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	void SetVertexBuffer(const std::string_view& _Value);

protected:

private:
	std::shared_ptr<class GameEngineVertexBuffer> VertexBuffer;

};

