#include "guihash.h"
#include "ui_guihash.h"
#include<chash.h>
#include<QFileDialog>
#include<QStringList>
#include<QMessageBox>
#include<QTextStream>
#include<QTextDocumentWriter>

GuiHash::GuiHash(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiHash)
{
    ui->setupUi(this);
    int index = ui->tabWidget->currentIndex();
    GuiHash::on_tabWidget_tabBarClicked(index);

}

GuiHash::~GuiHash()
{
    delete ui;
}

void GuiHash::on_pushButton_clicked()
{
    if (ui->lineEdit->displayText().compare("")==0)
    {
        QMessageBox::information(nullptr,"Информация","Выберите файл");
    }
    else {

        ui->textBrowser->setText(ui->lineEdit->displayText()+"   "+ReadFileByte(ui->lineEdit->displayText()));
        ui->label_4->setText("готово");
    }



}

void GuiHash::on_pushButton_2_clicked()
{
   ui->lineEdit->setText(QFileDialog::getOpenFileName(nullptr,"Открыть","","*.*"));


}

void GuiHash::on_pushButton_3_clicked()
{
    try {
        QString filter;
        QString nameSave = QFileDialog::getSaveFileName(nullptr,"Сохранить","hash","*.txt ;; *.odt", &filter);

            if(filter.contains("odt"))
            {
                QStringList docList = ui->textBrowser->toPlainText().split(QRegExp("   "));


                doc = new QTextDocument();
                QTextCursor cursors (doc);

                       cursors.movePosition(QTextCursor::Start);
                       QTextTableFormat tableformat;

                       cursors.insertTable(1,2,tableformat);
                       cursors.insertText(docList[0]);
                       cursors.movePosition(cursors.NextCell);
                       cursors.insertText(docList[1]);


                QTextDocumentWriter docwrite;
                docwrite.setFileName(nameSave);
                docwrite.setFormat("odt");

                docwrite.write(doc);
            }
            else {
                doc = ui->textBrowser->document();
                QTextDocumentWriter docwrite;
                docwrite.setFileName(nameSave);
                docwrite.setFormat("txt");
                 docwrite.write(doc);
            }






    }
    catch (...)
    {
 QMessageBox::warning(nullptr,"Ошибка","Невозможно сохранить файл",QMessageBox::Ok);
    }

}

void GuiHash::on_pushButton_5_clicked()
{


    if (ui->lineDirectory->displayText().compare("")==0)
    {
        QMessageBox::information(nullptr,"Информация","Выберите каталог");

}
    else {

ui->textDirectory->clear();
QDir dir(direct);


DirectoryHope(dir);
 ui->label_2->setText("готово");
    }
}
 void GuiHash::DirectoryHope (const QDir& dir)
    {
     try { QApplication::processEvents();

         QStringList listFile = dir.entryList(QDir::Files);
         foreach(QString file , listFile)
         {



         ui->textDirectory->append(dir.absoluteFilePath(file)+"   "+ReadDirectoryByte(dir.absoluteFilePath(file))+"\r\n");


         }

         QStringList listDir = dir.entryList(QDir::Dirs);
         foreach(QString subDir , listDir)
         {
         if (subDir == "."||subDir=="..")
         {
             continue;
          }



         DirectoryHope(QDir(dir.absoluteFilePath(subDir)));

         }

     } catch (...) {
          QMessageBox::warning(nullptr,"Ошибка","Невозможно прочитать подкаталоги",QMessageBox::Ok);
     }


}

void GuiHash::on_pushButton_4_clicked()
{

    direct = QFileDialog::getExistingDirectory(nullptr,"Каталог","");
    ui->lineDirectory->setText(direct);
}

void GuiHash::on_pushButton_6_clicked()
{
    try {

        QString filter;
        QString nameSave = QFileDialog::getSaveFileName(nullptr,"Сохранить","hash","*.txt ;; *.odt", &filter);

        if(filter.contains("odt"))
        {


            QStringList docList = ui->textDirectory->toPlainText().split(QRegExp("\n\n"));


            doc = new QTextDocument();
            QTextCursor cursors (doc);

                   cursors.movePosition(QTextCursor::Start);
                   QTextTableFormat tableformat;
                   int rows = docList.length();

                   cursors.insertTable(rows,2,tableformat);
                   for(int i = 0; i<rows;i++)
                   {
                       QStringList docRows = docList[i].split(QRegExp("   "));
                       cursors.insertText(docRows[0]);
                       cursors.movePosition(cursors.NextCell);
                       cursors.insertText(docRows[1]);
                       cursors.movePosition((cursors.NextRow));
                   }




            QTextDocumentWriter docwrite;
            docwrite.setFileName(nameSave);
            docwrite.setFormat("odt");

            docwrite.write(doc);
            delete  doc;
        }
        else {
            doc = ui->textDirectory->document();
            QTextDocumentWriter docwrite;
            docwrite.setFileName(nameSave);
            docwrite.setFormat("txt");

            docwrite.write(doc);


        }



    }
    catch (...)
    {
           QMessageBox::information(nullptr,"Ошибка","Файл не может быть сохранен");


    }




}
QString GuiHash::ReadFileByte(QString fileName)
{
    try {
        Chash *ch = new Chash();
        QFile fs(fileName);
        uint64_t Sizes = 0;
        uint value = 0;

        bool status = false;

        if(fs.open(QFile::ReadOnly))

        {
          uint64_t sizeFile = uint64_t(fs.size());
           int step = 0;
          if(uint64_t(readBlock)<sizeFile)
          {
          sizeFile = sizeFile/uint64_t(readBlock);
           ui->progressBarFile->setRange(step,int(sizeFile));
          }
          else
          {
              ui->progressBarFile->setRange(step,1);
          }





           QByteArray test;

          while((test = fs.read(readBlock)).length()>=0)
          {
              status = true;

              value = uint(test.length());

              step++;
              ui->progressBarFile->setValue(step);

              if(value == 0)
              {break;}





             ch->Initializ(test, value);
             ch->Cript();
             Sizes = Sizes+uint64_t(readBlock);
             QString s;
              s = s.setNum(Sizes);
              s =  s.append(" Byte");


              ui->label_4->setText("файл " + fileName+ " " +s);

        QCoreApplication::processEvents();



        }
          fs.close();

        if(status)
        {

            QByteArray resoult = ch->Resoult();
            QString hash (resoult.toHex());
            hash = hash.toUpper();
        delete  ch;
        return hash;
        }
        else {
            QString hash = "Файл прочитан с ошибкой";
            delete  ch;
            return hash;
        }
        }
        else
        {
               QMessageBox::information(nullptr,"Информация","Выбранный файл не доступен");
                return  "";

        }


    } catch (...) {
           QMessageBox::warning(nullptr,"Ошибка","Неудается вычислить ХЭШ файл не найден",QMessageBox::Ok);
        return  "";
    }

}
QString GuiHash::ReadDirectoryByte(QString fileName)
{
    try {
        Chash *ch = new Chash();
        QFile fs(fileName);
        uint64_t Sizes =0;
        uint value = 0;
          bool status = false;
        if(fs.open(QFile::ReadOnly))

        {
            uint64_t sizeFile = uint64_t(fs.size());
            int step = 0;
            if(uint64_t(readBlock)<=sizeFile)
            {
            sizeFile = sizeFile/uint64_t(readBlock);
            ui->progressBarDirectory->setRange(step,int(sizeFile));
            }

            else
            {

                ui->progressBarDirectory->setRange(step,1);
            }








            QByteArray test;
            while((test = fs.read(readBlock)).length()>=0)
          {
             status = true;
             value = uint(test.length());

             step ++;
             ui->progressBarDirectory->setValue(step);

             if(value == 0)
             {break;}


             ch->Initializ(test, value);
             ch->Cript();

             Sizes = Sizes+uint64_t(value);

             QString s;
             s = s.setNum(Sizes);
             s =  s.append(" Byte");

             ui->label_2->setText("файл " + fileName+ " " +s);
             QCoreApplication::processEvents();



        }

          fs.close();
          if(status)
          {

          QByteArray resoult = ch->Resoult();
          QString hash (resoult.toHex());
          hash = hash.toUpper();
          delete  ch;
          return hash;
          }
          else {
              QString hash = "Файл прочитан с ошибкой или пустой";
              delete  ch;
              return hash;
          }

        }
        else
        {
               QMessageBox::information(nullptr,"Информация","Выбранный файл не доступен");
                return  "";

        }
    }
    catch (...) {
          QMessageBox::warning(nullptr,"Ошибка","Неудается вычислить ХЭШ",QMessageBox::Ok);
          return  "";
    }


}

void GuiHash::on_pushButton_7_clicked()
{
    ui->textBrowser->clear();
     ui->label_4->setText("");
     ui->progressBarFile->reset();
}

void GuiHash::on_pushButton_8_clicked()
{
     ui->textDirectory->clear();
      ui->label_2->setText("");
      ui->progressBarDirectory->reset();
}

void GuiHash::on_pushButtonFile1_clicked()
{

    ui->lineFile1->setText(QFileDialog::getOpenFileName(nullptr,"Открыть"," ","*.txt;;*.*"));


}

void GuiHash::on_pushButtonFile2_clicked()
{
    ui->lineFile2->setText(QFileDialog::getOpenFileName(nullptr,"Открыть"," ","*.txt;;*.*"));
}


QStringList GuiHash::OpenFileCompare (QString fileName)
{

    try {

        QStringList compare;

        QFile fs(fileName);

        if(fs.open(QFile::ReadOnly))

        {

          QTextStream textStream (&fs);
          while(!textStream.atEnd())
          {
         compare.append(textStream.readLine());
        QCoreApplication::processEvents();
        }
        }
        fs.close();


        return compare;




    }
    catch (...)
    {
           QMessageBox::warning(nullptr,"Ошибка","Неудается вычислить ХЭШ файл не найден",QMessageBox::Ok);
           return{""};
    }
}

void GuiHash::on_pushButtonCompare_clicked()
{
    try {
        ui->textBrowserFile1->clear();
        ui->progressBarCompare->reset();

        QStringList compare1 = OpenFileCompare(ui->lineFile1->displayText());
        QStringList compare2 = OpenFileCompare(ui->lineFile2->displayText());

bool status = false;
int range = compare1.length();
int step = 1;
ui->progressBarCompare->setRange(step,range);

foreach (QString hash1, compare1)
{
    QString temp1 = hash1.section(QRegExp("   |\t"),1);

    if(temp1.compare("",Qt::CaseInsensitive)!=0)
    {
    foreach (QString hash2, compare2)
    {
        QString temp2 = hash2.section(QRegExp("   |\t"),1);
        if(temp2.compare(temp1,Qt::CaseInsensitive)==0)
        {

            status = true;
            break;
        }
        else
        {

            status = false;
        }
    }
    if(status)
    {

          ui->textBrowserFile1->append("STATUS: OK "+hash1.toUtf8()+"\r\n");

    }
    else {



        ui->textBrowserFile1->append("STATUS: NO FOUND "+hash1+"\r\n");

    }

    }

  ui->progressBarCompare->setValue(step++) ;

QCoreApplication::processEvents();
}



    }
    catch (...)
    {
           QMessageBox::warning(nullptr,"Ошибка","Неудается сравнить указанные файлы",QMessageBox::Ok);

    }
}

void GuiHash::on_pushButton_9_clicked()
{
    try {
        QString nameSave = QFileDialog::getSaveFileName(nullptr,"Сохранить","report","*.txt");
        QFile saveFile(nameSave);
        if(saveFile.open(QIODevice::WriteOnly))
        {
            QTextStream textStream (&saveFile);

            textStream<<ui->textBrowserFile1->toPlainText();

        }
        saveFile.close();

    }
    catch (...)
    {
           QMessageBox::information(nullptr,"Ошибка","Файл не может быть сохранен");


    }

}


void GuiHash::on_actionOpen_triggered()
{
int index = ui->tabWidget->currentIndex();
switch (index)
{
case 0: GuiHash::on_pushButton_2_clicked();
        break;
case 1: GuiHash::on_pushButton_4_clicked();
        break;
case 2: GuiHash::on_pushButtonFile1_clicked();
        GuiHash::on_pushButtonFile2_clicked();
        break;
default: break;
}

}


void GuiHash::on_actionSave_triggered()
{
    int index = ui->tabWidget->currentIndex();
    switch (index)
    {
    case 0: GuiHash::on_pushButton_3_clicked();
            break;
    case 1: GuiHash::on_pushButton_6_clicked();
            break;
    case 2: GuiHash::on_pushButton_9_clicked();

            break;
    default: break;
    }

}

void GuiHash::on_actionClear_triggered()
{
    int index = ui->tabWidget->currentIndex();
    switch (index)
    {
    case 0: GuiHash::on_pushButton_7_clicked();
            break;
    case 1: GuiHash::on_pushButton_8_clicked();
            break;
    case 2: ui->textBrowserFile1->clear();
            ui->progressBarCompare->reset();

            break;
    default: break;
    }
}

void GuiHash::on_actionAbout_triggered()
{
   QMessageBox::about(this, "Информация о программе","Данное программное обеспечение позволяет вычислить ХЭШ-значение файлов и каталогов в соответсвии с алгоритмом BELT-HASH");

}

void GuiHash::on_action_Close_triggered()
{
    QApplication::closeAllWindows();

}

void GuiHash::on_tabWidget_tabBarClicked(int index)
{
    switch (index)
    {
    case 0: ui->statusBar->showMessage("Выбран режим работы для вычисления хэш-значения фйала");
            break;
    case 1: ui->statusBar->showMessage("Выбран режим работы для вычисления хэш-значения каталога");
            break;
    case 2: ui->statusBar->showMessage("Выбран режим работы для сравнения вычисленных хэш-значений файлов");
            break;
    default: break;

    }
}


void GuiHash::on_actionFile_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
}

void GuiHash::on_actionDir_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void GuiHash::on_actionCompare_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}
