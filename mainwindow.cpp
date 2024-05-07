#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window = new QWidget();
    window->setWindowTitle("Store Inventory");

    QPalette palette = window->palette();
    palette.setColor(QPalette::Window, Qt::darkYellow);
    window->setPalette(palette);
    window->setAutoFillBackground(true);
    //window->setStyleSheet("QWidget{background-color: green;}");

    // Set font
    font = QFont("Times new Roman", 12, QFont::Bold);

    product = new QLabel("Selected Product:");
    product->setFont(font);

    quantity = new QLabel("Quantity:");
    quantity->setFont(font);

    lblProduct = new QLabel();
    lblProduct->setFixedWidth(150);
    lblProduct->setFixedHeight(25);
    lblProduct->setFont(font);
    lblProduct->setFrameShape(QFrame::Panel);
    QColor color = Qt::white;
    colorLabel(lblProduct, color);
    //palette = lblProduct->palette();
    //palette.setColor(QPalette::Window, Qt::red);
    //lblProduct->setPalette(palette);
    //lblProduct->setAutoFillBackground(true);

    qtyLabel = new QLabel();
    qtyLabel->setFont(font);
    qtyLabel->setFixedWidth(150);
    qtyLabel->setFixedHeight(25);
    qtyLabel->setFrameShape(QFrame::Panel);
    colorLabel(qtyLabel, color);

    list = new QListWidget();
    list->setFixedWidth(550);
    list->setFixedHeight(500);
    list->setFont(font);

    //window = new QWidget();
    //window->setWindowTitle("Store Inventory");

    lblImage = new QLabel;
    lblImage->setFixedHeight(250);
    lblImage->setFixedWidth(400);
    lblImage->setFrameShape(QFrame::Panel);

    int listRowCount = 5;

    btn = new QPushButton("Remove Selected Product");
    btn->setFont(font);

    menu = new QMenuBar();
    menu->setFont(font);

    file = menu->addMenu("&File");
    file->setFont(font);

    QAction *addProductAction = file->addAction("New Product");
    QAction *editProductAction = file->addAction("Edit Selected Product");
    file->addSeparator();
    QAction *saveProductAction = file->addAction("Save Product");
    QAction *loadProductAction = file->addAction("Load Product");
    file->addSeparator();
    QAction *exitAction = file->addAction("Exit");

    connect(addProductAction, &QAction::triggered, this, &MainWindow::handleMenuItemNew);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(removeSelectedProduct()));
    connect(list, &QListWidget::itemClicked, this, &MainWindow::handleItemClick);
    connect(editProductAction, &QAction::triggered, this, &MainWindow::menuItemEdit);
    connect(saveProductAction, &QAction::triggered, this, &MainWindow::handleSaveItems);
    connect(loadProductAction, &QAction::triggered, this, &MainWindow::handleLoadItems);

    setMenuBar(menu);
    grid = new QGridLayout(window);
    grid->addWidget(list,1,0,listRowCount,1);
    grid->addWidget(product, 1, 1);
    grid->addWidget(lblProduct, 1, 2);
    grid->addWidget(quantity, 2, 1);
    grid->addWidget(qtyLabel, 2, 2);
    grid->addWidget(btn, 1 + listRowCount, 0);
    grid->addWidget(lblImage, 1 + listRowCount,1,1,2,Qt::AlignCenter);
    //grid->addWidget(menu);


    window->setLayout(grid);
    this->setCentralWidget(window);

}

MainWindow::~MainWindow()
{
    for(Item *item : productList){
        delete item;
    }
    productList.clear();

    delete ui;

}

void MainWindow::handleMenuItemNew(){
    Item *nItem = nullptr;
    AddItemDialog addItem(nItem, nullptr);

    addItem.setModal(true);
    addItem.exec();

    if(nItem != nullptr){
        productList.push_back(nItem);
        list->addItem(nItem->getName());
    }
}

void MainWindow::removeSelectedProduct(){
    int index = list->currentRow();

    if(index >= 0){
        Item* theItem = productList.at(index);
        delete theItem;
        productList.removeAt(index);

        delete list->currentItem();
    }

    QPixmap pixmap("none.png");
    lblImage->setPixmap(pixmap);
}

void MainWindow::handleItemClick(QListWidgetItem *item){
    int index = item->listWidget()->currentRow();

    if(index != -1){
        Item *currItem = productList.at(index);

        if(currItem != nullptr){
            lblProduct->setText(currItem->getName());
            qtyLabel->setText(QString::number(currItem->getQuantity()));

            QPixmap pixmap(currItem->getImageFilePath());

            lblImage->setPixmap(pixmap);
            lblImage->setScaledContents(true);
        }
    }
}

void MainWindow::menuItemEdit(){
    int index = list->currentRow();

    if(index != -1){
        Item *currItem = productList.at(index);

        if(currItem != nullptr){
            UpdateItemDialog updateItem(currItem, nullptr);
            updateItem.exec();

            lblProduct->setText(currItem->getName());
            qtyLabel->setText(QString::number(currItem->getQuantity()));

            QPixmap pixmap(currItem->getImageFilePath());
            lblImage->setPixmap(pixmap);
            lblImage->setScaledContents(true);
        }
    }
}

void MainWindow::handleSaveItems(){
    QFile outputFile("products.txt");

    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&outputFile);

    for(Item *product: productList){
        out<<product->getName()<<",";
        out<<product->getQuantity()<<",";
        out<<product->getImageFilePath()<<Qt::endl;
    }

    out.flush();
    outputFile.close();
}

void MainWindow::handleLoadItems(){
    QFile inputFIle("products.txt");

    inputFIle.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&inputFIle);

    for(Item *temp: productList){
        delete temp;
    }

    productList.clear();
    list->clear();

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList info = line.split(",");


        list->addItem(info.at(0));
        Item *product = new Item(info.at(0), info.at(1).toInt(), info.at(2));

        productList.push_back(product);
    }

    in.flush();
    inputFIle.close();

}

void MainWindow::colorLabel(QLabel *label, QColor color){
    QPalette palette = label->palette();
    palette.setColor(QPalette::Window, color);
    label->setPalette(palette);
    label->setAutoFillBackground(true);
}
