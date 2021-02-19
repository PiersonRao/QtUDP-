#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pUdpSocket = new QUdpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_Listen_clicked()
{
//    m_pUdpSocket->waitForDisconnected()
    strIP = ui->ldt_IP->text();
    nPort = ui->ldt_listen->text().toUInt();
    bool bbind = m_pUdpSocket->bind(QHostAddress::AnyIPv4, nPort,QUdpSocket::ShareAddress);
    bool bret = m_pUdpSocket->joinMulticastGroup(QHostAddress(strIP));

    if(bbind && bret)
    {
        ui->textBrowser->append("UDP bind or join ok");
    }
    else
    {
        ui->textBrowser->append("UDP bind or join Error");
    }
    connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &Widget::ReceiveUDP);
}

void Widget::on_btn_clear_clicked()
{
    ui->textBrowser->clear();
}

void Widget::ReceiveUDP()
{
    QByteArray byRecv;
    if(m_pUdpSocket->hasPendingDatagrams())
    {

        byRecv.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(byRecv.data(), byRecv.size());
        ui->textBrowser->append("收到数据："+byRecv.toHex().toUpper());
    }
}
