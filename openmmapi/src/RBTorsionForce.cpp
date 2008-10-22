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

#include "Force.h"
#include "OpenMMException.h"
#include "RBTorsionForce.h"
#include "internal/RBTorsionForceImpl.h"

using namespace OpenMM;

RBTorsionForce::RBTorsionForce(int numTorsions) : rbTorsions(numTorsions) {
}

void RBTorsionForce::getTorsionParameters(int index, int& particle1, int& particle2, int& particle3, int& particle4, double& c0, double& c1, double& c2, double& c3, double& c4, double& c5) const {
    particle1 = rbTorsions[index].particle1;
    particle2 = rbTorsions[index].particle2;
    particle3 = rbTorsions[index].particle3;
    particle4 = rbTorsions[index].particle4;
    c0 = rbTorsions[index].c[0];
    c1 = rbTorsions[index].c[1];
    c2 = rbTorsions[index].c[2];
    c3 = rbTorsions[index].c[3];
    c4 = rbTorsions[index].c[4];
    c5 = rbTorsions[index].c[5];
}

void RBTorsionForce::setTorsionParameters(int index, int particle1, int particle2, int particle3, int particle4, double c0, double c1, double c2, double c3, double c4, double c5) {
    rbTorsions[index].particle1 = particle1;
    rbTorsions[index].particle2 = particle2;
    rbTorsions[index].particle3 = particle3;
    rbTorsions[index].particle4 = particle4;
    rbTorsions[index].c[0] = c0;
    rbTorsions[index].c[1] = c1;
    rbTorsions[index].c[2] = c2;
    rbTorsions[index].c[3] = c3;
    rbTorsions[index].c[4] = c4;
    rbTorsions[index].c[5] = c5;
}

ForceImpl* RBTorsionForce::createImpl() {
    return new RBTorsionForceImpl(*this);
}
