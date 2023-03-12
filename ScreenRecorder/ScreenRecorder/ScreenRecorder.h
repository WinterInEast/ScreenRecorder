#pragma once
#include <QtWidgets/QWidget>
#include "ui_ScreenRecorder.h"
#include "TitleBar.h"
#include "UtilsWrapper.h"
#include <memory>
#include <QTimer>


class ScreenRecorder : public QWidget
{
    Q_OBJECT

public:
    ScreenRecorder(QWidget *parent = nullptr);
    ~ScreenRecorder();

    void LoadQSS(QString qssPath);

public slots:
    void on_btnRec_clicked();
    void on_timer_timeout();
    void on_btnSearch_clicked();

private:
    Ui::ScreenRecorderClass ui;
    TitleBar* m_pTitle;
    std::unique_ptr<UtilsWrapper> m_pUtilsWrapper;
    QTimer* m_pTimer;
    REC_OBJ m_recObj;

    bool m_isRecording = false;
    int m_RecSeconds = 0;
};
