#include "TableOfContents.h"

#include <QFile>

namespace {
    QString readSourceFile(QString filename) {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly)) {
            return QString::fromUtf8(file.readAll());
        } else {
            return QString();
        }
    }
}

TableOfContents::TableOfContents(QObject *parent)
    : QStandardItemModel(parent)
{
    auto miscSection = new QStandardItem("Misc");
    auto mindMachinery = new QStandardItem("Mind Machinery");
    appendRow(miscSection);
    appendRow(mindMachinery);

    auto slateStarCodex = new QStandardItem();
    slateStarCodex->setData("Slate Star Codex",TableOfContents::Roles::Title);
    slateStarCodex->setData(ObjectType::WebPage,TableOfContents::Roles::ObjectType);
    slateStarCodex->setData("http://slatestarcodex.com/",WebPage::Roles::URL);
    miscSection->appendRow(slateStarCodex);

    auto internalizeOrgChart = new QStandardItem();
    internalizeOrgChart->setData("Internalize Org Chart",TableOfContents::Roles::Title);
    internalizeOrgChart->setData(ObjectType::Image,TableOfContents::Roles::ObjectType);
    internalizeOrgChart->setData("Internalize-Demo1.svg",Image::Roles::URL);
    miscSection->appendRow(internalizeOrgChart);


    auto poem = new QStandardItem();
    poem->setData("Death of a Hired Man",TableOfContents::Roles::Title);
    poem->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    poem->setData(readSourceFile(":/repository/DeathOfAHiredMap.txt"),Note::Roles::Content);
    miscSection->appendRow(poem);

    auto thinkingFastAndSlow = new QStandardItem();
    thinkingFastAndSlow->setData("Thinking Fast and Slow",TableOfContents::Roles::Title);
    thinkingFastAndSlow->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    thinkingFastAndSlow->setData(readSourceFile(":/repository/thinking-fast-and-slow.txt"),Note::Roles::Content);
    mindMachinery->appendRow(thinkingFastAndSlow);

    auto sapiens = new QStandardItem();
    sapiens->setData("Sapiens",TableOfContents::Roles::Title);
    sapiens->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    sapiens->setData(readSourceFile(":/repository/sapiens.txt"),Note::Roles::Content);
    mindMachinery->appendRow(sapiens);

    auto onIntelligence = new QStandardItem();
    onIntelligence->setData("On Intelligence",TableOfContents::Roles::Title);
    onIntelligence->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    onIntelligence->setData(readSourceFile(":/repository/on-intelligence.txt"),Note::Roles::Content);
    mindMachinery->appendRow(onIntelligence);
}

// Second, define the singleton type provider function (callback).
QObject *TableOfContents::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new TableOfContents();
}
