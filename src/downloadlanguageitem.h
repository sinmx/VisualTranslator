#ifndef DOWNLOADLANGUAGEITEM_H
#define DOWNLOADLANGUAGEITEM_H

#include <QWidget>
#include <networkfiledownloader.h>
#include <language.h>

namespace Ui {
class DownloadLanguageItem;
}

class DownloadLanguageItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadLanguageItem(QString name, QString iconPath, bool isDownloaded, QWidget *parent = 0);
    ~DownloadLanguageItem();
    Ui::DownloadLanguageItem *ui;
    QString name;

private slots:
    void on_pushButton_clicked();

private:
    void downloadButtonClicked();
    void removeButtonClicked();

signals:
    void downloadStart();
    void downloadFinished(QNetworkReply*);
    void downloadProgress(qint64 bytesRead, qint64 bytesTotal);
};

#endif // DOWNLOADLANGUAGEITEM_H
