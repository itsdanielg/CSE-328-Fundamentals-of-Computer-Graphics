#include "noise.h"
#include <math.h>

#define TABLE_SIZE				256
#define TABLE_MASK				TABLE_SIZE - 1

// PERLIN NOISE

PerlinNoise::PerlinNoise() {
	int permutationTable[TABLE_SIZE] = {
		 92, 252,  31,  44, 165, 225, 205,  49, 131, 214, 230,  55, 127, 145, 128, 203,
		  4, 247, 238,  70,  66,  84, 208, 160, 152, 174,  15, 191, 101,  81, 200, 115,
		246, 164,   5, 184, 146,  18, 206, 117, 222, 244,  32,  94, 235,  58, 171,  40,
		 96, 121,  74, 232,  22, 143, 197, 157,  10, 123, 182, 155,  93,   8, 254,  64,
		 83, 158, 130,  36, 129, 133,  95, 114, 176,  87, 213,  41, 124,  50,  45, 149,
		 38, 113,  12, 187, 106,   7, 105, 219,  71, 242,  72, 215, 156, 224,  57, 229,
		249,  73,  69, 223, 154, 144,  16, 168, 119, 211,  19, 227,  60,  86, 120, 198,
		  6, 209, 172, 204, 108, 185, 202,  61, 141, 231, 163, 167,  88, 139,  75, 102,
		107, 212, 170,  37,  91, 188,  17, 111,  78,  52, 180,  80, 190,  34,  54,  39,
		159,  14, 248,  43, 169, 193,  42, 122,  27, 173,  26, 179, 126,  79, 177, 192,
		 47, 112, 147, 245, 138,  25,  82, 189,  30, 207, 251, 210,  24, 132,  77,  29,
		 13, 125,  28, 103,   9, 100, 137, 153,  35,  11, 148,  46, 240,  99,  90, 166,
		255,  48, 110, 136, 216,  76, 116,  21, 243, 134, 151, 140, 199, 233, 250, 196,
		 20,  62, 226, 186, 162,  59, 241, 218, 253,  85,  56, 236, 161, 175,   3, 195,
		 89, 194, 109, 104,  67,  63, 150, 118,  98, 228,  23, 178, 142,   2, 183,  97,
		217,  51, 221, 201, 135, 237,  53,  68,   1, 234, 181, 239,  33, 220,  65, 143
	};
}

float PerlinNoise::computeNoise(float x, float y, float z) {
	int newX, newY, newZ, hashA, hashAA, hashAB, hashB, hashBA, hashBB;
	float fadeX, fadeY, fadeZ;
	newX = (int)floor(x) & TABLE_MASK;
	newY = (int)floor(y) & TABLE_MASK;
	newZ = (int)floor(z) & TABLE_MASK;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	fadeX = fade(x);
	fadeY = fade(y);
	fadeZ = fade(z);
	hashA = permutationTable[newX] + newY;
	hashAA = permutationTable[hashA] + newZ;
	hashAB = permutationTable[hashA+1] + newZ;
	hashB = permutationTable[newX+1] + newY;
	hashBA = permutationTable[hashB] + newZ;
	hashBB = permutationTable[hashB+1] + newZ;
	return lerp(fadeZ,	lerp(fadeY, lerp(fadeX,	grad(permutationTable[hashAA  ], x  , y  , z   ),
												grad(permutationTable[hashBA  ], x-1, y  , z   )),
									lerp(fadeX, grad(permutationTable[hashAB  ], x  , y-1, z   ),
												grad(permutationTable[hashBB  ], x-1, y-1, z   ))),
						lerp(fadeY, lerp(fadeX, grad(permutationTable[hashAA+1], x  , y  , z-1 ),
												grad(permutationTable[hashBA+1], x-1, y  , z-1 )),
									lerp(fadeX, grad(permutationTable[hashAB+1], x  , y-1, z-1 ),
												grad(permutationTable[hashBB+1], x-1, y-1, z-1 ))));
}

float PerlinNoise::computeNoise(float x, float y) {
	return computeNoise(x, y, 0.0);
}

float PerlinNoise::computeNoise(float x) {
	return computeNoise(x, 0.0, 0.0);
}

void PerlinNoise::copyPerm() {
	int i;
	for (i = 0; i < TABLE_SIZE ; i++) {
		newPermutationTable[TABLE_SIZE+i] = newPermutationTable[i] = permutationTable[i]; 
	}
}

float PerlinNoise::fade(float t) {
	return t * t * t * (t * (6 * t - 15) + 10);
}

float PerlinNoise::lerp(float t, float a, float b) {
	return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y, float z) {
	int h;
	float u, v, returnVal;
	h = hash & 15;
	if (h < 8) {
		u = x;
	}
	else {
		u = y;
	}
	if (h < 4) {
		v = y;
	}
	else {
		if (h == 12 || h == 14) {
			v = x;
		}
		else {
			v = z;
		}
	}
	if ((h & 1) == 0) {
		returnVal = u;
	}
	else { 
		returnVal = -u;
	}
	if ((h & 2) == 0) {
		returnVal += v;
	}
	else { 
		returnVal += -v;
	}
	return returnVal;
}