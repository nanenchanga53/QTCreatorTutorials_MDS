#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QExtrudedTextMesh>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Qt3DExtras::Qt3DWindow *m_view;
    //Qt3DCore::QEntity *scene;
    Qt3DCore::QEntity *m_rootEntity;

    // Camera
    Qt3DRender::QCamera *m_camera;
    // Camera controls
    Qt3DExtras::QOrbitCameraController *camController;

    Qt3DCore::QEntity *m_textEntity;

    void createRootEntry();

    QVector3D m_camPos3D;
    QVector3D m_camUpVector3D;
    QVector3D m_camViewCenter3D;

public slots:
    void setCamPosX_ValueChanged();
    void setCamPosY_ValueChanged();
    void setCamPosZ_ValueChanged();
};

#endif // WIDGET_H
