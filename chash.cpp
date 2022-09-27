#include "chash.h"
#include "coctet.h"
#include<QString>
#include<QByteArray>
#include <QDataStream>
#include<QIODevice>
#include<QFile>
#include<QBuffer>
#include<QTextStream>
#include<guihash.h>
#include <QLabel>
Chash::Chash()
{
count = {0,0,0,0} ;
H = {0xc8ba94b1, 0x3bf5080a, 0x8e006d36, 0xe45d4a58, 0x9dfa0485, 0xacc7b61b, 0xc2722e25, 0x0dcefd02};
X = {0,0,0,0,0,0,0,0};
S ={0,0,0,0} ;
}
Chash::~Chash()
{

}
Octet Chash::BCript(Octet Xi, Octet32 key)
      {

            k[0] = k[8] = k[16] = k[24] = k[32] = k[40] = k[48] = key.u1;
            k[1] = k[9] = k[17] = k[25] = k[33] = k[41] = k[49] = key.u2;
            k[2] = k[10] = k[18] = k[26] = k[34] = k[42] = k[50] = key.u3;
            k[3] = k[11] = k[19] = k[27] = k[35] = k[43] = k[51] = key.u4;
            k[4] = k[12] = k[20] = k[28] = k[36] = k[44] = k[52] = key.u5;
            k[5] = k[13] = k[21] = k[29] = k[37] = k[45] = k[53] = key.u6;
            k[6] = k[14] = k[22] = k[30] = k[38] = k[46] = k[54] = key.u7;
            k[7] = k[15] = k[23] = k[31] = k[39] = k[47] = k[55] = key.u8;


          uint temp,e = 0;
              for (uint i = 1; i < 9; i++)
          {



              Xi.u2 = Xi.u2 ^ Rh5(uint(((Xi.u1 + k[7 * i - 7]) % pow)));

              Xi.u3 = (Xi.u3 ^ Rh21(uint(((Xi.u4 + k[7 * i - 6]) % pow))));


              Xi.u1 = (Xi.u1 - Rh13(uint(((Xi.u2 + k[7 * i - 5]) % pow))));

              e = (Rh21(uint(((Xi.u2 + Xi.u3 + k[7 * i - 4]) % pow)))^uint((i%pow)));
              Xi.u2 = uint(((Xi.u2 + e) % pow));
              Xi.u3 = uint(((Xi.u3 - e) % pow));
              Xi.u4 = (Xi.u4 + Rh13(uint(((Xi.u3 + k[7 * i - 3] % pow)))));
              Xi.u2 = (Xi.u2 ^ Rh21(uint(((Xi.u1 + k[7 * i - 2]) % pow))));
              Xi.u3 = (Xi.u3 ^ Rh5(uint(((Xi.u4 + k[7 * i - 1]) % pow))));
              temp = Xi.u1;
              Xi.u1 = Xi.u2;
              Xi.u2 = temp;
              temp = Xi.u3;
              Xi.u3 = Xi.u4;
              Xi.u4 = temp;
              temp = Xi.u2;
              Xi.u2 = Xi.u3;
              Xi.u3 = temp;

          }


          Octet cript = {Xi.u2, Xi.u4, Xi.u1, Xi.u3};
          return cript;

      }


      uint Chash::Rh21(uint a)
      {

          return H21[a & 255] ^ H29[a >> 8 & 255] ^ H5[a >> 16 & 255] ^ H13[a >> 24];
      }
      uint Chash::Rh5(uint a)
      {

          return H5[a & 255] ^ H13[a >> 8 & 255] ^ H21[a >> 16 & 255] ^ H29[a >> 24];
      }
      uint Chash:: Rh13(uint a)
      {


          return H13[a & 255] ^ H21[a >> 8 & 255] ^ H29[a >> 16 & 255] ^ H5[a >> 24];
      }


  void Chash::Initializ(QByteArray inform, uint value)
      {
      if (value % 32 != 0)
                {
                    uint n = 32 - (value % 32);


                    count = Octet::plus(count,value*8);

                      this->inform = inform;

                     this->inform.resize(int((value+n)));

                    int b = this->inform.size();

              for(uint i = value; i<uint(b); i++)
              {
              this->inform[i] = 0x00;

              }


                }
                else
                {
          count = Octet::plus(count,value*8);
            this->inform = inform;
      }



      }
       void Chash::Cript()
      {


          Octet sig1;




          for (int i = 0; i < (inform.size() / 32); i++)
          {

              X.u1 = uint(uint8_t(inform.at(i*32+3))<<24^uint8_t(inform.at(i*32+2))<<16^uint8_t(inform.at(i*32+1))<<8^uint8_t(inform.at(i*32)));
              X.u2 = uint(uint8_t(inform.at(i*32+7))<<24^uint8_t(inform.at(i*32+6))<<16^uint8_t(inform.at(i*32+5))<<8^uint8_t(inform.at(i*32+4)));
              X.u3 = uint(uint8_t(inform.at(i*32+11))<<24^uint8_t(inform.at(i*32+10))<<16^uint8_t(inform.at(i*32+9))<<8^uint8_t(inform.at(i*32+8)));
              X.u4 = uint(uint8_t(inform.at(i*32+15))<<24^uint8_t(inform.at(i*32+14))<<16^uint8_t(inform.at(i*32+13))<<8^uint8_t(inform.at(i*32+12)));
              X.u5 = uint(uint8_t(inform.at(i*32+19))<<24^uint8_t(inform.at(i*32+18))<<16^uint8_t(inform.at(i*32+17))<<8^uint8_t(inform.at(i*32+16)));
              X.u6 = uint(uint8_t(inform.at(i*32+23))<<24^uint8_t(inform.at(i*32+22))<<16^uint8_t(inform.at(i*32+21))<<8^uint8_t(inform.at(i*32+20)));
              X.u7 = uint(uint8_t(inform.at(i*32+27))<<24^uint8_t(inform.at(i*32+26))<<16^uint8_t(inform.at(i*32+25))<<8^uint8_t(inform.at(i*32+24)));
              X.u8 = uint(uint8_t(inform.at(i*32+31))<<24^uint8_t(inform.at(i*32+30))<<16^uint8_t(inform.at(i*32+29))<<8^uint8_t(inform.at(i*32+28)));


              sig1 = Sig1(X,H);
              S = Mode16(S, sig1);
              H = Sig2(X, H);

          }
      }

         QByteArray Chash::Resoult ()
          {

          Octet32 x = {count.u4, count.u3, count.u2, count.u1, S.u1, S.u2, S.u3, S.u4};

          x = Sig2(x,H);
          QByteArray resuolt;

          resuolt = Octet32::transformationByte(x);

          return resuolt;
      }


        Octet32 Chash::Sig2(Octet32 xi, Octet32 h)
   {

          Octet buf = Sig1(xi,h);

          Octet32 key1 = {buf.u1, buf.u2, buf.u3, buf.u4, h.u5, h.u6, h.u7,h.u8};

          Octet32 key2 = {buf.u1 ^ 0xffffffff, buf.u2 ^ 0xffffffff, buf.u3 ^ 0xffffffff, buf.u4 ^ 0xffffffff,h.u1, h.u2,h.u3,h.u4};



     Octet u1 = {xi.u1, xi.u2, xi.u3, xi.u4};

          Octet u2 = {xi.u5, xi.u6, xi.u7, xi.u8};

          buf = BCript(u1, key1);

          buf = Mode16(buf,u1);
          xi.u1 = buf.u1;
          xi.u2 = buf.u2;
          xi.u3 = buf.u3;
          xi.u4 = buf.u4;


          buf = BCript(u2, key2);

          buf = Mode16(buf, u2);
          xi.u5 = buf.u1;
          xi.u6 = buf.u2;
          xi.u7 = buf.u3;
          xi.u8 = buf.u4;

          return xi;


   }

      Octet Chash::Sig1(Octet32 xi, Octet32 h)
      {
          Octet temp = Mode(h);
          Octet temp2 = temp;


          temp = BCript(temp, xi);

          temp.u1 = temp.u1 ^ temp2.u1;
          temp.u2 = temp.u2 ^ temp2.u2;
          temp.u3 = temp.u3 ^ temp2.u3;
          temp.u4 = temp.u4 ^ temp2.u4;

          return temp;


      }

       Octet Chash::Mode(Octet32 h)
      {
          Octet temp;
          temp.u1 = h.u1 ^ h.u5;
          temp.u2 = h.u2 ^ h.u6;
          temp.u3 = h.u3 ^ h.u7;
          temp.u4 = h.u4 ^ h.u8;

          return temp;
      }
       Octet Chash::Mode16(Octet a,Octet b)
      {

          a.u1 = a.u1 ^ b.u1;
          a.u2 = a.u2 ^ b.u2;
          a.u3 = a.u3 ^ b.u3;
          a.u4 = a.u4 ^ b.u4;

          return a;
      }



