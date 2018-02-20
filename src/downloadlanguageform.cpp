#include "downloadlanguageform.h"
#include "ui_downloadlanguageform.h"
#include "ui_downloadlanguageitem.h"

DownloadLanguageForm::DownloadLanguageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadLanguageForm)
{
    ui->setupUi(this);

    foreach (Lang language, Language::languages) {
        addLanguage(language.name, ":/resources/lang_icons/" + language.shortName + ".png", Language::isDownloaded(language.name));
    }
}

DownloadLanguageForm::~DownloadLanguageForm()
{
    delete ui;
}

void DownloadLanguageForm::showForm()
{
    this->show();
}

void DownloadLanguageForm::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void DownloadLanguageForm::addLanguage(QString name, QString iconPath, bool isDownloaded)
{
    DownloadLanguageItem *downloadLanguageItem = new DownloadLanguageItem(name, iconPath, isDownloaded);
    connect(downloadLanguageItem, SIGNAL(downloadStart()), this, SLOT(downloadStart()));
    connect(downloadLanguageItem, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(downloadLanguageItem, SIGNAL(downloadFinished(QNetworkReply*)), this, SLOT(onDownloadFinished(QNetworkReply*)));

    QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);

    ui->listWidget->addItem(listItem);
    ui->listWidget->setItemWidget(listItem, downloadLanguageItem);

    listItem->setSizeHint(QSize(downloadLanguageItem->width(),downloadLanguageItem->height()));
}

void DownloadLanguageForm::downloadStart()
{
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        DownloadLanguageItem *widget = qobject_cast<DownloadLanguageItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        widget->ui->pushButton->setEnabled(false);
    }

    ui->progressBar->reset();
    ui->progressBar->setFormat("Downloaded: %p%");
}

void DownloadLanguageForm::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal) {
    ui->progressBar->setValue(static_cast<int>(100.0 * bytesRead / bytesTotal));
}

void DownloadLanguageForm::onDownloadFinished(QNetworkReply *reply) {
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        DownloadLanguageItem *widget = qobject_cast<DownloadLanguageItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        widget->ui->pushButton->setEnabled(true);

        if (Language::isDownloaded(widget->name)) {
            widget->ui->pushButton->setText("Remove");
        }
    }
}
