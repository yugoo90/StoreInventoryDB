#ifndef UPDATEITEMDIALOG_H
#define UPDATEITEMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "item.h"


class UpdateItemDialog : public QDialog
{
    Q_OBJECT
public:
    UpdateItemDialog(Item *currentItem, QWidget *parent = nullptr);
    ~UpdateItemDialog();

    void confirmUpdate();
    void loadItemImage();

private:
    QFont font;
    QLabel *itemName;
    QLabel *qty;
    QLabel *itemImage;
    QSpinBox *quantity;
    QLabel *lblImage;
    QPushButton *ldImg;
    QPushButton *editBtn;
    QPixmap pixmap;
    QHBoxLayout *hBox1;
    QHBoxLayout *hBox2;
    QHBoxLayout *hBox3;
    QHBoxLayout *hBox4;
    QVBoxLayout *vBox1;
    QVBoxLayout *vBox2;


    Item *currentItem;
    QString imageFilePath;
};

#endif // UPDATEITEMDIALOG_H
