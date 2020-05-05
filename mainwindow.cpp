#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QColor>
#include<QMouseEvent>
#include<QPoint>
#include<QImage>
#include "complex.h"
#include <bits/stdc++.h>

//settings
const int iterations = 350;
const QColor borderColor = Qt::white;
const bool colorReverse = false;
//settings

const double eps = 1e-8;
const int displaysize = 500;
QColor colors[iterations + 1];
QPoint pointBegin, pointEnd, pointTmp;

double xstart = -2.0;
double ystart = -2.0;
double step = 2.0 / double(displaysize);
bool isPressed = false;
QImage * image;
int imagecopy[2 * (displaysize + 1)][2 * (displaysize + 1)];
bool isLine = false;



MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);
    this -> setMinimumSize(2 * displaysize + 1, 2 * displaysize + 1);
    this -> setMaximumSize(2 * displaysize + 1, 2 * displaysize + 1);
    for (int i = 30, j = 0; j <= iterations; i += 3, ++j) {
            colors[j] = (i <= 360) ? QColor::fromHsl(i, 210, 127).name() : colors[j - 1];
        }
        if (colorReverse) {
            std::reverse(colors, colors + 109);
        }
    image = new QImage(2 * displaysize + 1, 2 * displaysize + 1, QImage::Format_RGB32);
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == 16777220){
        xstart = -2;
        ystart = -2;
        step = 2.0 / double(displaysize);
        repaint();
    }

}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::pointCheck(complex & c) {
    complex z = complex(0, 0);
    int i = 0;
    for (i = 0; i < iterations; ++i) {
        z = z * z + c;
        if (z.v() > 2.0 + eps) {
            break;
        }
    }
    return i;
}

void MainWindow::mousePressEvent(QMouseEvent * event) {
    isPressed = true;
    pointEnd = pointBegin = event -> pos();
}


void MainWindow::mouseMoveEvent(QMouseEvent * event) {
    if (!isPressed) {
        return;
    }
    pointTmp = event -> pos();
    if (pointTmp.x() < 0 || pointTmp.y() < 0 || pointTmp.x() > 2 * displaysize || pointTmp.y() > 2 * displaysize) {
        return;
    }
    pointTmp = pointEnd;
    pointEnd = event -> pos();
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event) {
    isPressed = false;

    if (!(pointTmp.x() < 0 || pointTmp.y() < 0 || pointTmp.x() > 2 * displaysize || pointTmp.y() > 2 * displaysize)) {
        pointEnd = event -> pos();
    }

    int dx = pointEnd.x() - pointBegin.x(), dy = abs(pointEnd.y() - pointBegin.y());
    if (dx == 0 || dy == 0) {
        repaint();
        return;
    }
    if (dx > 0) {
        if (dy != 0) {
            xstart = double(qMin(pointEnd.x(), pointBegin.x())) * step + xstart;
            ystart = double(2.0 * displaysize - qMax(pointEnd.y(), pointBegin.y())) * step + ystart;
            step = double(qMax(dx, dy)) / (2.0 * double(displaysize)) * step;
            repaint();
        }
    } else if (dx < 0) {
        if (dy != 0) {
            step = (2.0 * double(displaysize)) / double(qMax(dx, dy)) * step;
            xstart -= double(qMin(pointEnd.x(), pointBegin.x())) * step;
            ystart -= double(2.0 * displaysize - qMax(pointEnd.y(), pointBegin.y())) * step;
            repaint();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent * event) {
    QPainter painter(this);
    painter.translate(displaysize, displaysize);
    painter.scale(1, -1);
    if (isPressed) {
        int px1 = qMin(pointBegin.x(), pointTmp.x()) - displaysize;
        int px2 = qMax(pointBegin.x(), pointTmp.x()) - displaysize;
        int py1 = displaysize - qMax(pointBegin.y(), pointTmp.y());
        int py2 = displaysize - qMin(pointBegin.y(), pointTmp.y());

        for (int i = px1; i <= px2; ++i) {
            image -> setPixelColor(i + displaysize, displaysize + py1, colors[imagecopy[i + displaysize][displaysize - py1]].toRgb());
            image -> setPixelColor(i + displaysize, displaysize + py2, colors[imagecopy[i + displaysize][displaysize - py2]].toRgb());
        }
        for (int i = py1; i <= py2; ++i) {
            image -> setPixelColor(px1 + displaysize, displaysize + i, colors[imagecopy[px1 + displaysize][-i + displaysize]].toRgb());
            image -> setPixelColor(px2 + displaysize, displaysize + i, colors[imagecopy[px2 + displaysize][-i + displaysize]].toRgb());
        }
        px1 = qMin(pointBegin.x(), pointEnd.x()) - displaysize;
        px2 = qMax(pointBegin.x(), pointEnd.x()) - displaysize;
        py1 = displaysize - qMax(pointBegin.y(), pointEnd.y());
        py2 = displaysize - qMin(pointBegin.y(), pointEnd.y());

        for (int i = px1; i <= px2; ++i) {
            image -> setPixelColor(i + displaysize, displaysize + py1, borderColor);
            image -> setPixelColor(i + displaysize, displaysize + py2, borderColor);
        }
        for (int i = py1; i <= py2; ++i) {
            image -> setPixelColor(px1 + displaysize, displaysize + i, borderColor);
            image -> setPixelColor(px2 + displaysize, displaysize + i, borderColor);
        }
        painter.drawImage(QPoint(-displaysize, -displaysize), * image);
        return;
    }

    for (int i = -displaysize; i <= displaysize; ++i) {
        for (int j = -displaysize; j <= displaysize; ++j) {
            complex point = complex((i + displaysize) * step + xstart, (displaysize - j) * step + ystart);
            int q = pointCheck(point);
            imagecopy[i + displaysize][j + displaysize] = q;
            image -> setPixelColor(i + displaysize, displaysize - j, colors[q].toRgb());
        }
    }
    painter.drawImage(QPoint(-displaysize, -displaysize), * image);
    return;
}
