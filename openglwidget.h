#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QFont>

#include <QWidget>
#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector4D>
#include <QFileDialog>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include "fileoperationsfromresource.h"
#include "mathutil.h"
#include "filterattributes.h"
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:    
    explicit OpenGLWidget(QWidget *parent = 0);
    void setEdgeThreshould(float edgeThreshould);
    void setGamma(float gamma);
    void setLumThresh(float lumThresh);
    void setWaveFrequency(float waveFrequency);
    void destroyVBOs();
    void createVBOs();
    void createShaders();
    void destroyShaders();

    ~OpenGLWidget();
signals:
    void signalSendImage(QImage *img);
public slots:
    void toggleBackgroundColor( bool changeBColor);
    void slotRecvImage(QImage *img);
    void slotSendImage();
    void slotFilter(int filter);

protected:

    void initializeGL();
    void resizeGL(int width ,int height);
    void paintGL();

private:
    void applyFilter();
    void paintImg(QImage *img,QImage *img2,int filter,int passFilter);
    void initParamOfFilters();
    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;    
    QOpenGLShaderProgram *shaderProgramEdge;
    QOpenGLShaderProgram *shaderProgramBlur;
    QOpenGLShaderProgram *shaderProgramBloom;
    QOpenGLShaderProgram *shaderProgramGamma;
    QOpenGLShaderProgram *shaderProgramWave;
    QOpenGLShaderProgram *shaderProgramFilterMask;
    QOpenGLShaderProgram *shaderProgramNegativo;
    QOpenGLBuffer *vboIndices;
    QOpenGLBuffer *vboTextureCoordinate;
    QImage *imgOrig;
    QImage *imgFilter;
    int filter;
    float edgeThreshould;
    float gamma;
    float lumThresh;
    float waveFrequency;
};

#endif // OPENGLWIDGET_H
