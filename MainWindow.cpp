#include "MainWindow.h"

/* The Constructor calls the subfunctions for creation of the sample application */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    animTime=500;
    createGuiControlComponents();
    createSubSlidingWidgets();
    createSlidingStackedWidget();
    createMainLayout();
    createConnections();
}

MainWindow::~MainWindow() {
}

void MainWindow::createGuiControlComponents() {
    int _min=500;
    int _max=1500;
    animTime=(_min+_max)>>1;

    buttonNext = new QPushButton(tr("Next"));
    buttonPrev = new QPushButton(tr("Prev"));
    checkWrap = new QCheckBox(tr("Wrap"));
    checkVertical = new QCheckBox(tr("Vertical"));
	
    listAll = new QComboBox();
    listAll->addItem(tr("Page 1"));
    listAll->addItem(tr("Page 2"));
    listAll->addItem(tr("Page 3"));
    listAll->addItem(tr("Page 4"));
    listAll->setMinimumHeight ( 40 );
	
    speedLabel = new QLabel(tr("Anim. Time:"));
    speedDisplay= new QLCDNumber();

    slideSpeed = new QSlider(Qt::Horizontal);
    slideSpeed->setMinimum(_min);
    slideSpeed->setMaximum(_max);

    //initialize slider and its display
    slideSpeed->setValue(animTime);
    speedDisplay->display(animTime);
}

void MainWindow::createMainLayout() {
    centralWidget=new QWidget(this);
    mainLayout=new QVBoxLayout();
    centralWidget->setLayout(mainLayout);
    controlPaneLayout=new QGridLayout();
    mainLayout->addWidget(slidingStacked);
    mainLayout->addLayout(controlPaneLayout);
    int row;
    row=1;
    controlPaneLayout->addWidget(buttonPrev,row,1,1,1);
    controlPaneLayout->addWidget(buttonNext,row,2,1,1);
    controlPaneLayout->addWidget(checkWrap,++row,1,1,1);
    controlPaneLayout->addWidget(checkVertical,row,2,1,1);
    controlPaneLayout->addWidget(speedLabel,++row,1,1,1);
    controlPaneLayout->addWidget(speedDisplay,row,2,1,1);	
    controlPaneLayout->addWidget(slideSpeed,++row,1,1,2);
    controlPaneLayout->addWidget(listAll,++row,1,1,2);

    this->setCentralWidget(centralWidget);
}

void MainWindow::createSubSlidingWidgets() {
    slideWidget1=new QWidget();
    slideWidget2=new QWidget();
    slideWidget3=new QWidget();
    slideWidget4=new QWidget();
    QVBoxLayout *slideWidget1layout=new QVBoxLayout();
    slideWidget1->setLayout(slideWidget1layout);
    QVBoxLayout *slideWidget2layout=new QVBoxLayout();
    slideWidget2->setLayout(slideWidget2layout);
    QVBoxLayout *slideWidget3layout=new QVBoxLayout();
    slideWidget3->setLayout(slideWidget3layout);
    QVBoxLayout *slideWidget4layout=new QVBoxLayout();
    slideWidget4->setLayout(slideWidget4layout);
    QPushButton *b11=new QPushButton("Qt");
    slideWidget1layout->addWidget(b11);
    QPushButton *b12=new QPushButton("is cool !");
    slideWidget1layout->addWidget(b12);

    QPushButton *b21=new QPushButton("Cool");
    slideWidget2layout->addWidget(b21);
    QPushButton *b22=new QPushButton("is Qt !");
    slideWidget2layout->addWidget(b22);

    QPushButton *b31=new QPushButton("Isn't");
    slideWidget3layout->addWidget(b31);
    QPushButton *b32=new QPushButton("Qt cool ?");
    slideWidget3layout->addWidget(b32);

    QPushButton *b41=new QPushButton("How cool");
    slideWidget4layout->addWidget(b41);
    QPushButton *b42=new QPushButton("is Qt !");
    slideWidget4layout->addWidget(b42);
}

void MainWindow::createSlidingStackedWidget() {
    slidingStacked= new SlidingStackedWidget(this);
    slidingStacked->addWidget(slideWidget1);
    slidingStacked->addWidget(slideWidget2);
    slidingStacked->addWidget(slideWidget3);
    slidingStacked->addWidget(slideWidget4);
    slidingStacked->setSpeed(animTime);
}

void MainWindow::createConnections() {
    QObject::connect(buttonNext,SIGNAL(pressed()),slidingStacked,SLOT(slideInNext()));
    QObject::connect(buttonPrev,SIGNAL(pressed()),slidingStacked,SLOT(slideInPrev()));
    QObject::connect(checkWrap,SIGNAL(clicked(bool)),slidingStacked,SLOT(setWrap(bool)));
    QObject::connect(checkVertical,SIGNAL(clicked(bool)),slidingStacked,SLOT(setVerticalMode(bool)));
    QObject::connect(slideSpeed,SIGNAL(valueChanged(int)),slidingStacked,SLOT(setSpeed(int)));
    QObject::connect(slideSpeed,SIGNAL(valueChanged(int)),speedDisplay,SLOT(display(int)));
    QObject::connect(listAll,SIGNAL(currentIndexChanged(int)),slidingStacked,SLOT(slideInIdx(int)));
}
