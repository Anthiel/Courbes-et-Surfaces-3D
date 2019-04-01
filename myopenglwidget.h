#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "courbeparametrique.h"

class myOpenGLWidget : public QOpenGLWidget,
			   protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit myOpenGLWidget(QWidget *parent = nullptr);
	~myOpenGLWidget();

public slots:

signals:  // On ne les implémente pas, elles seront générées par MOC ;
		  // les paramètres seront passés aux slots connectés.

protected slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void doProjection();
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *ev) override;
	void keyReleaseEvent(QKeyEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

private:
    double m_angleX = 0, m_angleY = 0, m_angleZ = 0;
    double m_x=0, m_y=0, m_z=0;
	QTimer *m_timer = nullptr;
	double m_ratio = 1;

    float dx=0,dy=0,dz=0;

    Point controlPoints[16];
    Point *E,*F,*G;
    CourbeParametrique *C1;
    int numPoint=0;

    bool editing=false,edited=true,firstDraw=true;

	//RR matrices utiles
	QMatrix4x4 m_modelView;
	QMatrix4x4 m_projection;
	QMatrix4x4 m_model;

	QOpenGLShaderProgram *m_program;
	QOpenGLBuffer m_vbo;

	void makeGLObjects();
	void tearGLObjects();

private slots:
    void setPasHomogene(int value);
    void setU(double value);
    void setV(double value);

    void translateForward();
    void translateLeft();
    void translateRight();
    void translateBackward();

    void rotateForward();
    void rotateLeft();
    void rotateRight();
    void rotateBackward();

    void reset();
    void editMode();

    void previousPoint();
    void nextPoint();
};


#endif // MYOPENGLWIDGET_H
