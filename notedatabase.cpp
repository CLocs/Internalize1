#include "notedatabase.h"

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>



NoteDatabase::NoteDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dataFolder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if(dataFolder.mkpath(dataFolder.path())) {
        db.setDatabaseName(dataFolder.filePath("notes"));
        db.open();
    }

    auto error = db.exec("CREATE TABLE IF NOT EXISTS notes (id int primary key, title TEXT, content TEXT)").lastError();

    m_notesTableModel = new NotesModel(db,this);
    m_notesTableModel->select();
}

// Second, define the singleton type provider function (callback).
QObject *NoteDatabase::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new NoteDatabase();
}

void NoteDatabase::addNote()
{
    m_notesTableModel->insertRow(0);
    m_notesTableModel->setData(m_notesTableModel->index(0,0),"Untitled Note",NotesModel::TitleRole);
    if(!m_notesTableModel->submitAll()) {
        auto err = m_notesTableModel->lastError();
        throw err;
    }
}

NotesModel::NotesModel(QSqlDatabase db, QObject *parent)
    : QSqlTableModel(parent,db)
{
    setTable("notes");
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

QHash<int, QByteArray> NotesModel::roleNames() const {
    QHash<int,QByteArray> names;
    names.insert(IdRole,"id");
    names.insert(TitleRole,"title");
    names.insert(ContentRole,"content");
    return names;
}

QVariant NotesModel::data(const QModelIndex &index, int role) const {
    switch(role) {
    case IdRole: return data(index.sibling(index.row(),fieldIndex("id")),Qt::EditRole);
    case TitleRole: return data(index.sibling(index.row(),fieldIndex("title")),Qt::EditRole);
    case ContentRole: return data(index.sibling(index.row(),fieldIndex("content")),Qt::EditRole);
    default: return QSqlTableModel::data(index,role);
    }
}

bool NotesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    switch(role) {
    case IdRole: return setData(index.sibling(index.row(),fieldIndex("id")),value, Qt::EditRole);
    case TitleRole: return setData(index.sibling(index.row(),fieldIndex("title")),value, Qt::EditRole);
    case ContentRole: return setData(index.sibling(index.row(),fieldIndex("content")),value, Qt::EditRole);
    default: return QSqlTableModel::setData(index,value,role);
    }
}
