
#include <cmath>
#include <cstdlib>

#include <limits>

#include "ml_mesh_type.h"
#include <vcg/complex/algorithms/update/position.h>
#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/complex/algorithms/update/selection.h>
#include <vcg/complex/algorithms/local_optimization.h>
#include <vcg/complex/algorithms/local_optimization/tri_edge_collapse_quadric.h>
#include <vcg/container/simple_temporary_data.h>

namespace vcg {
    namespace tri {

        typedef SimpleTempData<CMeshO::VertContainer, math::Quadric<double> > QuadricTemp;


        class QHelper {
        public:
            QHelper() {}

            static void Init() {}

            static math::Quadric<double> &Qd(CVertexO &v) { return TD()[v]; }

            static math::Quadric<double> &Qd(CVertexO *v) { return TD()[*v]; }

            static CVertexO::ScalarType W(CVertexO * /*v*/) { return 1.0; }

            static CVertexO::ScalarType W(CVertexO & /*v*/) { return 1.0; }

            static void Merge(CVertexO & /*v_dest*/, CVertexO const & /*v_del*/) {}

            static QuadricTemp *&TDp() {
                static QuadricTemp *td;
                return td;
            }

            static QuadricTemp &TD() { return *TDp(); }
        };

        typedef BasicVertexPair<CVertexO> VertexPair;

        class MyTriEdgeCollapse
                : public vcg::tri::TriEdgeCollapseQuadric<CMeshO, VertexPair, MyTriEdgeCollapse, QHelper> {
        public:
            typedef vcg::tri::TriEdgeCollapseQuadric<CMeshO, VertexPair, MyTriEdgeCollapse, QHelper> TECQ;

            inline MyTriEdgeCollapse(const VertexPair &p, int i, BaseParameterClass *pp) : TECQ(p, i, pp) {}
        };
    } // end namespace tri
} // end namepsace vcg
void QuadricSimplification(CMeshO &m, int TargetFaceNum, bool Selected, vcg::tri::TriEdgeCollapseQuadricParameter &pp);

