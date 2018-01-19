#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "arithmeticunit.h"


class Command;
class HistoryTableModel;

namespace Ui {
class MainWindow;
}

using std::unique_ptr;
using std::map;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class COMMAND_TYPE {ADD, SUB};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    map<COMMAND_TYPE,unique_ptr<Command>> operationSet;
    Command* currentOperation;
    unique_ptr<HistoryTableModel> model;
    ArithmeticUnit arithmeticUnit;

    static bool operationClicked;
    bool init;

    bool eventFilter(QObject *watched, QEvent *event) override;

    void removeDigit(int length);
    void resetCalculator();
    void enableButtons(bool flag);
    void processButton();
    void initConnections();
    bool isNumberCorrect();
    void storeHistory();
    Command* getOperation(COMMAND_TYPE operation);

public slots:
    void numberButtonRespond(QString number);
    void plusButtonRespond();
    void minusButtonRespond();
    void equalButtonRespond();

private slots:
    void cancelButtonRespond();

};

#endif // MAINWINDOW_H
