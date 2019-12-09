#pragma once

#ifndef NOISE_H
#define NOISE_H

#define TABLE_SIZE				256
#define TABLE_MASK				TABLE_SIZE - 1

class PerlinNoise {

public:

	PerlinNoise();
	float computeNoise(float x, float y, float z);
	float computeNoise(float x, float y);
	float computeNoise(float x);

private:

	int permutationTable[TABLE_SIZE];
	int newPermutationTable[TABLE_SIZE * 2];

	void copyPerm();
	float fade(float t);
	float lerp(float t, float a, float b);
	float grad(int hash, float x, float y, float z);

};

#endif