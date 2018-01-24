#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "command.h"
#include "add.h"
#include "sub.h"
#include "historytablemodel.h"
#include "operationinfo.h"
#include "operationsortfiltermodel.h"

#include <QKeyEvent>
#include <QMessageBox>

#include <cassert>

using std::make_unique;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_historyModel(new HistoryTableModel(this)),
    m_proxyModelPositive(new OperationSortFilterModel("+",this)),
    m_proxyModelNegative(new OperationSortFilterModel("-",this))
{
    m_operationSet.emplace(COMMAND_TYPE::ADD, make_unique<Add>());
    m_operationSet.emplace(COMMAND_TYPE::SUB, make_unique<Sub>());
    m_currentOperation = &getOperation(COMMAND_TYPE::ADD);

    initUI();
    initConnections();
    resetCalculator();

    m_historyModel->getSavedHistory();
    m_proxyModelPositive->setSourceModel(m_historyModel);
    m_proxyModelNegative->setSourceModel(m_historyModel);
}

MainWindow::~MainWindow() = default;

void MainWindow::initConnections()
{
    connect(ui->buttonPlus, &QPushButton::clicked,this,&MainWindow::plusButtonRespond);
    connect(ui->buttonMinus, &QPushButton::clicked,this,&MainWindow::minusButtonRespond);
    connect(ui->buttonEqual, &QPushButton::clicked,this,&MainWindow::equalButtonRespond);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &MainWindow::cancelButtonRespond);

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

void MainWindow::initUI()
{
    ui->setupUi(this);

    ui->calculationLine->setValidator(new QIntValidator(-INFINITY, INFINITY, this));
    ui->calculationLine->installEventFilter(this);

    ui->resultLine->hide();

    ui->historyTable->setModel(m_historyModel);
    ui->positiveOperationsTable->setModel(m_proxyModelPositive);
    ui->negativeOperationsTable->setModel(m_proxyModelNegative);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        switch(keyEvent->key())
        {
         case Qt::Key_C: cancelButtonRespond(); return true;
         case Qt::Key_Plus: plusButtonRespond(); return true;
         case Qt::Key_Minus: minusButtonRespond(); return true;
         case Qt::Key_Enter:
         case Qt::Key_Equal:
         case Qt::Key_Return: if(m_inputStarted) equalButtonRespond(); return true;
         case Qt::Key_Backspace: removeDigit(1); return true;

         case Qt::Key_0: emit ui->button0->clicked(true); return true;
         case Qt::Key_1: emit ui->button1->clicked(true); return true;
         case Qt::Key_2: emit ui->button2->clicked(true); return true;
         case Qt::Key_3: emit ui->button3->clicked(true); return true;
         case Qt::Key_4: emit ui->button4->clicked(true); return true;
         case Qt::Key_5: emit ui->button5->clicked(true); return true;
         case Qt::Key_6: emit ui->button6->clicked(true); return true;
         case Qt::Key_7: emit ui->button7->clicked(true); return true;
         case Qt::Key_8: emit ui->button8->clicked(true); return true;
         case Qt::Key_9: emit ui->button9->clicked(true); return true;

         default: QMessageBox::warning(this,"Incorrect Input","Only values allowed"); return false;
        }
    }
    return ui->calculationLine->eventFilter(watched, event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!m_historyModel->saveHistory())
        QMessageBox::warning(this,"Error","History of operations have not been saved!");

    event->accept();
}

void MainWindow::numberButtonRespond(const QString& number)
{
    if (!m_inputStarted)
    {
        m_inputStarted = true;
        enableButtons(true);
    }
    auto numLine = ui->calculationLine;

    if(m_operationClicked)
    {
        numLine->setText(number);
        m_operationClicked = false;
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

void MainWindow::plusButtonRespond()
{
    if(!m_operationClicked && m_inputStarted)
    {
        processButton();
    }

    m_currentOperation = &getOperation(COMMAND_TYPE::ADD);
    ui->calculationLine->setFocus();
}

void MainWindow::minusButtonRespond()
{
    if(!m_operationClicked && m_inputStarted)
    {
        processButton();
    }

    m_currentOperation = &getOperation(COMMAND_TYPE::SUB);
    ui->calculationLine->setFocus();
}

void MainWindow::equalButtonRespond()
{
    if(!m_operationClicked)
    {
        if(tryConvertNumber(ui->calculationLine->text()))
        {
            calculate();
            ui->resultLine->setText(QString::number(m_arithmeticUnit.getResult()));
        }
    }
    else ui->resultLine->setText(QString::number(m_arithmeticUnit.getResult()));

    m_currentOperation = &getOperation(COMMAND_TYPE::ADD);

    ui->resultLine->show();
    resetCalculator();
    ui->calculationLine->setFocus();
}

void MainWindow::removeDigit(int length)
{
    auto line = ui->calculationLine;

    line->setText(
                line->text().remove(
                        line->text().count() - length, length));

    if(line->text().count() == 0) resetCalculator();
}

void MainWindow::cancelButtonRespond()
{
    resetCalculator();
    ui->resultLine->hide();
    ui->calculationLine->setFocus();
}

void MainWindow::resetCalculator()
{
    m_inputStarted = false;
    m_operationClicked = false;

    m_arithmeticUnit.reset();

    ui->calculationLine->setText(QString("0"));

    enableButtons(false);
}

void MainWindow::enableButtons(bool flag)
{
    ui->buttonPlus->setEnabled(flag);
    ui->buttonMinus->setEnabled(flag);
    ui->buttonEqual->setEnabled(flag);
}

void MainWindow::processButton()
{
    if(tryConvertNumber(ui->calculationLine->text()))
    {
        calculate();
        ui->calculationLine->setText(QString::number(m_arithmeticUnit.getResult()));
    }
    else
    {
        resetCalculator();
        ui->resultLine->show();
    }

    m_operationClicked = true;
}

bool MainWindow::tryConvertNumber(const QString& numText)
{
    auto ok = true;
    auto num = numText.toLongLong(&ok);

    if(!ok)
         /*dynamic_cast<Div>(operation) == nullptr*/
        {
            ui->resultLine->setText("Value is out of range!");
            return 0;
        }
    return 1;
}

Command& MainWindow::getOperation(COMMAND_TYPE operation)
{
    assert(m_operationSet.find(operation) != m_operationSet.end());

    return *m_operationSet[operation];
}

void MainWindow::calculate()
{
    if(!m_arithmeticUnit.isInitialized())
    {
        processFirstInput();
    }
    else
    {
        processOperation();
    }
}

void MainWindow::processFirstInput()
{
    assert(m_currentOperation != nullptr);

    auto number = ui->calculationLine->text().toLongLong();
    auto isSymbolMinus = m_currentOperation->getSymbol() == COMMAND_TYPE::SUB;

    m_arithmeticUnit.setValue(isSymbolMinus ? (-1)*number : number);
}

void MainWindow::processOperation()
{
    assert(m_currentOperation != nullptr);

    m_currentOperation->setOperand(ui->calculationLine->text().toLongLong());

    OperationInfo operInfo (m_arithmeticUnit,*m_currentOperation);

    m_currentOperation->exec(m_arithmeticUnit);

    operInfo.setOperationResult(m_arithmeticUnit.getResult());

    m_historyModel->insertOperationRecord(std::move(operInfo));
}
