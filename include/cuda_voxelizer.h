#pragma once
// Trimesh for model importing
#include "TriMesh.h"
#include "cuda.h"
#include "cuda_runtime.h"

namespace CudaVoxelizer {
	// Returns vtable of the voxels
	extern "C" __declspec(dllexport) unsigned int *VoxelizeMesh(trimesh::TriMesh* themesh, int gridsize, bool forceCPU, bool solidVoxelization, std::string outputLocation = "");

	// Check if a voxel in the voxel table is set
	extern "C" __declspec(dllexport) __host__ __device__ inline bool checkVoxel(size_t x, size_t y, size_t z, const int gridsize, const unsigned int* vtable) {
		size_t location = x + (y * gridsize) + (z * gridsize * gridsize);
		size_t int_location = location / size_t(32);

		unsigned int bit_pos = size_t(31) - (location % size_t(32)); // we count bit positions RtL, but array indices LtR
		if ((vtable[int_location]) & (1 << bit_pos)) {
			return true;
		}
		return false;
	}
}
