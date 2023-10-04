#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>

// #include <functional>
// using Polinomial_funcs_delegate = std::function<double(double)>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->removeGraph(0);
    ui->widget->replot();

    QVector<int> * X = new QVector<int>();
    QVector<int> * Y = new QVector<int>();

    read_input(X, Y);

    ui->textBrowser->clear();
    int size = 0;
    if (X->size() != Y->size()) {
        ui->textBrowser->append("Функцію погано введено:\nx: "+
            QString::number(X->size())+", y: "+QString::number(Y->size()));
    }
    else {
        size = X->size();
        double * x_values = new double[size];
        double * y_values = new double[size];

        for (int i = 0; i < size; ++i) {
            x_values[i] = (*X)[i];
            y_values[i] = (*Y)[i];
        }

        func_delegate L = My_algorithms::final_func_builder(size, x_values, y_values);
        draw_plot(L);

        delete X;
        delete Y;
        delete[] x_values;
        delete[] y_values;
    }
}

void MainWindow::on_pushButton_func_clicked()
{
    ui->widget->removeGraph(0);
    ui->widget->replot();
    read_input(nullptr, nullptr);

    QString n_str = ui->lineEdit_n->text();
    bool is_n;
    int n = n_str.toInt(&is_n);
    if (!is_n)
        ui->textBrowser->append("n погано введено");

    double H = (b - a) / n;

    func_delegate F = My_algorithms::custom_function_builder();

    double * x_values = new double[n];
    double * y_values = new double[n];

    double v = a;
    for (int i = 0; i < n; v += H, ++i) {
        x_values[i] = v;
        y_values[i] = F(v);
    }

    ui->lineEdit_x->clear();
    ui->lineEdit_y->clear();

    func_delegate L = My_algorithms::final_func_builder(n, x_values, y_values);
    draw_plot(L);

    // draw_plot(My_algorithms::custom_function_builder());
}

void MainWindow::read_input(QVector<int> * X, QVector<int> * Y) {
    QString text_x = ui->lineEdit_x->text();
    QString text_y = ui->lineEdit_y->text();
    QString text_a = ui->lineEdit_a->text();
    QString text_b = ui->lineEdit_b->text();
    bool secc_a, secc_b;
    int input_a = text_a.toInt(&secc_a);
    int input_b = text_b.toInt(&secc_b);
    if (secc_a && secc_b && a < b) {
        a = input_a;
        b = input_b;
    } else if (secc_a && !secc_b)
        a = input_a;
    else if (secc_b && !secc_a)
        b = input_b;

    if (X != nullptr && Y != nullptr) {
        parce_input(text_x, X);
        parce_input(text_y, Y);
    }
}

void MainWindow::parce_input(QString text, QVector<int> * numbers) {
    numbers->clear();
    QTextStream stream(&text);
    while (!stream.atEnd()) {
        int number;
        stream >> number;
        numbers->append(number);
    }
}

void MainWindow::draw_plot(func_delegate F) {
    ui->widget->removeGraph(0);
    //ui->widget->clearGraphs();
    //ui->widget->graph(0)->brush();
    ui->widget->replot();

    h = 0.1;
    xBegin = a;
    xEnd = b + h;

    ui->widget->xAxis->setRange(a-1,b+1);
    ui->widget->yAxis->setRange(-9,9);

    X = xBegin;
    N = (xEnd - xBegin)/h + 2;

    for (X = xBegin; X < xEnd; X += h) {
        x.push_back(X);
        y.push_back(F(X));
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}





// connect(pushButton, &QPushButton::released, this, )
// connect(pushButton, QPushButton::clicked(), this, [&textBrowser]() {
//    textBrowser.append("hello bro!");
// });
