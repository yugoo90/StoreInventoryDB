#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

//#include "qboxlayout.h"
//#include "qtmetamacros.h"
#include <QDialog>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QSpinBox>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QPalette>
#include "item.h"

class AddItemDialog : public QDialog
{
    Q_OBJECT
public:
    AddItemDialog(Item*& newItem, QWidget* parent = nullptr);
    void confirmAdd();
    void loadItemImage();

signals:

private slots:

private:
    QGridLayout* grid;
    QString imageFilePath;
    QLabel *productName;
    QLabel *quantity;
    QLabel *image;
    QLabel *lblImage;
    QFont font;
    QLineEdit *nameBox;
    QSpinBox *qty;
    QPushButton *addButton;
    QPushButton *loadButton;
    QVBoxLayout *vBox1;
    QHBoxLayout *hBox1;
    QHBoxLayout *hBox2;
    QHBoxLayout *hBox3;
    QHBoxLayout *hBox4;
    QHBoxLayout *hBox5;
    Item** newItem;

};

#endif // ADDITEMDIALOG_H
