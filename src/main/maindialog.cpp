#include "maindialog.h"

#include "src/common/stringcommon.h"
#include "src/debug/debughelper.h"
#include "src/defines/defines.h"
#include "ui_maindialog.h"

#include <QAction>
#include <QColorDialog>
#include <QDesktopServices> /// open site
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QUrl>

MainDialog::MainDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    createGUI();
    createConnects();
}
//------------------------------------------------------------------------------
MainDialog::~MainDialog()
{
    delete m_highlighter;
    delete ui;
}
//------------------------------------------------------------------------------
void MainDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: ui->retranslateUi(this); break;
        default: break;
    }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MainDialog::slotQuit()
{
    // save or not
    myDebug() << "Quit";
    qApp->quit();
}
//------------------------------------------------------------------------------
void MainDialog::slotSaveStyle()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save QSS style"), QDir::currentPath(), tr("Qt Style Sheets (*.qss)"));

    if (!filename.isNull())
    {
        QString text = ui->TECode->toPlainText();

        QFile fileOut(filename);
        if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream streamFileOut(&fileOut);
        streamFileOut.setCodec("UTF-8");
        streamFileOut << text;
        streamFileOut.flush();

        fileOut.close();
    }
}
//------------------------------------------------------------------------------
void MainDialog::slotLoadExample()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open QSS style"), "", tr("Qt Style Sheets (*.qss)"), &selectedFilter, options);
    if (!fileName.isEmpty())
    {
        QFile t_file(fileName);
        t_file.open(QIODevice::ReadOnly);
        QString t_text = QTextStream(&t_file).readAll();
        t_file.close();
        ui->TECode->setText(t_text);
        slotUpdatePreview();
    }
}
//------------------------------------------------------------------------------
void MainDialog::slotUpdatePreview()
{
    ui->widgetView->setStyleSheet(ui->TECode->toPlainText());
}
//------------------------------------------------------------------------------
void MainDialog::slotShowAboutDialog()
{
    GUI_AboutDialog = new AboutDialog();
    GUI_AboutDialog->show();
}
//------------------------------------------------------------------------------
void MainDialog::slotOpenHomePage()
{
    QDesktopServices::openUrl(QUrl(D_WEB_SITE));
}
//------------------------------------------------------------------------------
void MainDialog::slotSelectTab(int f_numberTab)
{
    ui->comBElements->clear();
    switch (f_numberTab)
    {
        case TAB_MAIN: ui->comBElements->addItems(m_listMainSettings); break;
        case TAB_INNER: ui->comBElements->addItems(m_listInnerSettings); break;
        default: myDebug() << "[ERROR]";
    }
}
//------------------------------------------------------------------------------
void MainDialog::slotPickColor()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid())
    {
        ui->LAColor->setText(color.name());
        ui->LAColor->setPalette(QPalette(color));
        ui->LAColor->setAutoFillBackground(true);
    }
}
//------------------------------------------------------------------------------
void MainDialog::slotResizePreview(int f_tabNumber)
{
    if (f_tabNumber == TAB_BASIC)
        ui->widgetView->setMinimumHeight(300);
    if (f_tabNumber == TAB_ADVANCE)
        ui->widgetView->setMinimumHeight(200);
}
//------------------------------------------------------------------------------
void MainDialog::slotAdvancedDefault()
{
    ui->widgetView->setStyleSheet("");
}
//------------------------------------------------------------------------------
void MainDialog::slotBasicDefault()
{
    ui->widgetView->setStyleSheet("");
}
//------------------------------------------------------------------------------
void MainDialog::slotBasicSave()
{
    ui->widgetView->setStyleSheet(ui->TECode->toPlainText());
    slotUpdatePreview();
}
//------------------------------------------------------------------------------
void MainDialog::slotAdvancedSave()
{
    ui->widgetView->setStyleSheet(ui->TECode->toPlainText());
    slotUpdatePreview();
}
//------------------------------------------------------------------------------
void MainDialog::slotShowTestDialog()
{
    GUI_TestDialog->setStyleSheet(ui->TECode->toPlainText());
    GUI_TestDialog->show();
}
//------------------------------------------------------------------------------
void MainDialog::slotShowTestMainWindow()
{
    GUI_TestMainWindow->setStyleSheet(ui->TECode->toPlainText());
    GUI_TestMainWindow->show();
}
//------------------------------------------------------------------------------
void MainDialog::slotOpenExample()
{
    QAction *t = qobject_cast<QAction *>(QObject::sender());
    QString t_path = ":/examples/examples/" + t->text().replace(" ", "").toLower() + ".qss";

    QFile t_file(t_path);
    t_file.open(QIODevice::ReadOnly);
    QString t_text = QTextStream(&t_file).readAll();
    t_file.close();
    ui->TECode->setText(t_text);
    slotUpdatePreview();
}
//------------------------------------------------------------------------------
void MainDialog::createConnects()
{
    connect(ui->pBSave, SIGNAL(clicked()), this, SLOT(slotSaveStyle()));
    connect(ui->pBQuit, SIGNAL(clicked()), this, SLOT(slotQuit()));
    connect(ui->pBLoad, SIGNAL(clicked()), this, SLOT(slotLoadExample()));

    connect(ui->pBTestDialog, SIGNAL(clicked()), this, SLOT(slotShowTestDialog()));
    connect(ui->pBTestMainWindow, SIGNAL(clicked()), this, SLOT(slotShowTestMainWindow()));

    // tabs
    connect(ui->pBBasicColorPicker, SIGNAL(clicked()), this, SLOT(slotPickColor()));
    connect(ui->pBBasicSave, SIGNAL(clicked()), this, SLOT(slotBasicSave()));
    connect(ui->pBBasicDefault, SIGNAL(clicked()), this, SLOT(slotBasicDefault()));

    connect(ui->pBAdvancedSave, SIGNAL(clicked()), this, SLOT(slotAdvancedSave()));
    connect(ui->pBAdvancedDefault, SIGNAL(clicked()), this, SLOT(slotAdvancedDefault()));

    connect(ui->listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(slotUpdatePreview()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(slotSelectTab(int)));

    connect(ui->pBAbout, SIGNAL(clicked()), this, SLOT(slotShowAboutDialog()));
    connect(ui->pBHomePage, SIGNAL(clicked()), this, SLOT(slotOpenHomePage()));

    connect(ui->tabs, SIGNAL(currentChanged(int)), this, SLOT(slotResizePreview(int)));
}
//------------------------------------------------------------------------------
void MainDialog::createGUI()
{
    setWindowTitle(QString("%1 - %2").arg(D_PROG_NAME).arg(D_PROG_VERSION_STR));

    QFile t_mainSettings(":/settings/txt/main_elements.txt");
    t_mainSettings.open(QIODevice::ReadOnly);
    m_listMainSettings = QTextStream(&t_mainSettings).readAll().split("\n");
    m_listMainSettings.removeAll("");
    t_mainSettings.close();

    QFile t_innerSettings(":/settings/txt/inner_elements.txt");
    t_innerSettings.open(QIODevice::ReadOnly);
    m_listInnerSettings = QTextStream(&t_innerSettings).readAll().split("\n");
    m_listInnerSettings.removeAll(""); // = removeEmptyQStringFromQStringList(&m_listInnerSettings);
    t_innerSettings.close();

    m_listMainSettings = getListFromFile(":/settings/txt/main_elements.txt");
    m_listInnerSettings = getListFromFile(":/settings/txt/inner_elements.txt");
    m_listStates = getListFromFile(":/settings/txt/states.txt");
    m_listProperties = getListFromFile(":/settings/txt/properties.txt");

    GUI_TestDialog = new TestDialog(this);
    GUI_TestMainWindow = new TestMainWindow(this);

    // QSSHighlighter *highlighter = new QSSHighlighter(ui->TECode->document());
    m_highlighter = new Highlighter(ui->TECode->document());

    ui->comBProperties->addItems(m_listProperties);
    ui->comBStates->addItems(m_listStates);

    ui->widgetView->setMinimumHeight(200);

    QMenu *m_menu = new QMenu(ui->pBExamples);
    for (int i = 0; i < D_EXAMPLES_COUNT; i++) m_menu->addAction(QString("Example %1").arg(i + 1), this, SLOT(slotOpenExample()));

    ui->pBExamples->setMenu(m_menu);
}
//------------------------------------------------------------------------------
