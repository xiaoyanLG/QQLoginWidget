#include "xyqqloginwidget.h"
#include <QPainter>
#include <QMouseEvent>

XYQQLogInWidget::XYQQLogInWidget(QWidget *parent)
    : XYCloseAnimationWidget(parent)
{
    setMouseTracking(true);
}

void XYQQLogInWidget::paintEvent(QPaintEvent *event)
{
    if (!XYCloseAnimationWidget::isAnimationRunning())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing
                               | QPainter::TextAntialiasing
                               | QPainter::SmoothPixmapTransform);
        // 先画上面矩形区域
        painter.drawPixmap(QRect(0, 0, width(), height() * 0.4), QPixmap(":/top.png"));

        // 再画下面的矩形区域
        painter.drawPixmap(QRect(0, height() * 0.4, width(), height() - height() * 0.4),
                           QPixmap(":/bottom.png"));

        // 画QQ Log
        QQLog = QRect(5, 5, width() * 0.25, height() * 0.2);
        paintPixBox(painter, QQLog);

        // 画菜单按钮
        int btnWidth  = 25;
        int btnHeight = 25;
        closeBtn = QRect(width() - btnWidth, 0, btnWidth, btnHeight);
        paintPixBox(painter, closeBtn);

        minBtn = QRect(width() - 2 * btnWidth, 0, btnWidth, btnHeight);
        paintPixBox(painter, minBtn);

        settingBtn = QRect(width() - 3 * btnWidth, 0, btnWidth, btnHeight);
        paintPixBox(painter, settingBtn);

        // 画用户图片
        int radius = 90;
        userPix = QRect(width() / 2 - radius / 2, height() * 0.4 - radius / 2, radius, radius);
        QBrush brush(QPixmap(":/user.jpg").scaled(QSize(radius, radius)));
        painter.setBrush(brush);
        painter.drawEllipse(userPix.x(), userPix.y(), radius, radius);

        // 画用户名输入框， 密码输入框
        int userWidth = width() * 0.6;
        int userHeight = 30;
        user = QRect(width() * 0.2, userPix.bottom() + 12, userWidth, userHeight);
        paintUserEdit(painter, user);

        password = QRect(width() * 0.2, user.bottom() + 5, userWidth, userHeight);
        paintPassWordEdit(painter, password);

        // 画自动登录, 记住密码, 找回密码
        int autoLoginWidth = userWidth / 3 - 5;
        int autoLoginheight = 20;
        autoLogin = QRect(width() * 0.2, password.bottom() + 5, autoLoginWidth, autoLoginheight);
        paintBoxEdit(painter, autoLogin);

        rememberPassword = QRect(autoLogin.right() + 8, autoLogin.y(), autoLoginWidth, autoLoginheight);
        paintBoxEdit(painter, rememberPassword);

        retrievePassword = QRect(rememberPassword.right() + 8, autoLogin.y(), autoLoginWidth, autoLoginheight);
        paintTextBox(painter, retrievePassword);

        // 画登录按钮
        loginBtn = QRect(width() * 0.2, retrievePassword.bottom() + 8, userWidth, userHeight + 10);
        paintLoginBtn(painter, loginBtn);

        // 画注册账号， 二维码
        registerUser = QRect(15, height() - 25, 50, autoLoginheight);
        paintTextBox(painter, registerUser);

        QRCode = QRect(width() - 40, height() - 35, 30, 30);
        paintPixBox(painter, QRCode);

    }
    else
    {
        XYCloseAnimationWidget::paintEvent(event);
    }
}

void XYQQLogInWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mbLeftMousePressed = true;
        moLastPos = event->globalPos();
    }
}

void XYQQLogInWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mbLeftMousePressed = false;
        moLastPos = event->globalPos();

        if (closeBtn.contains(event->pos()))
        {
            setBackgroundPix(grab());
            startAnimation();
        }
        else if (minBtn.contains(event->pos()))
        {
            showMinimized();
        }
        else if (registerUser.contains(event->pos())
                 || QRCode.contains(event->pos()))
        {
            setCursor(Qt::PointingHandCursor);
        }
    }
}

void XYQQLogInWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mbLeftMousePressed)
    {
        QPoint lastpos(x(), y());
        lastpos.setX( lastpos.x() + event->globalX() - moLastPos.x());
        lastpos.setY( lastpos.y() + event->globalY() - moLastPos.y());
        move(lastpos);
        moLastPos = event->globalPos();
    }

    setCursor(Qt::ArrowCursor);
    if (closeBtn.contains(event->pos())
            || minBtn.contains(event->pos())
            || settingBtn.contains(event->pos())
            || QRCode.contains(event->pos())
            || loginBtn.contains(event->pos()))
    {
        setCursor(Qt::PointingHandCursor);
    }
    else if (retrievePassword.contains(event->pos()))
    {
        setCursor(Qt::PointingHandCursor);
        if (coverTextRect != retrievePassword)
        {
            coverTextRect = retrievePassword;
            update(coverTextRect);
        }
    }
    else if (registerUser.contains(event->pos()))
    {
        setCursor(Qt::PointingHandCursor);
        if (coverTextRect != registerUser)
        {
            coverTextRect = registerUser;
            update(coverTextRect);
        }
    }
    else
    {
        update(coverTextRect);
        coverTextRect = QRect();
    }
}

void XYQQLogInWidget::paintUserEdit(QPainter &painter, const QRect &rect)
{
    painter.save();
    painter.drawRect(rect);
    painter.restore();
}

void XYQQLogInWidget::paintPassWordEdit(QPainter &painter, const QRect &rect)
{
    painter.save();
    painter.drawRect(rect);
    painter.restore();
}

void XYQQLogInWidget::paintBoxEdit(QPainter &painter, const QRect &rect)
{
    painter.save();
    painter.drawRect(rect);
    painter.restore();
}

void XYQQLogInWidget::paintTextBox(QPainter &painter, const QRect &rect)
{
    painter.save();

    // 设置画笔
    if (rect == coverTextRect)
    {
        painter.setPen(QColor("blue"));
    }

    QString text;
    if (rect == retrievePassword)
    {
        text = QStringLiteral("找回密码");
    }
    else if (rect == registerUser)
    {
        text = QStringLiteral("注册账号");
    }
    else
    {
        painter.drawRect(rect);
    }

    painter.drawText(rect, text, QTextOption(Qt::AlignCenter));

    painter.restore();
}

void XYQQLogInWidget::paintPixBox(QPainter &painter, const QRect &rect)
{
    painter.save();

    if (rect == QQLog)
    {
        painter.drawPixmap(rect, QPixmap(":/QQ.png"));
    }
    else if (rect == QRCode)
    {
        painter.drawPixmap(rect, QPixmap(":/icos/qr_code.ico"));
    }
    else if (rect == closeBtn)
    {
        painter.drawPixmap(rect, QPixmap(":/icos/ic_close_white.png"));
    }
    else if (rect == minBtn)
    {
        painter.drawPixmap(rect, QPixmap(":/icos/ic_min_white.png"));
    }
    else if (rect == settingBtn)
    {
        painter.drawPixmap(rect, QPixmap(":/icos/ic_login_cfg.png"));
    }

    painter.restore();
}

void XYQQLogInWidget::paintLoginBtn(QPainter &painter, const QRect &rect)
{
    // 保存之前的配置
    painter.save();

    painter.setBrush(QColor("#04B9FB"));
    painter.setPen(QColor("#D3EFFF"));
    painter.drawRoundedRect(rect, 5, 5);
    painter.drawText(rect, QStringLiteral("登录"), QTextOption(Qt::AlignCenter));

    // 还原之前的配置
    painter.restore();
}
