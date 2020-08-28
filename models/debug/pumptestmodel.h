#ifndef PUMPTESTMODEL_H
#define PUMPTESTMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractTableModel>
#include <memory>
#include <QHash>
#include <QTimer>
#include "Responses/response.h"
#include "Responses/pumpinit_command_response.h"
#include "Responses/pumpabsorb_command_response.h"
#include "Responses/pumpdispense_command_response.h"

class PumpTestModel:public QAbstractTableModel
{
    Q_OBJECT
//    QML_ELEMENT
//    QML_ADDED_IN_MINOR_VERSION(1)
    enum TableRoles{
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };
public:
    explicit PumpTestModel(QObject *parent = nullptr);
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray>roleNames()const override;
public:
    inline void setResponseList(QList<std::shared_ptr<Response>> &value){_responseList = value;}
    inline const QList<std::shared_ptr<Response>> responseList()const{return _responseList;}
    void refresh();

public:
    QVariant getInitResult(const QModelIndex &index, int role);
    QVariant getAbsorbResult(const QModelIndex &index, int role);
    QVariant getDispenseResult(const QModelIndex &index, int role);
private:
    QList<std::shared_ptr<Response>> _responseList;
    QList<QList<QString>> _tableData;
    QTimer _timer;
    bool _isFirstRefresh;
};

#endif // PUMPTESTMODEL_H
