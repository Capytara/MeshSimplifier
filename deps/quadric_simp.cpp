
#include "ml_mesh_type.h"
#include "quadric_simp.h"

using namespace vcg;
using namespace std;

void QuadricSimplification(CMeshO &m, int TargetFaceNum, bool Selected, tri::TriEdgeCollapseQuadricParameter &pp) {
    math::Quadric<double> QZero;
    QZero.SetZero();
    tri::QuadricTemp TD(m.vert, QZero);
    tri::QHelper::TDp() = &TD;

    if (pp.PreserveBoundary && !Selected) {
        pp.FastPreserveBoundary = true;
        pp.PreserveBoundary = false;
    }

    if (pp.NormalCheck) pp.NormalThrRad = M_PI / 4.0;

    vcg::LocalOptimization<CMeshO> DeciSession(m, &pp);

    DeciSession.Init<tri::MyTriEdgeCollapse>();

    DeciSession.SetTargetSimplices(TargetFaceNum);
    DeciSession.SetTimeBudget(0.05f); 
    int faceToDel = m.fn - TargetFaceNum;
    while (DeciSession.DoOptimization() && m.fn > TargetFaceNum) {}

    DeciSession.Finalize<tri::MyTriEdgeCollapse>();
}
