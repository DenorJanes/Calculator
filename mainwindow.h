#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "arithmeticunit.h"
#include "commandtypes.h"

#include <QMainWindow>

#include <memory>



class Command;
class HistoryTableModel;
class OperationSortFilterModel;

namespace Ui {
class MainWindow;
}


class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void closeEvent(QCloseEvent* event) override;

    void removeDigit(int length);
    void enableButtons(bool flag);

    void resetCalculator();
    void initConnections();
    void initUI();

    void calculate();

    void processButton();
    void processOperation();
    void processFirstInput();

    bool tryConvertNumber(const QString& numLine);

    Command& getOperation(COMMAND_TYPE operation);

private slots:
    void numberButtonRespond(const QString& number);
    void plusButtonRespond();
    void minusButtonRespond();
    void equalButtonRespond();
    void cancelButtonRespond();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::map<COMMAND_TYPE,std::unique_ptr<Command>> m_operationSet;
    Command* m_currentOperation{};
    HistoryTableModel* m_historyModel{};
    OperationSortFilterModel* m_proxyModelPositive{};
    OperationSortFilterModel* m_proxyModelNegative{};
    ArithmeticUnit m_arithmeticUnit{};

    bool m_operationClicked{};
    bool m_inputStarted{};
};

#endif // MAINWINDOW_H
