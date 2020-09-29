#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTableView"
#include "QListWidget"
#include "QDirIterator"
#include "QProgressDialog"

#include "filetablemodel.h"
#include "settemplatedialog.h"
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
FileTableModel* tableModel = new FileTableModel();

QStringList templatesList;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->fileListView->setModel(tableModel);
    this->ui->fileListView->show();
    this->ui->tableScrollBar->setPageStep(tableModel->get_row_amount());

    //диалог для поиска необходимых директорий
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

    connect(setTemplate, SIGNAL(triggered()), SLOT(slotSetTemplate()));
    this->ui->menu_Settings->addAction(setTemplate);
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
    if (workingDirectoryString == ""){
        QMessageBox emptyStringBox;
        emptyStringBox.setWindowTitle("Ошибка чтения");
        emptyStringBox.setText("Директория не указана");
        emptyStringBox.exec();
        return;
    }

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

    QPair<int, int> status = tableModel->set_new_directory(workingDirectoryString, templatesList);

    tableScrollBarRefresh(status.first, status.second);

    this->ui->statusLabel->setText("Файлов: " + QString::number(status.first));
    QMessageBox foundMsgBox;
    foundMsgBox.setWindowTitle("Поиск закончен");
    foundMsgBox.setText("Внутри директории файлов найдено: " + QString::number(status.first));
    foundMsgBox.exec();


}

void MainWindow::tableScrollBarRefresh(const int& max, const int& size){
    int step = this->ui->tableScrollBar->pageStep();
    this->ui->tableScrollBar->setMaximum(max - step);
    this->ui->tableScrollBar->setValue(size);
}

void MainWindow::on_exelSaveButton_clicked()
{
    slotSaveExel();
}

void MainWindow::slotSaveExel(){
    QXlsx::Document xlsx;

    //QStringList fileList = tableModel.get_file_list();



    xlsx.saveAs("Test.xlsx");
}

void MainWindow::slotSetTemplate(){
    SetTemplateDialog tdlg( this );

    connect(&tdlg, SIGNAL( applied() ), SLOT ( onApplied()));
    switch(tdlg.exec()){
    case QDialog::Accepted:
        templatesList.append(tdlg.getInput());
        this->ui->tmpLabel->setText(tdlg.getInput().front());
        break;
    default:
        break;
   }
    return;
}

void MainWindow::onApplied(){
    if (SetTemplateDialog* dlg = qobject_cast<SetTemplateDialog*>(sender())){
        templatesList.append(dlg->getInput());
        this->ui->tmpLabel->setText(dlg->getInput().front());
    }
}


void MainWindow::on_tableScrollBar_valueChanged(int value)
{
    tableModel->scroll_table(value);
}
