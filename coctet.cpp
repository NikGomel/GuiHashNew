#include "coctet.h"
#include<QByteArray>
#include<QString>
#include<QBuffer>
#include <QDataStream>
#include<QIODevice>


Octet Octet::plus(Octet a, uint b)
{

    Octet c = {0,0,0,0};
   // quint64 temp = 0;
    uint64_t temp = 0;
    uint64_t ost =0;
    uint64_t mod = 0x100000000;
    //step1
    temp = uint64_t(a.u4) + b;
    ost = temp % mod;
    temp = temp >> 32;
    c.u4 = uint(ost);
    //step2
    temp = uint64_t(a.u3)+temp;
    ost = temp % mod;
    temp = temp >> 32;
    c.u3 = uint(ost);
    //step3
    temp = uint64_t(a.u2)+temp;
    ost = temp % mod;
    temp = temp >> 32;
    c.u2 = uint(ost);
    //step4
    temp = uint64_t(a.u1)+temp;
    ost = temp % mod;
    c.u1 = uint(ost);


    return  c;
}
uint Octet32::convert(uint x)
{
    uint a =x>>24;
    uint b =x&0x00ff0000;
    b = b>>8;
    uint c =x&0x0000ff00;
    c = c<<8;
    uint d =x<<24;
    x = a^b^c^d;
    return x;
}

QByteArray Octet32::transformationByte(Octet32 x)
{


    x.u1 = Octet32::convert(x.u1);
    x.u2 = Octet32::convert(x.u2);
    x.u3 = Octet32::convert(x.u3);
    x.u4 = Octet32::convert(x.u4);
    x.u5 = Octet32::convert(x.u5);
    x.u6 = Octet32::convert(x.u6);
    x.u7 = Octet32::convert(x.u7);
    x.u8 = Octet32::convert(x.u8);


    QByteArray test;
    QBuffer buffer (&test);
    buffer.open(QIODevice::WriteOnly);

    QDataStream dd(&buffer);
    dd << x.u1<<x.u2<<x.u3<<x.u4<<x.u5<<x.u6<<x.u7<<x.u8;
    buffer.close();
    return test;
}
