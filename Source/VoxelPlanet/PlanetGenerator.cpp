// Copyright Epic Games, Inc. All Rights Reserved.

// Copyright 2021 Phyronnaz

#if 1

#include "PlanetGenerator.h"
#include "FastNoise/VoxelFastNoise.inl"
#include "VoxelMaterialBuilder.h"


TVoxelSharedRef<FVoxelGeneratorInstance> UPlanetGenerator::GetInstance()
{
	return MakeVoxelShared<FPlanetGeneratorInstance>(*this);
}

///////////////////////////////////////////////////////////////////////////////

FPlanetGeneratorInstance::FPlanetGeneratorInstance(const UPlanetGenerator& MyGenerator)
	: Super(&MyGenerator)
	, NoiseHeight(MyGenerator.NoiseHeight)
	, Seed(MyGenerator.Seed)
{
}

void FPlanetGeneratorInstance::Init(const FVoxelGeneratorInit& InitStruct)
{
	Noise.SetSeed(Seed);
}

v_flt FPlanetGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
#if 1
	// Radius of the world
	const float Radius = 100.f;

	// Normalize the position to get the 3D noise sample position
	const FVector SamplePosition = FVector(X, Y, Z).GetSafeNormal();

	// Compute noise. Note that the noise has a much higher frequency since the sample position is normalized
	const float Height = Radius + Noise.GetPerlin_3D(SamplePosition.X, SamplePosition.Y, SamplePosition.Z, 1.f) * NoiseHeight;

	// Value = DistanceFromCenter - Height
	float Value = FVector(X, Y, Z).Size() - Height;

	// Smoother gradient
	Value /= 5;

#else //flat terrain
	const float Height = Noise.GetPerlin_2D(X, Y, 0.01f) * NoiseHeight;

	// Positive value -> empty voxel
	// Negative value -> full voxel
	// Value positive when Z > Height, and negative Z < Height
	float Value = Z - Height;

	// The voxel value is clamped between -1 and 1. That can result in a bad gradient/normal. To solve that we divide it
	Value /= 5;
#endif

	return Value;
}

FVoxelMaterial FPlanetGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	FVoxelMaterialBuilder Builder;

	// RGB
	Builder.SetMaterialConfig(EVoxelMaterialConfig::RGB);
	Builder.SetColor(FColor::Red);

	// Single index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	//Builder.SetSingleIndex(0); 

	// Multi index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::MultiIndex);
	//Builder.AddMultiIndex(0, 0.5f);
	//Builder.AddMultiIndex(1, 0.5f);

	return Builder.Build();
}

TVoxelRange<v_flt> FPlanetGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const
{
	// Return the values that GetValueImpl can return in Bounds
	// Used to skip chunks where the value does not change
	// Be careful, if wrong your world will have holes!
	// By default return infinite range to be safe
	return TVoxelRange<v_flt>::Infinite();

	// Example for the GetValueImpl above

	// Noise is between -1 and 1
	const TVoxelRange<v_flt> Height = TVoxelRange<v_flt>(-1, 1) * NoiseHeight;

	// Z can go from min to max
	TVoxelRange<v_flt> Value = TVoxelRange<v_flt>(Bounds.Min.Z, Bounds.Max.Z) - Height;

	Value /= 5;

	return Value;
}

FVector FPlanetGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}

#endif