#ifndef GUIHASH_H
#define GUIHASH_H
#include <QString>
#include <QFileDialog>
#include <QMainWindow>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>

namespace Ui {
class GuiHash;
}

class GuiHash : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiHash(QWidget *parent = nullptr);
    QString direct;
    const int readBlock = 1048576;

    ~GuiHash();
    QString ReadFileByte (QString fileName);
    QString ReadDirectoryByte(QString fileName);
    void DirectoryHope (const QDir& dir);
    QStringList OpenFileCompare (QString fileName);

private:
    Ui::GuiHash *ui;
    QTextDocument *doc;



private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButtonFile1_clicked();
    void on_pushButtonFile2_clicked();
    void on_pushButtonCompare_clicked();
    void on_pushButton_9_clicked();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClear_triggered();
    void on_actionAbout_triggered();
    void on_action_Close_triggered();
    void on_tabWidget_tabBarClicked(int index);
    void on_actionFile_triggered();
    void on_actionDir_triggered();
    void on_actionCompare_triggered();
    void on_tabWidget_currentChanged(int index);
};

#endif // GUIHASH_H
