#include "updateitemdialog.h"


UpdateItemDialog::UpdateItemDialog(Item *currentItem, QWidget *parent) {

    this->currentItem = currentItem;

    font = QFont("Times new Roman", 12, QFont::Bold);

    itemName = new QLabel("Name of Item");
    itemName->setFont(font);
    //itemName->setFrameShape(QFrame::Panel);

    qty = new QLabel("Quantity:");
    qty->setFont(font);

    itemImage = new QLabel("Item Image:");
    itemImage->setFont(font);

    quantity = new QSpinBox();
    quantity->setMaximum(1000);
    quantity->setMinimum(1);
    quantity->setFont(font);

    lblImage = new QLabel();
    lblImage->setFont(font);
    lblImage->setFixedWidth(250);
    lblImage->setFixedHeight(250);
    lblImage->setFrameShape(QFrame::Panel);

    ldImg = new QPushButton("Load Item Image");
    ldImg->setFont(font);

    editBtn = new QPushButton("Confirm Edit");
    editBtn->setFont(font);

    if(currentItem != nullptr){
        itemName->setText(currentItem->getName());
        pixmap =  QPixmap(currentItem->getImageFilePath());
        lblImage->setPixmap(pixmap);
        lblImage->setScaledContents(true);

        quantity->setValue(currentItem->getQuantity());

        imageFilePath = currentItem->getImageFilePath();
    }

    connect(editBtn, &QPushButton::clicked, this, &UpdateItemDialog::confirmUpdate);
    connect(ldImg, &QPushButton::clicked, this, &UpdateItemDialog::loadItemImage);

    hBox1 = new QHBoxLayout();
    hBox2 = new QHBoxLayout();
    hBox3 = new QHBoxLayout();
    hBox4 = new QHBoxLayout();

    vBox1 = new QVBoxLayout();
    vBox2 = new QVBoxLayout();

    hBox1->addWidget(itemName);

    hBox2->addWidget(qty);
    hBox2->addWidget(quantity);

    vBox2->addWidget(itemImage);
    vBox2->addWidget(ldImg);

    hBox3->addItem(vBox2);
    hBox3->addWidget(lblImage);

    hBox4->addWidget(editBtn);

    vBox1->addLayout(hBox1);
    vBox1->addLayout(hBox2);;
    vBox1->addLayout(hBox3);
    vBox1->addLayout(hBox4);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::darkYellow);

    this->setPalette(palette);
    this->setAutoFillBackground(true);

    this->setLayout(vBox1);
}

UpdateItemDialog::~UpdateItemDialog(){
    delete itemName;
    delete qty;
    delete itemImage;
    delete quantity;
    delete lblImage;
}

void UpdateItemDialog::confirmUpdate(){
    int amount = quantity->value();

    if(amount >= 1){
        currentItem->setQuantity(amount);
        currentItem->setImageFilePath(imageFilePath);
        this->close();
    }
    else{
        QMessageBox msg;
        msg.setText("Quantity must be at least 1.");
        msg.exec();
    }

}

void UpdateItemDialog::loadItemImage(){
    QString filename;

    filename = QFileDialog::getOpenFileName(this, "Open Image", "Image Files (*png *jpg)");

    if(filename != ""){
        int lastSlash = filename.lastIndexOf("/");
        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images" + shortName);
        pixmap = QPixmap("./images" + shortName); //comeback to this as it may cause an issue hopefully not

        lblImage->setPixmap(pixmap);
        lblImage->setScaledContents(true);

        imageFilePath = "./images" + shortName;
    }
}
