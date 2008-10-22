/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "CudaPlatform.h"
#include "CudaStreamFactory.h"
#include "CudaStreamImpl.h"
#include "OpenMMException.h"
#include "internal/OpenMMContextImpl.h"
#include "kernels/gpuTypes.h"

using namespace OpenMM;

StreamImpl* CudaStreamFactory::createStreamImpl(std::string name, int size, Stream::DataType type, const Platform& platform, OpenMMContextImpl& context) const {
    if (name == "particlePositions") {
        CudaPlatform::PlatformData& data = *static_cast<CudaPlatform::PlatformData*>(context.getPlatformData());
        float padding[] = {100000.0f, 100000.0f, 100000.0f, 0.2f};
        return new CudaStreamImpl<float4>(name, size, type, platform, data.gpu->psPosq4, 4, padding);
    }
    if (name == "particleVelocities") {
        CudaPlatform::PlatformData& data = *static_cast<CudaPlatform::PlatformData*>(context.getPlatformData());
        float padding[] = {0.0f, 0.0f, 0.0f, 0.0f};
        return new CudaStreamImpl<float4>(name, size, type, platform, data.gpu->psVelm4, 4, padding);
    }
    if (name == "particleForces") {
        CudaPlatform::PlatformData& data = *static_cast<CudaPlatform::PlatformData*>(context.getPlatformData());
        float padding[] = {0.0f, 0.0f, 0.0f, 0.0f};
        return new CudaStreamImpl<float4>(name, size, type, platform, data.gpu->psForce4, 4, padding);
    }
    switch (type) {
    case Stream::Float:
    case Stream::Double:
        return new CudaStreamImpl<float1>(name, size, type, platform, 1);
    case Stream::Float2:
    case Stream::Double2:
        return new CudaStreamImpl<float2>(name, size, type, platform, 1);
    case Stream::Float3:
    case Stream::Double3:
        return new CudaStreamImpl<float3>(name, size, type, platform, 1);
    case Stream::Float4:
    case Stream::Double4:
        return new CudaStreamImpl<float4>(name, size, type, platform, 1);
    case Stream::Integer:
        return new CudaStreamImpl<int1>(name, size, type, platform, 1);
    case Stream::Integer2:
        return new CudaStreamImpl<int2>(name, size, type, platform, 1);
    case Stream::Integer3:
        return new CudaStreamImpl<int3>(name, size, type, platform, 1);
    case Stream::Integer4:
        return new CudaStreamImpl<int4>(name, size, type, platform, 1);
    }
    throw OpenMMException("Tried to create a Stream with an illegal DataType.");
}
