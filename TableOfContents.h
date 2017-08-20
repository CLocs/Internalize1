#ifndef TABLEOFCONTENTS_H
#define TABLEOFCONTENTS_H

#include <QStandardItemModel>
#include <QtQml>

class ObjectType {
    Q_GADGET
    Q_ENUMS(ObjectTypeEnum)
public:
    enum ObjectTypeEnum{
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
        URL = ObjectTypeRoleBase+1 /* QUrl */
    };
};

class Image {
    Q_GADGET
    Q_ENUMS(Roles)
public:
    enum Roles {
        URL = ObjectTypeRoleBase+1 /* QUrl */
    };
};


class TableOfContents : public QStandardItemModel
{
    Q_OBJECT
    Q_ENUMS(Roles NodeType)
public:
    enum Roles {
        Title = Qt::DisplayRole, /* QString */
        SectionColor = Qt::BackgroundColorRole,

        ObjectType = Qt::UserRole,
        LinksTo,
        LinksFrom,

        // TODO: these need to be kept distinct, how to map them to the Object types above?
        Content = ObjectTypeRoleBase,
        URL
    };

    TableOfContents(QObject *parent = 0);

    QHash<int,QByteArray> roleNames() const override {
        static const auto roles = QStandardItemModel::roleNames().unite({
                {Title,"title"},
                {SectionColor,"sectionColor"},
                {ObjectType, "objectType"},
                {Content, "content"},
                {URL, "url"}
            });
        return roles;
    }

    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
};

#endif // TABLEOFCONTENTS_H
