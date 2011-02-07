#include "myclass.h"

MyClass::MyClass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

MyClass::~MyClass()
{

}
