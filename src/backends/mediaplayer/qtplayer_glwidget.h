/*
 * Copyright (C) 2020 ~ 2021, Deepin Technology Co., Ltd. <support@deepin.org>
 *
 * Author:     zhuyuliang <zhuyuliang@uniontech.com>
 *
 * Maintainer: zhuyuliang <zhuyuliang@uniontech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#ifndef _DMR_QTPLAYER_GLWIDGET_H
#define _DMR_QTPLAYER_GLWIDGET_H

#include <QtWidgets>
#undef Bool
#include "../../vendor/qthelper.hpp"
#include <DGuiApplicationHelper>
//DWIDGET_USE_NAMESPACE



namespace dmr {
class QtPlayerGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    friend class MpvProxy;

    explicit QtPlayerGLWidget(QWidget *parent);
    virtual ~QtPlayerGLWidget();

    /**
     * rounded clipping consumes a lot of resources, and performs bad on 4K video
     */
    void toggleRoundedClip(bool bFalse);

    void setPlaying(bool);

    void setVideoTex(QImage image);

protected:
    /**
     * @brief opengl初始化 cppcheck误报
     */
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;

    void setMiniMode(bool);

private:
    void initMember();
    void updateVbo();
    void updateVboCorners();
    void updateVboBlend();

    void updateMovieFbo();
    void updateCornerMasks();

    void setupBlendPipe();
    void setupIdlePipe();

    void prepareSplashImages();

private:

    bool m_bPlaying;                   //记录播放状态
    bool m_bInMiniMode;                //是否是最小化
    bool m_bDoRoundedClipping;         //

    QOpenGLVertexArrayObject m_vao;    //顶点数组对象
    QOpenGLBuffer m_vbo;               //顶点缓冲对象
    QOpenGLTexture *m_pDarkTex;        //深色主题背景纹理
    QOpenGLTexture *m_pLightTex;       //浅色主题背景纹理
    QOpenGLShaderProgram *m_pGlProg;

    QOpenGLVertexArrayObject m_vaoBlend;
    QOpenGLBuffer m_vboBlend;
    QOpenGLShaderProgram *m_pGlProgBlend;
    QOpenGLFramebufferObject *m_pFbo;
    QOpenGLShaderProgram *m_pGlProgBlendCorners;

    //textures for corner
    QOpenGLVertexArrayObject m_vaoCorner;
    QOpenGLTexture *m_pCornerMasks[4];
    QOpenGLBuffer m_vboCorners[4];
    QOpenGLShaderProgram *m_pGlProgCorner; //着色器程序

    QImage m_imgBgDark;                    //深色主题背景图
    QImage m_imgBgLight;                   //浅色主题背景图

    QOpenGLTexture* m_pVideoTex;
    int m_currWidth;
    int m_currHeight;
};

}

#endif /* ifndef _DMR_MPV_GLWIDGET_H */

