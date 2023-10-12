#pragma once

#include <ml_mesh_type.h>

struct Settings {
    float simRatio{};
    unsigned int targetFaceNum{};

    Settings() : simRatio(0.0f), targetFaceNum(0) {}
};

class MeshSimplifier {
   public:
    MeshSimplifier();

    void QemSimplify(CMeshO &mesh);

    void SetSettings(Settings conf) { settings_ = conf; }

    Settings &GetSettings() { return settings_; }

   private:
    void simMesh(CMeshO &mesh);

    void beginMakeSure(CMeshO &mesh);

    void endMakeSure(CMeshO &mesh);

   private:
    Settings settings_;
};
