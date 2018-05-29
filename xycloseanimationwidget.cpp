#include "xycloseanimationwidget.h"
#include <QPainter>
#include <QTimer>

XYCloseAnimationWidget::XYCloseAnimationWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);

    pixAnimation = new QPropertyAnimation(this, "pixLen");
    pixAnimation->setLoopCount(1);
    pixAnimation->setDuration(350);

    pixPosXAnimation = new QPropertyAnimation(this, "pixPosX");
    pixPosXAnimation->setLoopCount(1);
    pixPosXAnimation->setDuration(80);

    lineRiseAnimation = new QPropertyAnimation(this, "lineLen");
    lineRiseAnimation->setLoopCount(1);
    lineRiseAnimation->setDuration(200);

    linedeAnimation = new QPropertyAnimation(this, "lineLen");
    linedeAnimation->setLoopCount(1);
    linedeAnimation->setDuration(200);

    animationGroup = new QSequentialAnimationGroup(this);
    animationGroup->addAnimation(lineRiseAnimation);
    animationGroup->addAnimation(pixPosXAnimation);
    animationGroup->addAnimation(pixAnimation);
    animationGroup->addAnimation(linedeAnimation);
    connect(animationGroup, SIGNAL(finished()), this, SLOT(close()));
}

int XYCloseAnimationWidget::pixLen() const
{
    return pixleftLen;
}

void XYCloseAnimationWidget::setPixLen(int len)
{
    pixleftLen = len;
    update();
}

int XYCloseAnimationWidget::pixPosX() const
{
    return pixCurPosX;
}

void XYCloseAnimationWidget::setPixPosX(int x)
{
    pixCurPosX = x;
    update();
}

int XYCloseAnimationWidget::lineLen() const
{
    return lineLeftLen;
}

void XYCloseAnimationWidget::setLineLen(int len)
{
    lineLeftLen = len;
    update();
}

void XYCloseAnimationWidget::setBackgroundPix(const QPixmap &pix)
{
    backgroundPix = pix;
    pixleftLen = backgroundPix.width();
    resize(backgroundPix.size() + QSize(interval + 2, 0));
}

void XYCloseAnimationWidget::startAnimation()
{
    pixAnimation->setEndValue(0);
    pixPosXAnimation->setEndValue(interval);
    lineRiseAnimation->setEndValue(height());
    linedeAnimation->setEndValue(0);
    animationGroup->start();
}

void XYCloseAnimationWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawPixmap(QRect(pixCurPosX + backgroundPix.width() - pixleftLen, 0,
                             pixleftLen, backgroundPix.height()),
                       backgroundPix,
                       QRect(0, 0,
                             pixleftLen, backgroundPix.height()));

    if (lineLeftLen > 0)
    {
        painter.setPen(QColor("#9DDAE9"));
        painter.drawLine(width() - 2, (height() - lineLeftLen) / 2,
                         width() - 2, (height() + lineLeftLen) / 2);
    }

}

bool XYCloseAnimationWidget::isAnimationRunning()
{
    return animationGroup->state() == QAbstractAnimation::Running;
}
