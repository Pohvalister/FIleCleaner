#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTableWidget"
#include "QListWidget"
#include "QDirIterator"
#include "main_table_model.h"

//
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
//

#include <QMessageBox>

QFileDialog* mainFileDialog;
QString workingDirectoryString = "";

QStringList fileList;
MainTableModel tableModel;

QStringList templatesList;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*slots:
    void slotSaveExel();*/

    this->ui->fileTableView->setModel(&tableModel);
    this->ui->fileTableView->update();
    this->ui->fileTableView->show();

    //диалог для посика необходимых директорий
    mainFileDialog = new QFileDialog;
    mainFileDialog->setFileMode(QFileDialog::DirectoryOnly);

    //верхнее меню + все её возмолжности
    QAction* exelSave = new QAction("exel save action", 0);
    exelSave->setText("&Сохранить в Exel");
    exelSave->setShortcut(QKeySequence("CTRL+S"));
    exelSave->setToolTip("Save List to Exel File");
    exelSave->setStatusTip("Save the file to disk");
    exelSave->setWhatsThis("Save the file to disk");

    connect(exelSave, SIGNAL(triggered()), SLOT(slotSaveExel()));
    this->ui->menu_File->addAction(exelSave);

    QAction* setTemplate = new QAction("set search templates");
    setTemplate->setText("&Настроить шаблоны поиска");
    setTemplate->setShortcut(QKeySequence("CTRL+T"));
    setTemplate->setToolTip("Go to Search Template Setting Menu");
    setTemplate->setStatusTip("Go to search template settings");
    setTemplate->setWhatsThis("Go to search template settings");

    connect(setTemplate, SIGNAL(triggered()), SLOT(slotSaveExel()));
    this->ui->menu_Settings->addAction(setTemplate);

    //QToolBar* ptb = new QToolBar("Linker ToolBar");
    //ptb->addAction(pactSave);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openDirButton_clicked()
{
    QString dirName;
    dirName = mainFileDialog->getExistingDirectory();

    workingDirectoryString = dirName;

    this->ui->fileTextEdit->setText(dirName);
}

void MainWindow::on_getFilenamesButton_clicked()
{
    QDir directory(workingDirectoryString);

    if (!directory.exists()){
        QMessageBox nonExistMsgBox;
        nonExistMsgBox.setWindowTitle("Ошибка чтения");
        nonExistMsgBox.setText("Заданной директории не существует");
        nonExistMsgBox.exec();
        return;
    }
    if (directory.isEmpty()){
        QMessageBox emptyMsgBox;
        emptyMsgBox.setWindowTitle("Ошибка чтения");
        emptyMsgBox.setText("Заданная директория пуста");
        emptyMsgBox.exec();
        return;
    }

    QDirIterator it(workingDirectoryString, templatesList, QDir::Files, QDirIterator::Subdirectories);
    int counter = 0;
    fileList = QStringList();
    while (it.hasNext()){
        QString str = it.next();
        fileList.append(str);

        if (counter % 10 == 0)
            this->ui->statusLabel->setText("Файлов: " + QString::number(counter));
        fileList.push_back(str);
        counter++;
    }

    this->ui->statusLabel->setText("Файлов: " + QString::number(counter));
    QMessageBox foundMsgBox;
    foundMsgBox.setWindowTitle("Поиск закончен");
    foundMsgBox.setText("Внутри директории файлов найдено: " + QString::number(counter));
    foundMsgBox.exec();

    tableModel.rowCnt = 3;

    this->ui->fileTableView->update();
    this->ui->fileTableView->show();
   //fileList = directory.entryList(QDir::Files);

}

void MainWindow::on_exelSaveButton_clicked()
{

    QXlsx::Document xlsx;

    int counter = 1;
    foreach(QString str, fileList){
        xlsx.write(counter, 1, str);
        counter++;
    }
    xlsx.saveAs("Test.xlsx");
}
