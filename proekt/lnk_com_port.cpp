#include "lnk_com_port.h"

#include <QDebug>

LNK_COM_PORT::LNK_COM_PORT(QString threadName, qint16 port)
    :name(threadName), m_portNum(port)
{

}



void LNK_COM_PORT::run()
{
    while(true)
    {
        if(connectToPort())
        {
            while(connectionStatus())
            {
                portListen();
            }
        }
        else
        {
            qDebug() << "Не удалось подключиться...";
            wait(5);
        }
    }
}

bool LNK_COM_PORT::connectToPort()
{
    /*
     * Здесь должна быть реализована функция связи с ком-портом
    */
    return true;
}
void LNK_COM_PORT::portListen()
{
    /* Здесь должны прослушиваться ком-порты и записываться затем в статический класс
     * Здесь должна применяться COM_DATA::getClass().setData(getPortNum(), raw_data)
    */
    return;
}
bool LNK_COM_PORT::connectionStatus() const
{
    return true;
}
