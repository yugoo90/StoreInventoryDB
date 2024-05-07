#include "additemdialog.h"

AddItemDialog::AddItemDialog(Item*& newItem, QWidget *parent)
    : QDialog(parent)
{

    this->newItem = &newItem;
    imageFilePath = "none.png";

    font = QFont("Times new Roman", 12, QFont::Bold);

    // Create the product label widget
    productName = new QLabel("Product Name:");
    productName->setFont(font);

    // Create a line edit for entering the name of the product
    nameBox = new QLineEdit;
    nameBox->setFont(font);
    nameBox->setFixedWidth(300);

    // Label for quantity
    quantity = new QLabel("Quantity:");
    quantity->setFont(font);

    // Spin box for the quantity to add
    qty = new QSpinBox();
    qty->setMinimum(1);
    qty->setMaximum(1000);
    qty->setFont(font);
    qty->setFixedWidth(300);

    // Image label
    image = new QLabel("Item Image:");
    image->setFont(font);

    lblImage = new QLabel();
    lblImage->setFixedWidth(250);
    lblImage->setFixedHeight(250);
    lblImage->setFrameShape(QFrame::Panel);

    // Button to confirm that a product has been added
    addButton = new QPushButton("Confirm Add");
    addButton->setFont(font);
    addButton->setFixedWidth(150);

    // Button to load the image of an Item
    loadButton = new QPushButton("Load Item Image");
    loadButton->setFont(font);

    // Registering events
    //connect(addButton, SIGNAL(clicked()), this, SLOT(confirmAdd()));
    connect(addButton, &QPushButton::clicked, this, &AddItemDialog::confirmAdd);
    //connect(loadButton, SIGNAL(clicked()), this, SLOT(loadItemImage()));
    connect(loadButton, &QPushButton::clicked, this, &AddItemDialog::loadItemImage);

    // grid = new QGridLayout(this);
    // grid->addWidget(productName, 10, 15);
    hBox1 = new QHBoxLayout();
    hBox2 = new QHBoxLayout();
    hBox3 = new QHBoxLayout();
    hBox4 = new QHBoxLayout();
    //hBox5 = new QHBoxLayout();
    vBox1 = new QVBoxLayout();
    vBox1->setAlignment(Qt::AlignHCenter);
    QVBoxLayout* vBox2 = new QVBoxLayout();
    hBox1->addWidget(productName);
    hBox1->addWidget(nameBox);

    hBox2->addWidget(quantity);
    hBox2->addWidget(qty);

    vBox2->addWidget(image);
    vBox2->addWidget(loadButton);
    hBox3->addItem(vBox2);
    hBox3->addWidget(lblImage);

    hBox4->addWidget(addButton);

    vBox1->addLayout(hBox1);
    vBox1->addLayout(hBox2);
    vBox1->addLayout(hBox3);
    vBox1->addLayout(hBox4);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::darkYellow);

    this->setPalette(palette);
    this->setAutoFillBackground(true);

    this->setLayout(vBox1);
    //this->setAutoFillBackground(true);

    QDir pathDir("./images");
    if(!pathDir.exists()){
        // create it
        QDir().mkdir("./images");
    }
}

void AddItemDialog::confirmAdd(){
    QString productName = nameBox->text();
    int quantity = qty->value();

    if(productName.trimmed() != "" && quantity >= 1){
        *newItem = new Item(productName, quantity, imageFilePath);
        QMessageBox msg;
        msg.setText("You have just added a new " + productName + " product");
        msg.exec();
        this->close();
    }
    else{
        QMessageBox msg;
        msg.setText("You must enter a valid name for the product and a quantity of at least 1");
        msg.exec();
    }
}

void AddItemDialog::loadItemImage(){
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Open Image", "./", "Image Files (*.png *.jpg)");

    if(filename != ""){
        int lastSlash = filename.lastIndexOf("/");

        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images" + shortName);

        QPixmap pixmap("./images" + shortName);
        lblImage->setPixmap(pixmap);
        lblImage->setScaledContents(true);

        imageFilePath = "./images" + shortName;
    }
}

