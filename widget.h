#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_Listen_clicked();

    void on_btn_clear_clicked();

    void ReceiveUDP();

private:
    Ui::Widget *ui;
    QUdpSocket *m_pUdpSocket;
    QString strIP;
    quint16 nPort;
};

#endif // WIDGET_H
