#ifndef NOTEDATABASE_H
#define NOTEDATABASE_H

#include <QObject>
#include <QSqlTableModel>
#include <QtQml>

class NotesModel: public QSqlTableModel {
    Q_OBJECT
public:
    enum {IdRole = Qt::UserRole, TitleRole, ContentRole };

    NotesModel(QSqlDatabase db, QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

public slots:
    void setTitle(int row, const QString &value) { setData(index(row,0),value,TitleRole); }
    void setContent(int row, const QString &value) { setData(index(row,0),value,ContentRole); }
};

class NoteDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *model READ getModel CONSTANT)
public:
    NoteDatabase();
    QAbstractItemModel *getModel() { return m_notesTableModel; }

    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    void addNote();
private:
    QSqlTableModel *m_notesTableModel;
};

#endif // NOTEDATABASE_H
