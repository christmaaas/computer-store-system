#include "order.h"

Order::Order()
{
    receiverLineEdit = nullptr;
    receiverNumberLineEdit = nullptr;
    deliveryAdressLineEdit = nullptr;

    orderDetailDialog = nullptr;
    orderTable = nullptr;
}

Order::~Order()
{
    delete receiverLineEdit;
    delete receiverNumberLineEdit;
    delete deliveryAdressLineEdit;
    delete orderTable;
    delete orderDetailDialog;
}

bool checkOrderForCorrect(const QString& receiver, const QString& phoneNumberOfReceiver, const QString& deliveryAdress)
{
    if (receiver.isNull() || phoneNumberOfReceiver.isNull() || deliveryAdress.isNull() || !receiver.contains(QRegularExpression("[A-Za-zА-Яа-яЁё]")))
        return false;

    if (!phoneNumberOfReceiver.startsWith('+') || !phoneNumberOfReceiver.contains(QRegularExpression("\\+375(29|44)\\d{7}")) || phoneNumberOfReceiver.size() != 13)
        return false;

    if(deliveryAdress.count(';') == 2)
    {
        QStringList addressParts = deliveryAdress.split(";", Qt::SkipEmptyParts);

        if (addressParts.size() < 3 || (addressParts[0].trimmed().isEmpty() || !addressParts[0].contains(QRegularExpression("[A-Za-zА-Яа-яЁё]"))) || (addressParts[1].trimmed().isEmpty() || !addressParts[1].contains(QRegularExpression("[A-Za-zА-Яа-яЁё]"))) || (addressParts[2].trimmed().isEmpty() || addressParts[2].contains(QRegularExpression("[A-Za-zА-Яа-яЁё]"))))
            return false;
    }
    else
        return false;

    return true;
}


void Order::TakeLabelsContent()
{
    if(checkOrderForCorrect(receiverLineEdit->text(), receiverNumberLineEdit->text(), deliveryAdressLineEdit->text()))
    {
        orderId = QRandomGenerator::global()->bounded(10000, 99999);
        receiver = receiverLineEdit->text();
        phoneNumberOfReceiver = receiverNumberLineEdit->text();

        QStringList addressParts = deliveryAdressLineEdit->text().split(";", Qt::SkipEmptyParts);
        deliveryAdress = "г. " + addressParts[0] + "," + " ул. " + addressParts[1] + ", " + addressParts[2];

        orderDetailDialog->accept();
    }
    else
        QMessageBox::warning(nullptr, "Предупреждение", "Вы не заполнили данные");
}

void Order::FillReceiverData(int orderCost)
{
    orderDetailDialog = new QDialog();
    orderDetailDialog->setWindowTitle("Данные о заказе");

    orderDetailDialog->resize(500, 100);

    QVBoxLayout* layout = new QVBoxLayout;

    QLabel* titleLabel = new QLabel("Заполните данные для заказа");
    titleLabel->setFont(QFont("Arial", 14));

    receiverLineEdit = new QLineEdit;
    receiverLineEdit->setPlaceholderText("Получатель: (Имя)");
    receiverLineEdit->setFont(QFont("Arial", 14));

    receiverNumberLineEdit = new QLineEdit;
    receiverNumberLineEdit->setPlaceholderText("Номер получателя: (+375...)");
    receiverNumberLineEdit->setFont(QFont("Arial", 14));

    deliveryAdressLineEdit = new QLineEdit;
    deliveryAdressLineEdit->setPlaceholderText("Адрес доставки: (г.;ул.;№дома)");
    deliveryAdressLineEdit->setFont(QFont("Arial", 14));

    QPushButton* readyButton = new QPushButton("Готово");
    readyButton->setFont(QFont("Arial", 14));

    layout->addWidget(titleLabel);
    layout->addWidget(receiverLineEdit);
    layout->addWidget(receiverNumberLineEdit);
    layout->addWidget(deliveryAdressLineEdit);
    layout->addWidget(readyButton);

    orderDetailDialog->setLayout(layout);

    connect(readyButton, &QPushButton::clicked, this, &Order::TakeLabelsContent);

    this->orderCost = orderCost;

    orderDetailDialog->exec();

    delete titleLabel;

    delete receiverLineEdit;
    receiverLineEdit = nullptr;

    delete receiverNumberLineEdit;
    receiverNumberLineEdit = nullptr;

    delete deliveryAdressLineEdit;
    deliveryAdressLineEdit = nullptr;

    delete readyButton;
    delete layout;
}

void Order::FillFile(QList<Component::Component*> cart)
{
    QFile file(ORDERS_FILE);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);

        out << orderId << ";" << receiver << ";" << phoneNumberOfReceiver << ";" << deliveryAdress << ";" << orderCost << ";";

        for(Component::Component* component : cart)
            out << component->GetName() + " x" + QString::number(component->GetAmount()) << ";";

        out << "\n";

        file.close();
    }
    else
        qDebug() << "Ошибка открытия файла " << BUFFER_FILE;
}

int Order::GetOrderCost()
{
    return orderCost;
}

void Order::FillTable(QList<Component::Component*> cart)
{
    QFile file(ORDERS_FILE);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    orderTable->clearContents();
    orderTable->setRowCount(0);

    int row = 0;
    while(!in.atEnd())
    {
        QString str = in.readLine();
        QStringList substrings = str.split(";");

        orderTable->insertRow(row);
        orderTable->setItem(row, 0, new QTableWidgetItem(substrings[ORDER_ID]));
        orderTable->setItem(row, 1, new QTableWidgetItem(substrings[ORDER_NAME]));
        orderTable->setItem(row, 2, new QTableWidgetItem(substrings[ORDER_NUMBER]));
        orderTable->setItem(row, 3, new QTableWidgetItem(substrings[ORDER_ADRESS]));
        orderTable->setItem(row, 5, new QTableWidgetItem(substrings[ORDER_PRICE] + "$"));

        QString components;
        for(int i = 5, indexInTable = 1; i < substrings.size() - 1; i++, indexInTable++)
            components += QString::number(indexInTable) + ". " + substrings[i] + "\n";

        QTextEdit* textEdit = new QTextEdit();
        textEdit->setPlainText(components);
        textEdit->setReadOnly(true);
        textEdit->setFrameStyle(QFrame::NoFrame);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        orderTable->setCellWidget(row, 4, textEdit);

        for(int col = 0; col < orderTable->columnCount(); col++)
        {
            QTableWidgetItem* item = orderTable->item(row, col);

            if (item)
                item->setFlags((item->flags() & ~Qt::ItemIsEditable));
        }

        orderTable->setRowHeight(row, 50);

        row++;
    }

    file.close();
}

void Order::CreateTab(QWidget* ordersTab, QVBoxLayout* orderLayout)
{
    orderTable = new QTableWidget(ordersTab);
    orderTable->setColumnCount(6);
    orderTable->setHorizontalHeaderLabels({"Номер заказа", "Получатель", "Номер получателя", "Адрес доставки", "Товары", "Сумма заказа"});

    orderTable->setColumnWidth(0, 100);
    orderTable->setColumnWidth(1, 150);
    orderTable->setColumnWidth(2, 150);
    orderTable->setColumnWidth(3, 250);
    orderTable->setColumnWidth(4, 630);
    orderTable->setColumnWidth(5, 100);

    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setSelectionMode(QAbstractItemView::SingleSelection);

    orderLayout = new QVBoxLayout(ordersTab);
    orderLayout->addWidget(orderTable);
}

QDialog* Order::GetOrderDetailDialog()
{
    return orderDetailDialog;
}

void Order::SetOrderDetailDialog(QDialog* orderDetailDialog)
{
    this->orderDetailDialog = orderDetailDialog;
}
