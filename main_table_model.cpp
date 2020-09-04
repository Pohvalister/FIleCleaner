#include "main_table_model.h"

MainTableModel::MainTableModel(QObject *parent)
    :QAbstractTableModel(parent){
}

int MainTableModel::rowCount(const QModelIndex &parent) const{
    return rowCnt;
}

int MainTableModel::columnCount(const QModelIndex &parent) const{
    return colCnt;
}

QVariant MainTableModel::data(const QModelIndex &index, int role) const{
    switch (role) {
    case Qt::DisplayRole:
        return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() + 1);
    default:
        return QVariant();
    }

}
