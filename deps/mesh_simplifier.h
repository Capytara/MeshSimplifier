#pragma once

#include <ml_mesh_type.h>

class MeshSimplifier {
public:
    /**
 * \class Settings
 * \brief �򻯲�������
 */
    struct Settings {
        float simRatio{};              //�򻯱���
        unsigned int targetFaceNum{};  //��Ŀ��

        Settings() : simRatio(0.0f), targetFaceNum(0) {}
    };

public:
    MeshSimplifier();

    //��
    void QemSimplify(CMeshO &mesh);

    //���ü򻯲���
    void SetSettings(Settings conf) { settings_ = conf; }

    //��ü򻯲���
    Settings &GetSettings() { return settings_; }

private:
    void simMesh(CMeshO &mesh);

    void beginMakeSure(CMeshO &mesh);

    void endMakeSure(CMeshO &mesh);

private:
    Settings settings_;


};

