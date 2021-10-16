#include "widget.h"
#include "ui_widget.h"

#define COLOR_SUCCESS "color:green;"
#define COLOR_ERROR "color:red;"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    calculateAll();
}

Widget::~Widget()
{
    delete ui;
}

//Добавить новую точку
void Widget::addPoint(){
    QListWidgetItem* item = new QListWidgetItem;
    Point* point = new Point;
    item->setText(POINT_NAME + QString::number(ui->pointList->count()+1));
    points.insert({item, point});
    ui->pointList->addItem(item);
}

//Расчёт модуля для вещественного числа
double Widget::dabs(double x){
    if(x >= 0) return x;
    return -1 * x;
}

std::vector<Point> Widget::getVectorPoints(){
    std::vector<Point> v_points;
    for(int i = 0; i < ui->pointList->count(); i++){
        v_points.push_back(*points.at(ui->pointList->item(i)));
    }
    return v_points;
}

//Функция произведения векторов
double Widget::vectorMultiple(double x1, double y1, double x2, double y2){
    return x1 * y2 - x2 * y1;
}

//Функция проверки пересечения 2-ух отрезков
bool Widget::checkCross(Point p1, Point p2, Point p3, Point p4){
    double v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    v1 = vectorMultiple(p4.x-p3.x, p4.y-p3.y , p1.x-p3.x, p1.y-p3.y);
    v2 = vectorMultiple(p4.x-p3.x, p4.y-p3.y , p2.x-p3.x, p2.y-p3.y);
    v3 = vectorMultiple(p2.x-p1.x , p2.y-p1.y , p3.x-p1.x , p3.y-p1.y);
    v4 = vectorMultiple(p2.x-p1.x , p2.y-p1.y , p4.x-p1.x , p4.y-p1.y);
    if ((v1 * v2 < 0) && (v3 * v4 < 0)) return true;
    return false;
}

//Функция проверки на наличие в многоульнике пересекающихся сторон
bool Widget::hasCross(std::vector<Point> v_points){
    if(points.size() < 4) return false; //Если в многоульнике меньше 4-ёх вершин, то он не может самопересекаться, поэтому досрочный выход
    bool crossed = false;

    unsigned int counter = 1;
    auto it = v_points.begin();
    auto endIt = --v_points.end();

    //Цикл проверки для стороны начальной и конечной вершин
    while(counter < v_points.size()-1){
        if(checkCross(*(v_points.begin()+counter), *(v_points.begin()+1+counter), *it, *endIt)) crossed = true;
        //qDebug("Checked");
        counter++;
    }

    //Цикл проверки для всех остальных сторон многоульника
    it = v_points.begin()+3;
    while(it != v_points.end()){
        counter = 0;
        while(counter < v_points.size()-3){
            if(checkCross(*(v_points.begin()+counter), *(v_points.begin()+1+counter), *(it-1), *it)) crossed = true;
            //qDebug("Checked");
            counter++;
        }
        ++it;
    }
    return crossed;
}

void Widget::calculateAll(){
    if(points.size() < 1) return;
    calculatePolygonSides();
    bool crossed = false;
    double s = calculatePolygonSquare(&crossed);
    double p = calculatePerimeter();
    ui->squareEdit->setText(crossed ? "Самопересекающийся многоугольник" : (s == 0 ? "Вырожденный многоугольник" : QString::number(s, 'f', 2)));
    ui->perimeterEdit->setText(QString::number(p, 'f', 2));
}

//Расчёт периметра многоульника
double Widget::calculatePerimeter(){
    double p = 0;
    for(auto it = points.begin(); it != points.end(); ++it){
        p += it->second->side;
    }
    return p;
}

//Рассчитывает стороны соединения всех вершин многоугольника
void Widget::calculatePolygonSides(){
    if(points.size() <= 1) return;
    auto it = points.begin();
    auto end = --points.end();
    end->second->side = sqrt(pow(it->second->x-end->second->x, 2) + pow(it->second->y-end->second->y, 2));
    while(it != end){
        auto p1 = it->second;
        auto p2 = (++it)->second;
        p1->side = sqrt(pow(p2->x-p1->x, 2) + pow(p2->y-p1->y, 2));
    }
}

//Расчёт площади многоульника
double Widget::calculatePolygonSquare(bool* crossed = nullptr){
    if(points.size() <= 1) return 0;
    *crossed = hasCross(getVectorPoints());
    //qDebug(*crossed ? "Has cross" : "Has no cross");
    double part1 = 0, part2 = 0;
    auto it = points.begin();
    auto end = --points.end();
    part1 += end->second->x * it->second->y;
    part2 += end->second->y * it->second->x;
    while(it != end){
        int x1 = it->second->x, y1 = it->second->y;
        ++it;
        part1+=x1*it->second->y;
        part2+=y1*it->second->x;
    }
    return dabs((part1-part2)/2);
}


void Widget::on_addPointButton_clicked()
{
    addPoint();
    calculateAll();
}


void Widget::on_removePointButton_clicked()
{
    if(ui->pointList->count() < 1) return;
    QListWidgetItem* item = ui->pointList->item(ui->pointList->count()-1);
    points.erase(item);
    delete item;
    calculateAll();
}


void Widget::on_pointList_itemClicked(QListWidgetItem *item)
{
    ui->xEdit->setText(QString::number(points.at(item)->x));
    ui->yEdit->setText(QString::number(points.at(item)->y));
    ui->sideEdit->setText(QString::number(points.at(item)->side, 'f', 2));
}


void Widget::on_xEdit_textChanged(const QString &arg1)
{
    if(ui->pointList->selectedItems().count() < 1) return ui->xEdit->clear();
    bool ok = true;
    int x = arg1.toInt(&ok);
    points.at(ui->pointList->selectedItems()[0])->x = ok ? x : 0;
    calculateAll();
}


void Widget::on_yEdit_textChanged(const QString &arg1)
{
    if(ui->pointList->selectedItems().count() < 1) return ui->yEdit->clear();
    bool ok = true;
    int x = arg1.toInt(&ok);
    points.at(ui->pointList->selectedItems()[0])->y = ok ? x : 0;
    calculateAll();
}

