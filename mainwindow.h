#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>
#include <QWidget>
class photoset;
class cdialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void setbgc();
    void setCanvasSize();
    void penColor();
    void penWidth();
    void penType();
    void customDraw();
    void rectDraw();
    void ellipseDraw();
    void lineDraw();
    void erase();
    void movement();
    void fill();
    void gra();
    void reset();
    void masaic();
    void pressed();
    void onZoomInImage();
    void onZoomOutImage();
    void onPresetImage();
private:
    void createActions();
    void createMenus();
    void createToolBars();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    photoset *photo;
    cdialog *c;
    QScrollArea *scrollArea;
    QMenu *saveAsMenu;
    QMenu *photoMenu;
    QMenu *penStyleMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *shapeMenu;
    QMenu *toolsMenu;
    QToolBar *toolbar;


    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *saveAct;
    QAction *exitAct;
    QAction *setCanvasSizeAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QList<QAction *> penStyleActs;
    QAction *eraseAct;
    QAction *printAct;

    QAction *setbgcAct;
    QAction *clearScreenAct;
    QAction *customDrawAct;
    QAction *rectDrawAct;
    QAction *ellipseDrawAct;
    QAction *lineDrawAct;
    QAction *movementAct;
    QAction *fillAct;

    QList<QAction *> photoActs;
    QAction *graAct;
    QAction *resetAct;
    QAction *masaicAct;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *presetAction;
    QAction *stateAct;


};


#endif
