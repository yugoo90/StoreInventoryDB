#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    Item(QString name, int quantity, QString imageFilePath =" ");

    void setName(QString name);
    QString getName() const;
    void setQuantity(int quantity);
    int getQuantity() const;
    void setImageFilePath(QString path);
    QString getImageFilePath() const;
private:
    QString name;
    int quantity;
    QString imageFilePath;
};

#endif // ITEM_H
