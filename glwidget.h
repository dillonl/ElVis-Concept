#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>

class GLWidget : QGLWidget
{
	Q_OBJECT
public:
	GLWidget(QObject* parent=0);
	~GLWidget();
};

#endif // GLWIDGET_H
