#ifndef XYQQLOGINWIDGET_H
#define XYQQLOGINWIDGET_H

#include "xycloseanimationwidget.h"

class XYQQLogInWidget : public XYCloseAnimationWidget
{
    Q_OBJECT
public:
    explicit XYQQLogInWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

protected:
    // 画用户名输入
    void paintUserEdit(QPainter &painter, const QRect &rect);

    // 画密码输入
    void paintPassWordEdit(QPainter &painter, const QRect &rect);

    // 画选择框
    void paintBoxEdit(QPainter &painter, const QRect &rect);

    // 画文本框
    void paintTextBox(QPainter &painter, const QRect &rect);

    // 画图片框
    void paintPixBox(QPainter &painter, const QRect &rect);

    // 画登录按钮
    void paintLoginBtn(QPainter &painter, const QRect &rect);

protected:
    bool   mbLeftMousePressed = false;  // 记录鼠标左键是否按下
    QPoint moLastPos;                   // 记录上次鼠标按下移动的位置

    QRect  coverTextRect;               // 当前悬浮的文本框

private:
    QRect  QQLog;             // QQlog图片
    QRect  userPix;           // 用户图片
    QRect  user;              // 用户名输入框
    QRect  password;          // 密码输入框

    QRect  autoLogin;         // 自动登录
    QRect  rememberPassword;  // 记住密码
    QRect  retrievePassword;  // 找回密码

    QRect  loginBtn;          // 登录按钮

    QRect  registerUser;      // 注册区域
    QRect  QRCode;            // 二维码

    QRect  settingBtn;        // 设置按钮
    QRect  minBtn;            // 最小化按钮
    QRect  closeBtn;          // 关闭按钮

};

#endif // XYQQLOGINWIDGET_H
