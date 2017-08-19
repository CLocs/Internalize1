#ifndef TABLEOFCONTENTS_H
#define TABLEOFCONTENTS_H

#include <QStandardItemModel>
#include <QtQml>

class ObjectType {
public:
    enum {
        Note,
        WebPage,
        Image
    };
};

const int ObjectTypeRoleBase = Qt::UserRole + 0x100;

class Note {
    Q_GADGET
    Q_ENUMS(Roles)
public:
    enum Roles {
        Content = ObjectTypeRoleBase /* QString, HTML for QTextDocument */
    };
};

class WebPage {
    Q_GADGET
    Q_ENUMS(Roles)
public:
    enum Roles {
        URL = ObjectTypeRoleBase /* QUrl */
    };
};

class Image {
    Q_GADGET
    Q_ENUMS(Roles)
public:
    enum Roles {
        URL = ObjectTypeRoleBase /* QUrl */
    };
};


class TableOfContents : public QStandardItemModel
{
    Q_OBJECT
    Q_ENUMS(Roles NodeType)
public:
    enum Roles {
        Title = Qt::DisplayRole, /* QString */
        LinksTo,
        LinksFrom,

        ObjectType = Qt::UserRole,

    };

    TableOfContents(QObject *parent = 0);

    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
};

#endif // TABLEOFCONTENTS_H
