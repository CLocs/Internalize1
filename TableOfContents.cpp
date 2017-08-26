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



    QColor randomColor(int i) {
        //https://en.wikipedia.org/wiki/Golden_angle
        const double goldenRatio = 1.6180339887498948482;
        const double goldenAngle = 1/(1+goldenRatio);
        return QColor::fromHslF(fmod(i/goldenRatio,1), 1, 0.85);
    }
}

TableOfContents::TableOfContents(QObject *parent)
    : QStandardItemModel(parent)
{
    // Sections
    auto miscSection = new QStandardItem("Misc");
    miscSection->setData(randomColor(1),SectionColor);
    auto mindMachinery = new QStandardItem("Mind Machinery");
    mindMachinery->setData(randomColor(2),SectionColor);
    appendRow(miscSection);
    appendRow(mindMachinery);

    for(int i = 3; i < 6; ++i) {
        auto more = new QStandardItem(QString("Section %1").arg(i));
        more->setData(randomColor(i),SectionColor);
        appendRow(more);
    }

    // Pages

    // Section: Misc
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
    poem->setData(readSourceFile(":/repository/DeathOfAHiredMan.txt"),Note::Roles::Content);
    miscSection->appendRow(poem);

    auto untitled1 = new QStandardItem();
    untitled1->setData("Untitled 1",TableOfContents::Roles::Title);
    untitled1->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    untitled1->setData("",Note::Roles::Content);
    miscSection->appendRow(untitled1);

    // Section: Mind Machinery
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

    auto drive = new QStandardItem();
    drive->setData("Drive",TableOfContents::Roles::Title);
    drive->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    drive->setData(readSourceFile(":/repository/drive.txt"),Note::Roles::Content);
    mindMachinery->appendRow(drive);

    auto originals = new QStandardItem();
    originals->setData("Originals",TableOfContents::Roles::Title);
    originals->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    originals->setData(readSourceFile(":/repository/originals.txt"),Note::Roles::Content);
    mindMachinery->appendRow(originals);

    auto personality_myth = new QStandardItem();
    personality_myth->setData("Personality Myth",TableOfContents::Roles::Title);
    personality_myth->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    personality_myth->setData(readSourceFile(":/repository/personality_myth.txt"),Note::Roles::Content);
    mindMachinery->appendRow(personality_myth);

    auto skills_vs_talents = new QStandardItem();
    skills_vs_talents->setData("Skills vs Talents",TableOfContents::Roles::Title);
    skills_vs_talents->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    skills_vs_talents->setData(readSourceFile(":/repository/personality_myth.txt"),Note::Roles::Content);
    mindMachinery->appendRow(skills_vs_talents);

    auto slowing_down = new QStandardItem();
    slowing_down->setData("Slowing Down",TableOfContents::Roles::Title);
    slowing_down->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    slowing_down->setData(readSourceFile(":/repository/slowing_down.txt"),Note::Roles::Content);
    mindMachinery->appendRow(slowing_down);

    auto the_18_mistakes_that_kill_startups = new QStandardItem();
    the_18_mistakes_that_kill_startups->setData("The 18 Mistakes That Kill Startups",TableOfContents::Roles::Title);
    the_18_mistakes_that_kill_startups->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    the_18_mistakes_that_kill_startups->setData(readSourceFile(":/repository/the_18_mistakes_that_kill_startups.txt"),Note::Roles::Content);
    mindMachinery->appendRow(the_18_mistakes_that_kill_startups);

    auto tim_ferriss_187_jocko = new QStandardItem();
    tim_ferriss_187_jocko->setData("Tim Ferriss 187 - Jocko Willink",TableOfContents::Roles::Title);
    tim_ferriss_187_jocko->setData(ObjectType::Note,TableOfContents::Roles::ObjectType);
    tim_ferriss_187_jocko->setData(readSourceFile(":/repository/tim_ferriss_187_jocko.txt"),Note::Roles::Content);
    mindMachinery->appendRow(tim_ferriss_187_jocko);
}

// Second, define the singleton type provider function (callback).
QObject *TableOfContents::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new TableOfContents();
}
