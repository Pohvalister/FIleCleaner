#ifndef MAIN_TABLE_MODEL_H
#define MAIN_TABLE_MODEL_H


#include <QAbstractListModel>
#include <QDirIterator>



class FileTableModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QString directory;
    QStringList templates;


    int ROW_MAX = 30;
    const int CACHE_AMOUNT = 1024;//the range between checkpoints

    QVector<QString> fileListCache;
    //QVector<QString> fileCheckpoints;


    int file_amount = 0;
    int scanned_amount = 0;
    int file_cache_start = 0;


    void refresh_view();

public:
    FileTableModel(QObject *parent = nullptr);

    //model interaction
    QPair<int,int> refresh_table();
    void scroll_table(const int& scroll_val);
    QPair<int,int> set_new_directory(const QString& dir, const QStringList& temp = {});
    int get_row_amount() const;
    //model interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MAIN_TABLE_MODEL_H
