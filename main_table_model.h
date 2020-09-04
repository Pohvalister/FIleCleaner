#ifndef MAIN_TABLE_MODEL_H
#define MAIN_TABLE_MODEL_H

#include <QAbstractTableModel>


class MainTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MainTableModel(QObject *parent = nullptr);

    int rowCnt;
    int colCnt;

    //void insert_value(int col, int raw, )

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MAIN_TABLE_MODEL_H
