#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QtWidgets>

struct Lang
{
  QString name;
  QString shortName;
  QString googleName;
  QString url;
};

class Language : public QObject
{
public:
    explicit Language(QObject *parent = nullptr);
    static QList<Lang> languages;

    // Helper methods
    static QString getUrl(QString name);
    static QString getFileName(QString name);
    static QString getShortName(QString name);
    static QString getGoogleName(QString name);
    static QString getNameByUrl(QString url);
    static bool isDownloaded(QString name);

private:
    static Lang find(QString name);
};

#endif // LANGUAGE_H
