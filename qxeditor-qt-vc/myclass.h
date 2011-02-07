#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui/QMainWindow>
#include "ui_myclass.h"

class MyClass : public QMainWindow
{
	Q_OBJECT

public:
	MyClass(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MyClass();

private:
	Ui::MyClassClass ui;
};

#endif // MYCLASS_H
