#include "showphoto.h"
#include "ui_showphoto.h"

ShowPhoto::ShowPhoto(QString pathName = "", QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowPhoto)
{
    ui->setupUi(this);
    QImage img(pathName);

    ui->label->setPixmap(QPixmap::fromImage(img));

}

ShowPhoto::~ShowPhoto()
{
    delete ui;
}
