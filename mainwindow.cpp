#include <QtWidgets>
#include <QtDebug>
#include "mainwindow.h"
#include "photoset.h"
#include "sizedialog.h"
#include <QScrollArea>
#include <fillingdialog.h>
#include <QToolBar>
#include <QDebug>
#include<cdialog.h>
    MainWindow::MainWindow()
{
   // scrollArea->setBackgroundRole(QPalette::Dark);
    this->setWindowTitle("SimplePhotoshop");
   setWindowIcon(QIcon(":/icon/1.png"));
    //setWindowOpacity(0.94);
    //setCentralWidget(scrollArea);

    photo = new photoset;
    c = new cdialog;
   //setCentralWidget(photoset);

   //scrollArea->show();

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(photo);
    scrollArea->setWidgetResizable(true);
    //scrollArea->widget()->setMinimumSize(photoset->width(), photoset->height());

    setCentralWidget(scrollArea);

    createActions();
    createMenus();
    createToolBars();

    setWindowTitle(tr("Scribble"));
    resize(1500, 1000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            photo->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::setCanvasSize()
{
    SizeDialog *dlg = new SizeDialog;
    dlg->setWindowTitle("SetCanvasSize");
    dlg->setWindowIcon(QIcon(":/icon/3.png"));
    dlg->setWidget(photo);
    dlg->show();

}
void MainWindow::penColor()
{

    QColor newColor = QColorDialog::getColor(Qt::white,NULL,"photoset->penColor()",QColorDialog::ShowAlphaChannel);
    if (newColor.isValid())
        photo->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        photo->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        photo->setPenWidth(newWidth);
}

void MainWindow::penType()
{
     QAction *action = qobject_cast<QAction *>(sender());
     int s = action->data().toInt();
     photo->setPenType(s);
}
void MainWindow::setbgc()
{
    QColor newColor = QColorDialog::getColor(photo->getbgColor());
    if (newColor.isValid())
        photo->setbgColor(newColor);
}
void MainWindow::onZoomInImage()
{
    photo->onZoomInImage();
}
void MainWindow::onZoomOutImage()
{
    photo->onZoomOutImage();
}
void MainWindow::onPresetImage()
{
    photo->onPresetImage();
}
void MainWindow::gra()
{
    photo->graimage();
}
void MainWindow::pressed()
{
    c->onpressed();
}
void MainWindow::reset()
{
    photo->resetimage();
}
void MainWindow::masaic()
{
    photo->masaicimage();
}
void MainWindow::erase()
{
    photo->setShape(photoset::Pen);
    photo->setPenType(Qt::SolidLine);
    photo->setPenColor(QColor(255, 255, 254));
}
 void MainWindow::customDraw()
{
    photo->setShape(photoset::Pen);
}
void MainWindow::rectDraw()
{
    photo->setShape(photoset::Rect);
}
void MainWindow::ellipseDraw()
{
    photo->setShape(photoset::Ellipse);
}
void MainWindow::lineDraw()
{
    photo->setShape(photoset::Line);
}
void MainWindow::movement()
{
    photo->setMovement();
}
void MainWindow::fill()
{
    FillingDialog *fd = new FillingDialog;
    fd->setWindowIcon(QIcon(":/icon/2.png"));
    fd->setWindowTitle("SetFillingPattern");
    fd->linkWith(photo->fillbrush, photo->filling);
    fd->show();


}

void MainWindow::createActions()

{
    openAct = new QAction(QIcon(":/icon/open_file.png"),tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    resetAct = new QAction(QIcon(":/icon/revoke.png"),"还原");
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

    graAct = new QAction(QIcon("://新"),"灰度图");
    connect(graAct, SIGNAL(triggered()), this, SLOT(gra()));

    stateAct = new QAction(QIcon("://"),"拖动");
    connect(stateAct, SIGNAL(triggered()), this, SLOT(pressed()));

    masaicAct=new QAction(QIcon("://新"),"马赛克");
    connect(masaicAct, SIGNAL(triggered()), this, SLOT(masaic()));

    saveAct = new QAction(QIcon(":/icon/save_file.png"),tr("Save"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(save()));

    setCanvasSizeAct = new QAction(QIcon(":/icon/save.png"),tr("Set canvas size"), this);
    connect(setCanvasSizeAct, SIGNAL(triggered()), this, SLOT(setCanvasSize()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    QString penstyles[5] = {tr("&Solid&Line"), tr("&Dot&Line"), tr("&Dash&Line"), tr("&DashDot&Line"), tr("&DashDotDot&Line")};
    QIcon penicons[5] = {QIcon(":/icon/line.png"),QIcon(":/icon/dotline.png"),  QIcon(":/icon/dashline.png"),QIcon(":/icon/dashdotline.png"),QIcon(":/icon/dashdotdot.png")};
    int pentype[5] = {Qt::SolidLine, Qt::DotLine, Qt::DashLine, Qt::DashDotLine, Qt::DashDotDotLine};
    for(int p = 0; p < 5; p ++)
    {
        QAction *action = new QAction(penicons[p], penstyles[p], this);
        action->setData(pentype[p]);
          (action,SIGNAL(triggered()), this, SLOT(penType()));
        penStyleActs.append(action);
    }


    printAct = new QAction(QIcon(":/icon/print.png"),tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), photo, SLOT(print()));

    exitAct = new QAction(QIcon(":/icon/exit.png"),tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(QIcon(":/icon/pencolor.png"),tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    eraseAct = new QAction(QIcon(":/icon/eraser.png"),tr("&Eraser"), this);
    connect(eraseAct, SIGNAL(triggered()), this, SLOT(erase()));

    penWidthAct = new QAction(QIcon(":/icon/width.png"),tr("Pen &Width / Eraser &Width"), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    setbgcAct = new QAction(tr("Set the color of canvas"), this);
    connect(setbgcAct, SIGNAL(triggered()), this, SLOT(setbgc()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            photo, SLOT(clearImage()));

    customDrawAct = new QAction(tr("&Use pen"), this);
    connect(customDrawAct, SIGNAL(triggered()), this, SLOT(customDraw()));

    rectDrawAct = new QAction(QIcon(":/icon/rect.png"),tr("&Draw rectangle"), this);
    connect(rectDrawAct, SIGNAL(triggered()), this, SLOT(rectDraw()));

    ellipseDrawAct = new QAction(QIcon(":/icon/ellipse.png"),tr("&Draw ellipse"), this);
    connect(ellipseDrawAct, SIGNAL(triggered()), this, SLOT(ellipseDraw()));

    lineDrawAct = new QAction(QIcon(":/icon/line.png"),tr("&Draw line"), this);
    connect(lineDrawAct, SIGNAL(triggered()), this, SLOT(lineDraw()));

    movementAct = new QAction(QIcon(":/icon/move.png"),tr("&Move the selected area"), this);
    connect(movementAct, SIGNAL(triggered()), this, SLOT(movement()));

    fillAct = new QAction(QIcon(":/icon/fill.png"),tr("&Fill the shape"), this);
    connect(fillAct, SIGNAL(triggered()), this, SLOT(fill()));

    zoomInAction = new QAction(tr("Zoom In"));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(onZoomInImage()));

    zoomOutAction = new QAction(tr("Zoom Out"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(onZoomOutImage()));


    presetAction = new QAction(tr("Preset"));
    connect(presetAction, SIGNAL(triggered()), this, SLOT(onPresetImage()));

}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    penStyleMenu = new QMenu(tr("&Set pen style"), this);
    foreach(QAction *action, penStyleActs)
        penStyleMenu->addAction(action);

    photoMenu = new QMenu(tr("&photoset"), this);
    photoMenu->addAction(resetAct);
   photoMenu->addAction(graAct);
   photoMenu->addAction(masaicAct);
   photoMenu->addAction(zoomInAction);
   photoMenu->addAction(zoomOutAction);
   photoMenu->addAction(presetAction);
   photoMenu->addAction(stateAct);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Pen"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addMenu(penStyleMenu);
    optionMenu->addSeparator();
    optionMenu->addAction(eraseAct);
    optionMenu->addAction(setbgcAct);
    optionMenu->addAction(setCanvasSizeAct);
    optionMenu->addAction(clearScreenAct);


    shapeMenu = new QMenu(tr("&Shape"), this);
    shapeMenu->addAction(customDrawAct);
    shapeMenu->addAction(rectDrawAct);
    shapeMenu->addAction(ellipseDrawAct);
    shapeMenu->addAction(lineDrawAct);

    toolsMenu = new QMenu(tr("&Tools"), this);
    toolsMenu->addAction(movementAct);
    toolsMenu->addAction(fillAct);

    menuBar()->addMenu(photoMenu);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(shapeMenu);
    menuBar()->addMenu(toolsMenu);


}

void MainWindow::createToolBars()
{
    toolbar = new QToolBar(this);
    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addAction(exitAct);
    toolbar->addSeparator();

    toolbar->addAction(resetAct);
    toolbar->addAction(graAct);
    toolbar->addAction(masaicAct);
    toolbar->addSeparator();

    toolbar->addActions(penStyleActs);
    toolbar->addAction(penWidthAct);
    toolbar->addAction(penColorAct);
    toolbar->addSeparator();

    toolbar->addAction(eraseAct);
    toolbar->addAction(clearScreenAct);
    toolbar->addSeparator();

    toolbar->addAction(customDrawAct);
    toolbar->addAction(rectDrawAct);
    toolbar->addAction(ellipseDrawAct);
    toolbar->addAction(lineDrawAct);
    toolbar->addSeparator();

    toolbar->addAction(customDrawAct);
    toolbar->addAction(rectDrawAct);
    toolbar->addAction(lineDrawAct);
    toolbar->addSeparator();

    toolbar->addAction(movementAct);
    toolbar->addAction(fillAct);
    toolbar->addSeparator();


    this->addToolBar(toolbar);
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}
bool MainWindow::maybeSave()
{
    if (photo->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return photo->saveImage(fileName, fileFormat.constData());
    }
}
