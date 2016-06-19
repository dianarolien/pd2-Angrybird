#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QGraphicsTextItem>
#include <QLabel>
#include "mycontactlistener.h"
#include <QMediaPlayer>

MyContactListener my;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    score = 0;
    key = 0;
    key1 = 0;
    key2 = 0;
    key3 = 0;
    key4 = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

b2Vec2 MainWindow::calculate(int a, int b)
{
    b2Vec2 b2;
    b2.x = (a*bird->g_worldsize.width())/bird->g_windowsize.width()+ bird->g_size.width()/2;
    b2.y = -(bird->g_worldsize.height()*b)/bird->g_windowsize.height()-bird->g_size.height()/2+bird->g_worldsize.height();
    return b2;
}

void MainWindow::showEvent(QShowEvent *)
{
    setWindowTitle(tr("Angry bird"));

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());

    //設定背景圖片
    QPixmap *pixmap = new QPixmap(":/image/background.png");
    scene->setBackgroundBrush(pixmap->scaled(720,540,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);

    //背景音樂
    QMediaPlayer * bgm = new QMediaPlayer();
    bgm->setMedia(QUrl("qrc:/player_battle.mp3"));
    bgm->play();

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,2,QPixmap(":/ground.png"),world,scene));

    world->SetContactListener(&my);

    form = new Form();

    // Create the slingshot
    Slingshot *sling =  new Slingshot();
    scene->addItem(sling);

    // Create bird (You can edit here)
    bird = new Bird(5,6.333333333f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/18.0,height()/18.0),world,scene);
    itemList.push_back(bird);

    //Create woods
    wood = new Wood(20.0,4.f,0.6,3,8,&timer,QPixmap(":/image/thinwood1.png"),world,scene);
    wood2 = new Wood(24.0,4.f,0.6,3,8,&timer,QPixmap(":/image/thinwood1.png"),world,scene);
    wood3 = new Wood(22.0f,5.8f,4.8,0.5f,1,&timer,QPixmap(":/image/thinwood.png"),world,scene);
    //Create a enimy
    enimy = new Enimy(22,3.0f,0.27f,&timer,QPixmap(":/image/enimy.png").scaled(height()/17.0,height()/17.0),world,scene);


    // Set label
    QLabel *label =  new QLabel(this);

    //設置字體大小
    QFont ft;
    ft.setPointSize(16);
    label->setFont(ft);

    //設置字體顏色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    label->setPalette(pa);

    QString str = QString("過關條件：以蛋擊豬 ");
    label->setText(str);
    label->setGeometry(50,30,500,100);        //設定位置大小
    label->setAlignment(Qt::AlignLeft);
    scene->addWidget(label);
    label->show();

    // Set label -score
    label2 =  new QLabel(this);

    //設置字體大小
    QFont ft2;
    ft2.setPointSize(16);
    label2->setFont(ft2);

    //設置字體顏色
    QPalette pa2;
    pa2.setColor(QPalette::WindowText,Qt::white);
    label2->setPalette(pa2);

    QString str2 = QString("Score : "+QString::number(score)+" / 10000");
    label2->setText(str2);
    label2->setGeometry(50,55,500,100);        //設定位置大小
    label2->setAlignment(Qt::AlignLeft);
    scene->addWidget(label2);
    label2->show();


    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(check()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        std::cout << "Press !" << std::endl ;
        key =1;

        // The second bird create
        if( key1 == 1 && key2 == 0 )
        {
           bird2 = new Bird2(5.0f,6.33333333f,0.27f,&timer,QPixmap(":/image/yellow.png").scaled(height()/18.0,height()/18.0),world,scene);
           itemList.push_back(bird2);
           key2 =1;
        }
        //The second bird special function
        if(key2==2)
        {
            b2Vec2 b2 = bird2->g_body->GetLinearVelocity();
            b2.x = b2.x*1.5;
            b2.y = b2.y*1.5;
            bird2->setLinearVelocity(b2);
            key2=3;
        }

        // The third bird create
        if( key2 == 3 && key3 == 0 )
        {
           bird3 = new Bird3(5.0f,6.33333333f,0.27f,&timer,QPixmap(":/image/blue.png").scaled(height()/18.0,height()/18.0),world,scene);
           itemList.push_back(bird3);
           key3 =1;
        }
        //The third bird special function
        if(key3==2)
        {
            b2Vec2 v = bird3->g_body->GetLinearVelocity();
            b2Vec2 p = bird3->g_body->GetPosition();
            b2Vec2 v1,v2,v3;
            // Set velocity
            v1.x = v.x;
            v1.y = 0;
            v2.x = v.x;
            v2.y = v.y*2;
            v3.x = v.x;
            v3.y = -v.y;
            bird2->setLinearVelocity(v1);
            // Create  new birds
            bir = new Bird3(p.x,p.y,0.27f,&timer,QPixmap(":/image/blue.png").scaled(height()/18.0,height()/18.0),world,scene);
            itemList.push_back(bir);
            bir->setLinearVelocity(v2);
            bir->g_body->SetActive(true);
            bir2 = new Bird3(p.x,p.y,0.27f,&timer,QPixmap(":/image/blue.png").scaled(height()/18.0,height()/18.0),world,scene);
            itemList.push_back(bir2);
            bir2->setLinearVelocity(v3);
            bir2->g_body->SetActive(true);
            key3=3;
        }

        // The fourth bird create
        if( key3 == 3 && key4== 0 )
        {
           bird4 = new Bird4(5.0f,6.33333333f,0.27f,&timer,QPixmap(":/image/white.png").scaled(height()/14.0,height()/14.0),world,scene);
           itemList.push_back(bird4);
           key4 =1;
        }
        // The fourth bird special function
        if(key4==2)
        {
            b2Vec2 p = bird4->g_body->GetPosition();
            egg = new Egg(p.x+0.1,p.y-0.3,0.27f,&timer,QPixmap(":/image/egg.png").scaled(height()/22.0,height()/24.0),world,scene);
            itemList.push_back(egg);
            b2Vec2 v = bird4->g_body->GetLinearVelocity();
            v.x = v.x*0.8;
            v.y = v.y*0.8;
            bird4->setLinearVelocity(v);
            key4=3;
        }

    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
        QMouseEvent *e = static_cast <QMouseEvent*> ( event );
         if( key == 1 )
        {
             if(key1==0 && e->x() <=250 && e->x()>= 50 )
             {
                 b2Vec2 b2 = calculate(e->x(),e->y());
                 bird->g_body->SetTransform(b2,bird->g_body->GetAngle());
             }
             if( key1 == 1 && key2 ==1 && e->x() <=250 && e->x()>= 50 )
             {
                 b2Vec2 b2 = calculate(e->x(),e->y());
                 bird2->g_body->SetTransform(b2,bird2->g_body->GetAngle());
                 key3 = 4;
              }
             if( key2 == 3 && key3 ==1 && e->x() <=250 && e->x()>= 50 )
             {
                 b2Vec2 b2 = calculate(e->x(),e->y());
                 bird3->g_body->SetTransform(b2,bird3->g_body->GetAngle());
                 key4 = 4;
              }
             if( key3 == 3 && key4 ==1 && e->x() <=250 && e->x()>= 50 )
             {
                 b2Vec2 b2 = calculate(e->x(),e->y());
                 bird4->g_body->SetTransform(b2,bird4->g_body->GetAngle());
                 key1 = 3;
              }
         }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        std::cout << "Release !" << std::endl ;
        QMouseEvent *e = static_cast <QMouseEvent*> ( event );
        key = 0;
        if(key1==0)
        {
            b2Vec2 b2 = b2Vec2(5,6.333333333)-calculate(e->x(),e->y());
            b2.x = b2.x*6;
            b2.y = b2.y*6;
            bird->setLinearVelocity(b2);
            bird->g_body->SetActive(true);
            key1 = 1;
            return false;
        }
       if(key3==4)
       {
           b2Vec2 b2 = b2Vec2(5,6.333333333)-calculate(e->x(),e->y());
           b2.x = b2.x*6;
           b2.y = b2.y*6;
           bird2->setLinearVelocity(b2);
           bird2->g_body->SetActive(true);
           key2 = 2;
           key3 = 0;
       }
       if(key4==4)
       {
           b2Vec2 b2 = b2Vec2(5,6.333333333)-calculate(e->x(),e->y());
           b2.x = b2.x*6;
           b2.y = b2.y*6;
           bird3->setLinearVelocity(b2);
           bird3->g_body->SetActive(true);
           key3 = 2;
           key4 = 0;
       }
       if(key1==3)
       {
           b2Vec2 b2 = b2Vec2(5,6.333333333)-calculate(e->x(),e->y());
           b2.x = b2.x*6;
           b2.y = b2.y*6;
           bird4->setLinearVelocity(b2);
           bird4->g_body->SetActive(true);
           key4 = 2;
           key1 = 4;
       }


    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}



void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::check()
{
    if(score>=10000)
       delete egg;
    score = enimy->score + wood->score + wood2->score + wood3->score;
    QString str2 = QString("Score : "+QString::number(score)+" / 10000");
    label2->setText(str2);
    if(key4==3)
    {
        key4 =5;
        connect(&timer2,SIGNAL(timeout()),this,SLOT(time()));
        timer2.start(5000);
    }
    if(form->key==1)
    {
        form->key=0;
        key1=0;
        key2=0;
        key3=0;
        key4=0;
        score = 0;
        delete bird;
        delete bird2;
        delete bir;
        delete bir2;
        delete bird3;
        delete bird4;
        delete wood;
        delete wood2;
        delete wood3;
        delete egg;
        delete enimy;

        bird = new Bird(5,6.333333333f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/18.0,height()/18.0),world,scene);
        itemList.push_back(bird);
        wood = new Wood(20.0,4.f,0.6,3,8,&timer,QPixmap(":/image/thinwood1.png"),world,scene);
        itemList.push_back(wood);
        wood2 = new Wood(24.0,4.f,0.6,3,8,&timer,QPixmap(":/image/thinwood1.png"),world,scene);
        itemList.push_back(wood2);
        wood3 = new Wood(22.0f,5.8f,4.8,0.5f,1,&timer,QPixmap(":/image/thinwood.png"),world,scene);
        itemList.push_back(wood3);
        enimy = new Enimy(22,3.0f,0.27f,&timer,QPixmap(":/image/enimy.png").scaled(height()/17.0,height()/17.0),world,scene);
        itemList.push_back(enimy);

    }
    if(form->key==2)
    {
        form->key=0;
        QUITSLOT();
    }
}

void MainWindow::time()
{
    form->show();
    QLabel *label =  new QLabel(form);

    //設置字體大小
    QFont ft;
    ft.setPointSize(30);
    label->setFont(ft);

    //設置字體顏色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    label->setPalette(pa);
    QString str;
    if(score>=10000)
       str = QString("Excellent!");
    else if(score<10000)
       str = QString("Gameover!!!");
    label->setText(str);
    label->setGeometry(50,20,500,100);        //設定位置大小
    label->setAlignment(Qt::AlignLeft);
    scene->addWidget(label);
    label->show();
    timer2.stop();

}
