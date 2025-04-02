#ifndef FILEADAPTER_H
#define FILEADAPTER_H

#include <QObject>

class MainWindow;

class FileAdapter final : public QObject
{
    Q_OBJECT
public:
    explicit FileAdapter(MainWindow *parent = nullptr);

signals:
    void sigFileOpened(const QString &filePath);
    void sigFileSaved(const QString &filePath);

public slots:
    void slotNew(const QString &filePath);
    void slotOpenFile(const QString &filePath);
    void slotSaveFile(const QString &filePath);

    void slotUndo();
    void slotRedo();
private:
    MainWindow *m_mainWnd{nullptr};
};

#endif // FILEADAPTER_H