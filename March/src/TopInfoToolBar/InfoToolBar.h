#ifndef INFOTOOLBAR_H
#define INFOTOOLBAR_H

#include <QToolBar>

class InfoToolBar final : public QToolBar
{
    Q_OBJECT
public:
    explicit InfoToolBar(QWidget* parent = nullptr);

signals:
    void sigNewFile();
    void sigOpenFile();
    void sigSaveFile();
    void sigCut();
    void sigCopy();
    void sigPaste();

private:
    void initUI();

private:
    QAction* m_actNew{ nullptr };
    QAction* m_actOpen{ nullptr };
    QAction* m_actSave{ nullptr };
    QAction* m_actCut{ nullptr };
    QAction* m_actCopy{ nullptr };
    QAction* m_actPaste{ nullptr };
};

#endif // INFOTOOLBAR_H