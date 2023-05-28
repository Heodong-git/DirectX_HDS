#pragma once
#include "BaseActor.h"

// Ό³Έν :
class GruntEffect : public BaseActor
{
public:
	// constrcuter destructer
	GruntEffect();
	~GruntEffect();

	// delete Function
	GruntEffect(const GruntEffect& _Other) = delete;
	GruntEffect(GruntEffect&& _Other) noexcept = delete;
	GruntEffect& operator=(const GruntEffect& _Other) = delete;
	GruntEffect& operator=(GruntEffect&& _Other) noexcept = delete;

protected:

private:

};
