#include "filetablemodel.h"
#include <QDirIterator>
#include <math.h>


FileTableModel::FileTableModel(QObject *parent)
    :QAbstractListModel(parent){
}

int FileTableModel::rowCount(const QModelIndex &parent) const{
    return std::max(std::min(ROW_MAX, file_amount - 1), 0);
}


QVariant FileTableModel::data(const QModelIndex &index, int role) const{

    switch (role) {
    case Qt::DisplayRole:
        return fileListCache[scanned_amount + index.row()];
       // return fileListCache[(scanned_amount - (scanned_amount/CACHE_AMOUNT)*CACHE_AMOUNT) + index.row()];

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
    QDirIterator it(directory, templates, QDir::Files, QDirIterator::Subdirectories);
    fileListCache.clear();
    int count = 0;
    while (it.hasNext()){
        fileListCache.push_back(it.next());
        count++;
    }

    file_amount = count;
    if (scanned_amount > file_amount - ROW_MAX)
        scanned_amount = 0;

    refresh_view();
    return QPair<int,int>(file_amount, scanned_amount);
}

/*void FileTableModel::refresh_cache(){
    fileListCache.clear();
    int cache_start = scanned_amount / CACHE_AMOUNT;
    QDirIterator it(fileCheckpoints[cache_start], templates, QDir::Files, QDirIterator::Subdirectories);
    QString last_file_name = (cache_start > fileCheckpoints.size() - 2 ? "" : fileCheckpoints[cache_start + 2]);//2 блока, чтобы учесть переход конца
    bool tmp = it.hasNext();
    QString fn = it.fileName();
    while(it.hasNext() && it.fileName() != last_file_name){
        fileListCache.push_back(it.next());
    }
}*/

void FileTableModel::scroll_table(const int &scroll_val){
    scanned_amount = scroll_val;
    refresh_view();
}

void FileTableModel::refresh_view(){
    //QModelIndex topLeft = createIndex(0,0);
    //QModelIndex botRight = createIndex(ROW_MAX - 1,COLUMN_MAX - 1);
    endResetModel();
    //emit this->dataChanged(topLeft, botRight, {Qt::DisplayRole});
    //emit this->

    //emit QAbstractTableModel::dataChanged(topLeft, botRight, {Qt::DisplayRole});
}

int FileTableModel::get_row_amount() const{
    return ROW_MAX;
}
