#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "command.h"
#include "add.h"
#include "sub.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <assert.h>
#include "historytablemodel.h"
#include "operationinfo.h"


bool MainWindow::operationClicked = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new HistoryTableModel)
{
    operationSet.emplace(COMMAND_TYPE::ADD, unique_ptr<Command>(new Add()));
    operationSet.emplace(COMMAND_TYPE::SUB, unique_ptr<Command>(new Sub()));
    currentOperation = getOperation(COMMAND_TYPE::ADD);

    ui->setupUi(this);
    ui->calculationLine->setValidator( new QIntValidator(-INFINITY, INFINITY, this) );
    ui->calculationLine->installEventFilter(this);
    ui->CalcTab->setTabText(0, QString("Calculator"));
    ui->CalcTab->setTabText(1, QString("History"));
    ui->resultLine->hide();

    init = false;

    ui->historyTable->setModel(model.get());
    OperationInfo operInfo (arithmeticUnit,*currentOperation);
    currentOperation->exec(arithmeticUnit);

    model->insertOperationRecord(std::move(operInfo));


    //QAbstractItemModel model;
    //ui->historyTable->setModel(model);

//    model.insertRow(0);
//    ui->historyTable->setModel(model);

//    model.insertRow(0);

    resetCalculator();
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plusButtonRespond()
{
    if(!operationClicked && init)
    {
        processButton();
    }

    currentOperation = getOperation(COMMAND_TYPE::ADD);
    ui->calculationLine->setFocus();
}

void MainWindow::minusButtonRespond()
{
    if(!operationClicked && init)
    {
        processButton();
    }

    currentOperation = getOperation(COMMAND_TYPE::SUB);
    ui->calculationLine->setFocus();
}

void MainWindow::equalButtonRespond()
{
    if(!operationClicked && isNumberCorrect())
    {
        currentOperation->setOperand(ui->calculationLine->text().toLongLong());
        currentOperation->exec(arithmeticUnit);

        ui->resultLine->setText(QString::number(arithmeticUnit.getResult()));
    }

    operationClicked = true;
    currentOperation = getOperation(COMMAND_TYPE::ADD);

    ui->resultLine->show();
    resetCalculator();
    ui->calculationLine->setFocus();
}


void MainWindow::numberButtonRespond(QString number)
{
    if (!init)
    {
        init = true;
        enableButtons(true);
    }
    auto numLine = ui->calculationLine;

    if(operationClicked)
    {
        numLine->setText(number);
        operationClicked = false;
    }
    else if(numLine->text() == QString("0"))
    {
        numLine->setText(number);
    }
    else
    {
        numLine->setText(numLine->text().append(number));
    }
}

void MainWindow::cancelButtonRespond()
{
    resetCalculator();
    ui->resultLine->hide();
    ui->calculationLine->setFocus();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        switch(keyEvent->key())
        {
         case Qt::Key_Plus: plusButtonRespond(); return true;
         case Qt::Key_Minus: minusButtonRespond(); return true;
         case Qt::Key_Enter:
         case Qt::Key_Equal:
         case Qt::Key_Return: if(init) equalButtonRespond(); return true;
         case Qt::Key_Backspace: removeDigit(1); return true;

         case Qt::Key_0: emit ui->Button0->clicked(true); return true;
         case Qt::Key_1: emit ui->Button1->clicked(true); return true;
         case Qt::Key_2: emit ui->Button2->clicked(true); return true;
         case Qt::Key_3: emit ui->Button3->clicked(true); return true;
         case Qt::Key_4: emit ui->Button4->clicked(true); return true;
         case Qt::Key_5: emit ui->Button5->clicked(true); return true;
         case Qt::Key_6: emit ui->Button6->clicked(true); return true;
         case Qt::Key_7: emit ui->Button7->clicked(true); return true;
         case Qt::Key_8: emit ui->Button8->clicked(true); return true;
         case Qt::Key_9: emit ui->Button9->clicked(true); return true;

         default: QMessageBox::warning(this,"Incorrect Input","Only values allowed"); return false;
        }
    }
    return ui->calculationLine->eventFilter(watched, event);
}

void MainWindow::removeDigit(int length)
{
    auto line = ui->calculationLine;

    line->setText(
                line->text().remove(
                        line->text().count() - length, length));

    if(line->text().count() == 0) resetCalculator();
}

void MainWindow::resetCalculator()
{
    init = false;
    arithmeticUnit.reset();

    ui->calculationLine->setText(QString("0"));

    enableButtons(false);
}

void MainWindow::enableButtons(bool flag)
{
    ui->buttonPlus->setEnabled(flag);
    ui->ButtonMinus->setEnabled(flag);
    ui->ButtonEqual->setEnabled(flag);
}

bool MainWindow::isNumberCorrect()
{
    QString numText = ui->calculationLine->text();
    auto ok = true;
    qlonglong num = numText.toLongLong(&ok);

    if(!ok)
         /*dynamic_cast<Div>(operation) == nullptr*/
        {
            ui->resultLine->setText("Value is out of range!");
            return 0;
        }
    return 1;
}

void MainWindow::processButton()
{
    auto numLine = ui->calculationLine;

    if(isNumberCorrect())
    {
        if(!arithmeticUnit.isInitialized())
        {
            long long number;
            number = numLine->text().toLongLong();

            arithmeticUnit.setValue(
                        (currentOperation->getSymbol() == '-') ? (-1)*number : number
                        );

            numLine->setText(QString::number(arithmeticUnit.getResult()));
        }
        else
        {
            currentOperation->setOperand(numLine->text().toLongLong());
            currentOperation->exec(arithmeticUnit);

            numLine->setText(QString::number(arithmeticUnit.getResult()));
        }
    }
    else
    {
        resetCalculator();
        ui->resultLine->show();
    }

    operationClicked = true;
}

void MainWindow::initConnections()
{
    connect(ui->buttonPlus, &QPushButton::clicked,this,&MainWindow::plusButtonRespond);
    connect(ui->ButtonMinus, &QPushButton::clicked,this,&MainWindow::minusButtonRespond);
    connect(ui->ButtonEqual, &QPushButton::clicked,this,&MainWindow::equalButtonRespond);
    connect(ui->ButtonCancel, &QPushButton::clicked, this, &MainWindow::cancelButtonRespond);

    auto buttonList = ui->NumbersFrame->findChildren<QPushButton*>();
    for(auto button: buttonList)
    {
        connect(button,
                &QPushButton::clicked,
                [this,button]
                {
                    numberButtonRespond(button->text());
                });
    }
}

Command* MainWindow::getOperation(COMMAND_TYPE operation)
{
    assert(operationSet.find(operation) != operationSet.end());

    return operationSet[operation].get();
}

//void MainWindow::storeHistory()
//{
//    auto table = ui->historyTable;
//    int count = table->rowCount();

////    table->insertRow(count);
////    for(int i = 0; i < 4; ++i)
////    {
////        table->insertColumn(table->columnCount());
////    }




////    table->setItem(count - 1, 0, new QTableWidgetItem(QString::number(arithmeticUnit.getResult())));
////    table->setItem(count - 1, 1, new QTableWidgetItem(QChar(currentOperation->getSymbol())));
////    table->setItem(count - 1, 2, new QTableWidgetItem(QString::number(currentOperation->getOperand())));
////    //table->setItem(count - 1, 3, new QTableWidgetItem(arithmeticUnit.getResult() + currentOperation->getOperand()));

////    currentOperation->exec(arithmeticUnit);

////    table->setItem(count - 1, 3, new QTableWidgetItem(QString::number(arithmeticUnit.getResult())));
//}


