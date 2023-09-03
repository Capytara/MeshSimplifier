#include <iostream>

#include <Eigen/Core>
#include <mesh_simplifier.h>
#include <ml_mesh_type.h>

#include <igl/writeOBJ.h>
#include <igl/readOBJ.h>

void QemSimplify(Eigen::MatrixXd &verts, Eigen::MatrixXi &faces,
                            int target_faces_count) {
    CMeshO mesh;
    auto vi = vcg::tri::Allocator<CMeshO>::AddVertices(mesh, verts.rows());
    std::vector<CMeshO::VertexPointer> verts_pointers(verts.rows());

    for (int i = 0; i < verts.rows(); ++i) {
        verts_pointers.at(i) = &*vi;
        for (int j = 0; j < 3; ++j) {
            verts_pointers.at(i)->P()[j] = verts(i, j);
        }
        ++vi;
    }

    auto fi = vcg::tri::Allocator<CMeshO>::AddFaces(mesh, faces.rows());

    for (int i = 0; i < faces.rows(); ++i) {
        for (int j = 0; j < 3; ++j) {
            (*fi).V(j) = verts_pointers.at(faces(i, j));
        }
        ++fi;
    }

    MeshSimplifier::Settings conf;
    conf.targetFaceNum = target_faces_count;

    MeshSimplifier mesh_sim;
    mesh_sim.SetSettings(conf);
    mesh_sim.QemSimplify(mesh);

    verts.resize(mesh.VN(), 3);
    faces.resize(mesh.FN(), 3);

    int v_idx = 0;
    for (auto & vii : mesh.vert) {
        if (!vii.IsD()) {
            verts.row(v_idx) = Eigen::Vector3d{vii.P()[0], vii.P()[1], vii.P()[2]};
            ++v_idx;
        }
    }

    int vert_idx = 0;
    std::vector<int> VertexId(mesh.vert.size());
    for (auto vii = mesh.vert.begin(); vii != mesh.vert.end(); ++vii) {
        if (!(*vii).IsD()) {
            VertexId[vii - mesh.vert.begin()] = vert_idx;
            vert_idx++;
        }
    }

    int face_idx{};
    for (int i = 0; i < mesh.face.size(); ++i) {
        if (mesh.face.at(i).IsD()) continue;
        for (int j = 0; j < 3; ++j) {
            int index = VertexId[vcg::tri::Index(mesh, mesh.face.at(i).V(j))];
            faces(face_idx, j) = index;
        }
        ++face_idx;
    }
}

int main() {
    Eigen::MatrixXd verts;
    Eigen::MatrixXi faces;

    std::string input_model_path{R"()"};
    std::string output_model_path{R"()"};
    int target_faces_count{1000}; // 简化后的面数

    igl::readOBJ(input_model_path, verts, faces);
    QemSimplify(verts, faces, target_faces_count);
    igl::writeOBJ(output_model_path, verts, faces);

    return 0;
}
