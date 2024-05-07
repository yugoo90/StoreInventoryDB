#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include "item.h"
#include "additemdialog.h"
#include "updateitemdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFont font;
    QGridLayout* grid;
    QListWidget *list;
    QLabel *quantity;
    QLabel *product;
    QLabel *lblProduct;
    QLabel *qtyLabel;
    QLabel *lblImage;
    QPushButton *btn;
    QWidget *window;
    QVector<Item*> productList;
    QMenuBar *menu;
    QMenu *file;
    void colorLabel(QLabel *label, QColor color);

signals:


private slots:
    void handleMenuItemNew();
    void removeSelectedProduct();
    void handleItemClick(QListWidgetItem *item);
    void menuItemEdit();
    void handleSaveItems();
    void handleLoadItems();
};
#endif // MAINWINDOW_H
