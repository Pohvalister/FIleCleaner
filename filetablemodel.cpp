#include "filetablemodel.h"
#include <QDirIterator>
#include <math.h>


FileTableModel::FileTableModel(QObject *parent)
    :QAbstractTableModel(parent){
}

int FileTableModel::rowCount(const QModelIndex &parent) const{
    return std::min(ROW_MAX, file_amount);
}

int FileTableModel::columnCount(const QModelIndex &parent) const{
    return COLUMN_MAX;
}

QVariant FileTableModel::data(const QModelIndex &index, int role) const{

    switch (role) {
    case Qt::DisplayRole:
        return fileListCache[(scanned_amount - file_cache_start) + index.row()];

    default:
        return QVariant();
    }

}

QPair<int,int> FileTableModel::set_new_directory(const QString &dir, const QStringList &temp){
    directory = dir;
    templates = temp;
    file_amount = 0;
    scanned_amount = 0;
    return refresh_table();
}

QPair<int,int> FileTableModel::refresh_table(){
    /*
    QDirIterator it_first(directory, templates, QDir::Files, QDirIterator::Subdirectories);
    QDirIterator it_last(directory, templates, QDir::Files, QDirIterator::Subdirectories);

    int cashe_start = std::max(scanned_amount - CASHE_SIDE, 0);
    int cashe_end = std::min(scanned_amount + CASHE_SIDE, file_amount);

    int count = 0;
    int scanned_count = 0;
    int cashe_count = 0;

    while (it_last.hasNext() && count < RAW_MAX) {
        count++;
    }

    while(it_last.hasNext() && count < cashe_start){
       it_first.next();
       scanned_count++;
       cashe_count++;
       it_last.next();
       count++;
    }

    file_cashe_start = cashe_count;

    fileListCashe.clear();

    QString last_name = it_last.fileName();
    QString file_name = it_first.fileName();
    while(it_first.hasNext() && file_name != last_name && cashe_count){
        fileListCashe.append(it_first.next());
    }

    while(it_last.hasNext()){
        it_last.next();
        count++;
    }

    file_amount = count;
*/
    fileListCache.clear();
    QDirIterator it(directory, templates, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        fileListCache.append(it.next());
    }
    file_amount = fileListCache.size();
    scanned_amount = std::min(scanned_amount,std::max(file_amount - ROW_MAX, 0));
    refresh_view();
    return QPair<int,int>(file_amount,scanned_amount);
}

void FileTableModel::scroll_table(const int &scroll_val){
    scanned_amount = scroll_val;
    refresh_view();
    //if (scroll_val + scanned_amount < file_cashe_start || scroll_val + scanned_amount + RAW_MAX > file_amount);
}

void FileTableModel::refresh_view(){
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex botRight = createIndex(ROW_MAX - 1,COLUMN_MAX - 1);
    endResetModel();
    //emit this->dataChanged(topLeft, botRight, {Qt::DisplayRole});
    //emit this->

    //emit QAbstractTableModel::dataChanged(topLeft, botRight, {Qt::DisplayRole});
}
