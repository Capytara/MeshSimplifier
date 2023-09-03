#pragma once

#include <ml_mesh_type.h>

class MeshSimplifier {
public:
    /**
 * \class Settings
 * \brief 简化参数设置
 */
    struct Settings {
        float simRatio{};              //简化比例
        unsigned int targetFaceNum{};  //简化目标

        Settings() : simRatio(0.0f), targetFaceNum(0) {}
    };

public:
    MeshSimplifier();

    //简化
    void QemSimplify(CMeshO &mesh);

    //设置简化参数
    void SetSettings(Settings conf) { settings_ = conf; }

    //获得简化参数
    Settings &GetSettings() { return settings_; }

private:
    void simMesh(CMeshO &mesh);

    void beginMakeSure(CMeshO &mesh);

    void endMakeSure(CMeshO &mesh);

private:
    Settings settings_;


};

