#ifndef XYCLOSEANIMATIONWIDGET_H
#define XYCLOSEANIMATIONWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class XYCloseAnimationWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int pixLen READ pixLen WRITE setPixLen)
    Q_PROPERTY(int pixPosX READ pixPosX WRITE setPixPosX)
    Q_PROPERTY(int lineLen READ lineLen WRITE setLineLen)
public:
    explicit XYCloseAnimationWidget(QWidget *parent = 0);

public:
    int pixLen() const;
    void setPixLen(int len);

    int pixPosX() const;
    void setPixPosX(int x);

    int lineLen() const;
    void setLineLen(int len);

public slots:
    void setBackgroundPix(const QPixmap &pix);
    void startAnimation();

protected:
    void paintEvent(QPaintEvent *event);

protected:
    bool isAnimationRunning();

private:
    int   pixleftLen;                      // 图片剩余区域（动画需要的变量，不要动）
    int   pixCurPosX = 0;                  // 图片当前（动画需要的变量，不要动）
    int   lineLeftLen = 0;                 // 线长（动画需要的变量，不要动）

private:
    QPropertyAnimation *pixAnimation;      // 图片动画
    QPropertyAnimation *pixPosXAnimation;  // 图片移动动画
    QPropertyAnimation *lineRiseAnimation; // 直线增长动画
    QPropertyAnimation *linedeAnimation;   // 直线缩短动画
    QPixmap             backgroundPix;     // 图片

    int                 interval = 30;     // 窗口和线的间隔

    QSequentialAnimationGroup *animationGroup; // 动画集成

};

#endif // XYCLOSEANIMATIONWIDGET_H
