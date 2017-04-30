#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();
    generateMenu();
}

void Tray::generateMenu()
{
    menu = new QMenu(this);
    langFromMenu = new QMenu("Translate from", menu);
    langToMenu = new QMenu("Translate to", menu);
    menuLangFromGroup = new QActionGroup(this);
    menuLangToGroup = new QActionGroup(this);

    addLangMenuItem("from", "Autodetect", QVariant("auto"), QIcon(":/resources/lang_icons/auto.png"));
    addLangMenuItem("from", "Arabic", QVariant("arabic"), QIcon(":/resources/lang_icons/sa.png"));
    addLangMenuItem("from", "English", QVariant("spanish"), QIcon(":/resources/lang_icons/us.png"));
    addLangMenuItem("from", "French", QVariant("french"), QIcon(":/resources/lang_icons/fr.png"));
    addLangMenuItem("from", "German", QVariant("german"), QIcon(":/resources/lang_icons/de.png"));
    addLangMenuItem("from", "Italian", QVariant("italian"), QIcon(":/resources/lang_icons/it.png"));
    addLangMenuItem("from", "Japanese", QVariant("japanese"), QIcon(":/resources/lang_icons/jp.png"));
    addLangMenuItem("from", "Korean", QVariant("korean"), QIcon(":/resources/lang_icons/kr.png"));
    addLangMenuItem("from", "Portuguese", QVariant("portuguese"), QIcon(":/resources/lang_icons/pt.png"));
    addLangMenuItem("from", "Russian", QVariant("russian"), QIcon(":/resources/lang_icons/ru.png"));
    addLangMenuItem("from", "Spanish", QVariant("spanish"), QIcon(":/resources/lang_icons/es.png"));
    addLangMenuItem("from", "Ukrainian", QVariant("ukrainian"), QIcon(":/resources/lang_icons/ua.png"));

    addLangMenuItem("to", "Arabic", QVariant("arabic"), QIcon(":/resources/lang_icons/sa.png"));
    addLangMenuItem("to", "English", QVariant("spanish"), QIcon(":/resources/lang_icons/us.png"));
    addLangMenuItem("to", "French", QVariant("french"), QIcon(":/resources/lang_icons/fr.png"));
    addLangMenuItem("to", "German", QVariant("german"), QIcon(":/resources/lang_icons/de.png"));
    addLangMenuItem("to", "Italian", QVariant("italian"), QIcon(":/resources/lang_icons/it.png"));
    addLangMenuItem("to", "Japanese", QVariant("japanese"), QIcon(":/resources/lang_icons/jp.png"));
    addLangMenuItem("to", "Korean", QVariant("korean"), QIcon(":/resources/lang_icons/kr.png"));
    addLangMenuItem("to", "Portuguese", QVariant("portuguese"), QIcon(":/resources/lang_icons/pt.png"));
    addLangMenuItem("to", "Russian", QVariant("russian"), QIcon(":/resources/lang_icons/ru.png"));
    addLangMenuItem("to", "Spanish", QVariant("spanish"), QIcon(":/resources/lang_icons/es.png"));
    addLangMenuItem("to", "Ukrainian", QVariant("ukrainian"), QIcon(":/resources/lang_icons/ua.png"));

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    trayIcon->setContextMenu(menu);
}

void Tray::showMessage()
{
     trayIcon->showMessage(QString("Message"), QString("Test message"));
}

void Tray::chooseFromLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<action->data().toString();
}

void Tray::chooseToLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<action->data().toString();
}

void Tray::addLangMenuItem(QString type, QString title, QVariant data , QIcon icon)
{
    QAction *item = new QAction(title);
    item->setCheckable(true);
    item->setData(data);
    item->setIcon(icon);

    if (type == "from") {
       langFromMenu->addAction(item);
       QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseFromLang()));
       menuLangFromGroup->addAction(item);
    } else {
        langToMenu->addAction(item);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseToLang()));
        menuLangToGroup->addAction(item);
    }
}