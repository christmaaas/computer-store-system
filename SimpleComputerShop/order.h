#ifndef ORDER_H
#define ORDER_H

#include <QRegularExpression>

#include "component.h"

#define ORDER_ID 0
#define ORDER_NAME 1
#define ORDER_NUMBER 2
#define ORDER_ADRESS 3
#define ORDER_PRICE 4

#define ORDERS_FILE "./holders/orders.txt"
#define BUFFER_FILE "./holders/buffer.txt"

class Order : public QObject
{
    Q_OBJECT

private:
    int orderId;
    int orderCost;

    QString receiver;
    QString phoneNumberOfReceiver;
    QString deliveryAdress;

    QLineEdit* receiverLineEdit;
    QLineEdit* receiverNumberLineEdit;
    QLineEdit* deliveryAdressLineEdit;

    QDialog* orderDetailDialog;

    QTableWidget* orderTable;

private slots:
    void TakeLabelsContent();

public:
    Order();
    ~Order();

    void FillReceiverData(int order_price);
    void FillTable(QList<Component::Component*> cart);
    void FillFile(QList<Component::Component*> cart);
    int GetOrderCost();
    void CreateTab(QWidget* ordersTab, QVBoxLayout* orderLayout);
    QDialog* GetOrderDetailDialog();
    void SetOrderDetailDialog(QDialog* orderDetailDialog);
};

#endif // ORDER_H
