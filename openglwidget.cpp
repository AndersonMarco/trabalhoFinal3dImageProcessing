#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{


    vboIndices=NULL;
    vboTextureCoordinate=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    shaderProgram=NULL;
    imgOrig=NULL;
    shaderProgramEdge=NULL;
    shaderProgramBlur=NULL;
    shaderProgramBloom=NULL;
    shaderProgramGamma=NULL;
    shaderProgramWave=NULL;
    imgFilter=NULL;
    shaderProgramFilterMask=NULL;
    shaderProgramNegativo=NULL;

    initParamOfFilters();

}
OpenGLWidget::~OpenGLWidget(){
    destroyVBOs();
    destroyShaders();
    if(imgOrig) delete imgOrig;
}
void OpenGLWidget::toggleBackgroundColor( bool changeBColor){
    makeCurrent();
    if(changeBColor)
        glClearColor(0,0,0,1);
    else
        glClearColor(1,1,1,1);

    update();
}
void OpenGLWidget::setEdgeThreshould(float edgeThreshould){
    this->edgeThreshould=edgeThreshould;
    applyFilter();
    update();
}
void OpenGLWidget::setGamma(float gamma){
    this->gamma=gamma;
    applyFilter();
    update();
}
void OpenGLWidget::setLumThresh(float lumThresh){
    this->lumThresh=lumThresh;
    applyFilter();
    update();
}
void OpenGLWidget::setWaveFrequency(float waveFrequency){
    this->waveFrequency=waveFrequency;
    applyFilter();
    update();
}
void OpenGLWidget::initParamOfFilters(){
    filter=0;
    edgeThreshould=0.2;
    gamma=0.7;
    lumThresh=0.9;
    waveFrequency=0.0;
}
void OpenGLWidget::slotFilter(int filter){
    initParamOfFilters();
    this->filter=filter;
    applyFilter();    
    update();
}
void OpenGLWidget::destroyShaders(){
    if(vertexShader)delete vertexShader;
    vertexShader=NULL;
    if(fragmentShader)delete fragmentShader;
    fragmentShader=NULL;
    if(shaderProgram){
        shaderProgram->release();
         delete shaderProgram;
         shaderProgram=NULL;
    }
    if(shaderProgramEdge){
        shaderProgramEdge->release();
        delete shaderProgramEdge;
        shaderProgramEdge=NULL;
    }
    if(shaderProgramBlur){
        shaderProgramBlur->release();
        delete shaderProgramBlur;
        shaderProgramBlur=NULL;
    }
    if(shaderProgramBloom){
        shaderProgramBloom->release();
        delete shaderProgramBloom;
        shaderProgramBloom=NULL;
    }
    if(shaderProgramGamma){
        shaderProgramGamma->release();
        delete shaderProgramGamma;
        shaderProgramGamma=NULL;
    }
    if(shaderProgramFilterMask){
        shaderProgramFilterMask->release();
        delete shaderProgramFilterMask;
        shaderProgramFilterMask=NULL;
    }
    if(shaderProgramWave){
        shaderProgramWave->release();
        delete shaderProgramWave;
        shaderProgramWave=NULL;
    }
    if(shaderProgramNegativo){
        shaderProgramNegativo->release();
        delete shaderProgramNegativo;
        shaderProgramNegativo=NULL;
    }
}
void OpenGLWidget::destroyVBOs(){
    if(vboTextureCoordinate){
        vboTextureCoordinate->release();
        delete vboTextureCoordinate;
        vboTextureCoordinate=NULL;
    }

    if(vboIndices){
        vboIndices->release();
        delete vboIndices;
        vboIndices=NULL;
    }
}
void OpenGLWidget::createShaders(){
    destroyShaders();
    QString vertexShaderFile=":/shader.vert";
    QString fragmentShaderFile=":/shader.frag";
    QString fragmentShaderFileEdge=":/edge.frag";
    QString fragmentShaderFileBlur=":/gaussianblur.frag";
    QString fragmentShaderFileBloom=":/bloom.frag";
    QString fragmentShaderFileGamma=":/gammacorrection.frag";
    QString fragmentShaderFileFilterMask=":/filtermask.frag";
    QString fragmentShaderFileWave=":/wave.frag";
    QString fragmentShaderFileNegativo=":/negativo.frag";


    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFile));
    if(!shaderProgram->link()){
        qWarning() << shaderProgram->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramEdge = new QOpenGLShaderProgram;
    shaderProgramEdge->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramEdge->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileEdge));
    if(!shaderProgramEdge->link()){
        qWarning() << shaderProgramEdge->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramBlur = new QOpenGLShaderProgram;
    shaderProgramBlur->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramBlur->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileBlur));
    if(!shaderProgramBlur->link()){
        qWarning() << shaderProgramBlur->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramBloom = new QOpenGLShaderProgram;
    shaderProgramBloom->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramBloom->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileBloom));
    if(!shaderProgramBloom->link()){
        qWarning() << shaderProgramBloom->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramGamma = new QOpenGLShaderProgram;
    shaderProgramGamma->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramGamma->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileGamma));
    if(!shaderProgramGamma->link()){
        qWarning() << shaderProgramGamma->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramFilterMask = new QOpenGLShaderProgram;
    shaderProgramFilterMask->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramFilterMask->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileFilterMask));
    if(!shaderProgramFilterMask->link()){
        qWarning() << shaderProgramFilterMask->log() << endl;
    }

    qWarning()<< "==========================================" <<endl;
    shaderProgramWave = new QOpenGLShaderProgram;
    shaderProgramWave->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramWave->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileWave));
    if(!shaderProgramWave->link()){
        qWarning() << shaderProgramWave->log() << endl;
    }
    qWarning()<< "==========================================" <<endl;
    shaderProgramNegativo = new QOpenGLShaderProgram;
    shaderProgramNegativo->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile));
    shaderProgramNegativo->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFileNegativo));
    if(!shaderProgramNegativo->link()){
        qWarning() << shaderProgramNegativo->log() << endl;
    }

}


void OpenGLWidget::createVBOs(){
    destroyVBOs();//destroy previous (GPU allocated) VBOs
    //define coordinate texture=========================================
    QVector2D *qVector2DTextureCoordinate=new QVector2D[4];
    qVector2DTextureCoordinate[3]= QVector2D(0,0);
    qVector2DTextureCoordinate[2]=QVector2D(1,0);
    qVector2DTextureCoordinate[1]=QVector2D(1,1);
    qVector2DTextureCoordinate[0]=QVector2D(0,1);
    //end===============================================================

    //transfer coordenate  texture to gpu===============================
    vboTextureCoordinate = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboTextureCoordinate->create();
    vboTextureCoordinate->bind();
    vboTextureCoordinate->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboTextureCoordinate->allocate(qVector2DTextureCoordinate , 4*sizeof(QVector2D));
    //end===============================================================

    //define face to form one square====================================
    unsigned int  *indices = new unsigned int[2*3];
    indices[0]=0; indices[1]=1; indices[2]=2;
    indices[3]=2; indices[4]=3; indices[5]=0;
    //end===============================================================
    //transfer face to gpu==============================================
    vboIndices =new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vboIndices ->create();
    vboIndices ->bind();
    vboIndices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboIndices ->allocate(indices , 2 * 3 *sizeof(unsigned int));
    //end===============================================================
    delete [] indices;
    delete qVector2DTextureCoordinate;
}

void OpenGLWidget::applyFilter(){
    if(imgOrig==NULL) return;

    int pass=1;
    if(filter==FilterAttributes::filterTypeBlur) pass=2;
    if(filter==FilterAttributes::filterTypeBloom) pass=3;

    if(imgFilter){
        delete imgFilter;
        imgFilter=NULL;
    }

    makeCurrent();


    for(int i=1;i<=pass;i++){
        QOpenGLFramebufferObject fbo(imgOrig->width(), imgOrig->height());
        fbo.bind();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glViewport(0, 0, imgOrig->width(), imgOrig->height());
        glMatrixMode(GL_PROJECTION);

        paintImg(imgOrig,imgFilter,filter,i);
        fbo.release();
        if(imgFilter) delete imgFilter;

        imgFilter= new QImage(fbo.toImage());

    }

    QOpenGLFramebufferObject::bindDefault();

}

void OpenGLWidget::slotSendImage(){
    if(imgFilter==NULL) return;
    makeCurrent();
    QOpenGLFramebufferObject fbo(imgFilter->width(), imgFilter->height());
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glViewport(0, 0, imgFilter->width(), imgFilter->height());
    glMatrixMode(GL_PROJECTION);
    fbo.bind();

    paintImg(imgFilter,NULL,0,0);
    fbo.release();
    emit signalSendImage(new QImage(fbo.toImage()));

}


void OpenGLWidget::slotRecvImage(QImage *img){
    if(imgOrig) delete imgOrig;
    imgOrig=img;
    applyFilter();
    update();
}


void OpenGLWidget::initializeGL(){
    qWarning() << "ola";
    this->createVBOs();
    this->createShaders();
    qWarning() << "end";
    initializeOpenGLFunctions();



}
void OpenGLWidget::resizeGL(int w, int h){


}
void OpenGLWidget::paintGL(){

    paintImg(imgFilter,NULL,0,0);
}
void OpenGLWidget::paintImg(QImage *img,QImage *img2,int filter,int passFilter){
    if(img==NULL) return;
    float *weights=NULL;
    QOpenGLShaderProgram * selectedShader;
    if(filter==FilterAttributes::filterTypeEdge)            selectedShader=shaderProgramEdge;
    else if(filter==FilterAttributes::filterTypeBlur)       selectedShader=shaderProgramBlur;
    else if(filter==FilterAttributes::filterTypeBloom)      selectedShader=shaderProgramBloom;
    else if(filter==FilterAttributes::filterTypeGamma)      selectedShader=shaderProgramGamma;
    else if(filter==FilterAttributes::filterTypeSharpen)    selectedShader=shaderProgramFilterMask;
    else if(filter==FilterAttributes::filterTypeUnsharpen)  selectedShader=shaderProgramFilterMask;
    else if(filter==FilterAttributes::filterTypeWave)       selectedShader=shaderProgramWave;
    else if(filter==FilterAttributes::filterTypeNegativo)   selectedShader=shaderProgramNegativo;
    else selectedShader=shaderProgram;

    //create Vertices========================================
    QVector4D *vertices =new QVector4D[4];
    vertices[0]=  QVector4D(0,0,0,1);
    vertices[1]=  QVector4D((float)img->width(),0,0,1);
    vertices[2]=  QVector4D((float)img->width(),(float)img->height(),0,1);
    vertices[3]=  QVector4D(0,(float)img->height(),0,1);
    //end====================================================

    glClear(GL_COLOR_BUFFER_BIT);

    selectedShader->bind();
    QOpenGLTexture * texture;
    if(filter== FilterAttributes::filterTypeBlur && passFilter==2) texture= new QOpenGLTexture(*img2);
    else texture= new QOpenGLTexture(*img);

    //texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
    texture->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    glUniform1i(glGetUniformLocation(selectedShader->programId(), "texture1"), 0);

    QOpenGLTexture * texture2=NULL;
    if(img2 && filter== FilterAttributes::filterTypeBloom){
        texture2= new QOpenGLTexture(*img2);
        //texture->setMagnificationFilter(QOpenGLTexture::Nearest);
        texture2->setMagnificationFilter(QOpenGLTexture::Linear);
        texture2->setMinificationFilter(QOpenGLTexture::Linear);
        texture2->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
        texture2->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);
        glActiveTexture(GL_TEXTURE1);
        texture2->bind();
        glUniform1i(glGetUniformLocation(selectedShader->programId(), "texture2"), 1);

    }


    QVector2D *resolution= new QVector2D(img->width(), img->height());
    selectedShader->setUniformValue("u_resolution",*resolution);
    if(filter==FilterAttributes::filterTypeEdge) selectedShader->setUniformValue("edgeThreshould",edgeThreshould);

    if(filter==FilterAttributes::filterTypeBlur){
        weights=MathUtil::getWeights(5);
        selectedShader->setUniformValueArray("weights",weights,5,1);
        selectedShader->setUniformValue("pass",passFilter);

    }
    if(filter==FilterAttributes::filterTypeBloom){

        weights=MathUtil::getWeights(10);
        selectedShader->setUniformValueArray("weights",weights,10,1);
        selectedShader->setUniformValue("pass",passFilter);

        selectedShader->setUniformValue("lumThresh",lumThresh);

    }
    if(filter==FilterAttributes::filterTypeGamma) selectedShader->setUniformValue("gamma",gamma);

    if(filter==FilterAttributes::filterTypeSharpen){
        float mask[9]= {-1, -1, -1,
                        -1, 16, -1,
                        -1, -1, -1};
         selectedShader->setUniformValueArray("u_kernel",mask,9,1);

    }
    if(filter==FilterAttributes::filterTypeUnsharpen){
        float mask[9]= { -1, -1, -1,
                         -1,  9, -1,
                         -1, -1, -1};
        selectedShader->setUniformValueArray("u_kernel",mask,9,1);

    }

    if(filter==FilterAttributes::filterTypeWave){
        selectedShader->setUniformValue("frequency",waveFrequency);
    }
    //tansfer vertices to gpu===========================================
    QOpenGLBuffer *vboVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboVertices ->create();
    vboVertices ->bind();
    vboVertices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboVertices ->allocate(vertices , 4 *sizeof(QVector4D));
    vboVertices->bind();//vertices is linked with a_position
    selectedShader->enableAttributeArray("a_position");//vertices is linked with a_position
    selectedShader->setAttributeBuffer("a_position",GL_FLOAT, 0,4,0);//vertices is linked with a_position
    //end===============================================================

    //coordenate  texture is linked with a_texCoord"====================
    vboTextureCoordinate->bind();
    selectedShader->enableAttributeArray("a_texCoord");
    selectedShader->setAttributeBuffer("a_texCoord",GL_FLOAT, 0,2,0);
    //end===============================================================

    vboIndices->bind();
    glDrawElements(GL_TRIANGLES,2*3,GL_UNSIGNED_INT,0);
    vboIndices->release();
    texture->release();

    if(texture2){
        texture2->release();
        delete texture2;
    }
    vboVertices->release();
    selectedShader->release();
    if(weights) delete weights;
    delete vboVertices;
    delete [] vertices;
    delete resolution;
    delete texture;

}
