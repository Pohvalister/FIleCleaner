#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openDirButton_clicked();

    void on_getFilenamesButton_clicked();

    void on_exelSaveButton_clicked();

    void slotSaveExel();

    void slotSetTemplate();
    void onApplied();

    void on_tableScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    void tableScrollBarRefresh(const int& max, const int& size);
};
#endif // MAINWINDOW_H
