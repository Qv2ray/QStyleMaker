#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "src/dialogs/about/about.h"
#include "src/dialogs/qsseditor/highlighter.h"
#include "src/dialogs/test/testdialog.h"
#include "src/dialogs/test/testmainwindow.h"

#include <QDialog>
namespace Ui
{
    class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

  protected:
    void changeEvent(QEvent *e);

  private slots:
    void slotSaveStyle();
    void slotShowTestDialog();
    void slotShowTestMainWindow();
    void slotQuit();

    void slotUpdatePreview();
    void slotShowAboutDialog();
    void slotOpenHomePage();
    void slotLoadExample();

    void slotPickColor();
    void slotBasicSave();
    void slotBasicDefault();

    void slotAdvancedSave();
    void slotAdvancedDefault();

    void slotSelectTab(int);
    void slotResizePreview(int);

    void slotOpenExample();

  private:
    Ui::MainDialog *ui;

    AboutDialog *GUI_AboutDialog;
    TestMainWindow *GUI_TestMainWindow;
    TestDialog *GUI_TestDialog;
    Highlighter *m_highlighter;

    void createConnects();
    void createGUI();

    QStringList m_listMainSettings;
    QStringList m_listInnerSettings;
    QStringList m_listProperties;
    QStringList m_listStates;

    enum m_TABS
    {
        TAB_MAIN = 0,
        TAB_INNER
    };

    enum m_TABS_Q
    {
        TAB_BASIC = 0,
        TAB_ADVANCE
    };
};

#endif // MAINDIALOG_H
