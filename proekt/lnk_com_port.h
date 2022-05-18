#ifndef LNK_COM_PORT_H
#define LNK_COM_PORT_H

#include <QThread>
#include <QMap>
#include <QDebug>

class COM_DATA
{
    COM_DATA();
    COM_DATA(const COM_DATA&) = delete;
    COM_DATA(const COM_DATA&&) = delete;
    COM_DATA& operator=(const COM_DATA&) = delete;
    COM_DATA& operator=(const COM_DATA&&) = delete;

    static QMap<uint, QString> data;
public:
    static COM_DATA& getClass()
    {
        static COM_DATA com_data;
        return com_data;
    }

    QString* getData(uint key) const {return &data[key]; }
    void setData(uint key, QByteArray raw_data) { data[key] = QString(raw_data); qDebug() << "Даннные в " << key << " были успешно записаны";}
};

class LNK_COM_PORT : public QThread
{
public:
    explicit LNK_COM_PORT(QString threadName, qint16 port);
    LNK_COM_PORT(){}

    QString getName() const {return name;}
    qint16 getPortNum() const {return m_portNum;}
    bool connectionStatus() const;
    void portListen();
private:
    QString name;
    qint16 m_portNum;

    bool connectToPort();
protected:
    void run();
};

#endif // LNK_COM_PORT_H
