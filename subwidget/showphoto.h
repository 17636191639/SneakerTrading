#ifndef SHOWPHOTO_H
#define SHOWPHOTO_H

#include <QWidget>

namespace Ui {
class ShowPhoto;
}

class ShowPhoto : public QWidget
{
    Q_OBJECT

public:
    explicit ShowPhoto(QString pathName, QWidget *parent = 0);
    ~ShowPhoto();

private:
    Ui::ShowPhoto *ui;


};

#endif // SHOWPHOTO_H
