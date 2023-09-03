
#include <vcg/complex/algorithms/clean.h>

#include "quadric_simp.h"

#include "mesh_simplifier.h"


bool simCallBackPos(const int pos, const char *str) {
    if (pos == 1)
        std::cout << str << std::endl;
    else
        std::cout << "\r\t" << str << pos << "%";
    return true;
}

MeshSimplifier::MeshSimplifier() = default;

void MeshSimplifier::QemSimplify(CMeshO &mesh) {
    if (mesh.face.empty()) return;

    simMesh(mesh);
}

void MeshSimplifier::simMesh(CMeshO &mesh) {
    beginMakeSure(mesh);

    int TargetFaceNum = settings_.targetFaceNum;
    if (settings_.simRatio != 0.0f) TargetFaceNum = mesh.fn * settings_.simRatio;

    vcg::tri::TriEdgeCollapseQuadricParameter pp;

    QuadricSimplification(mesh, TargetFaceNum, false, pp);

}

void MeshSimplifier::beginMakeSure(CMeshO &mesh) {
    mesh.vert.EnableVFAdjacency();
    mesh.face.EnableVFAdjacency();
    vcg::tri::UpdateTopology<CMeshO>::VertexFace(mesh);
    mesh.vert.EnableMark();
    vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromVF(mesh);
}

void MeshSimplifier::endMakeSure(CMeshO &mesh) {
    vcg::tri::UpdateBounding<CMeshO>::Box(mesh);
    if (mesh.fn > 0) {
        vcg::tri::UpdateNormal<CMeshO>::PerFaceNormalized(mesh);
        vcg::tri::UpdateNormal<CMeshO>::PerVertexAngleWeighted(mesh);
    }
    vcg::tri::UpdateNormal<CMeshO>::NormalizePerFace(mesh);
    vcg::tri::UpdateNormal<CMeshO>::PerVertexFromCurrentFaceNormal(mesh);
    vcg::tri::UpdateNormal<CMeshO>::NormalizePerVertex(mesh);
}