#ifndef STOCKINFODIALOG_H
#define STOCKINFODIALOG_H

#include <QDialog>

namespace Ui {
    class StockInfoDialog;
}

class StockInfoDialog : public QDialog
{
    Q_OBJECT

public:
    StockInfoDialog(QWidget* parent);
    ~StockInfoDialog();

private:
    void UpdateStockInfo() noexcept;

private:
    Ui::StockInfoDialog* ui;
};

#endif // STOCKINFODIALOG_H
