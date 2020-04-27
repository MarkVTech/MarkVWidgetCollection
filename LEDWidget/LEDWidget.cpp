#include <cmath>

#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QSizePolicy>
#include <QDebug>

#include "LEDWidget.h"

LEDWidget::LEDWidget(QWidget *parent) :
    QWidget(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(toggleState()));

    setDiameterMM(m_diameterMM);

    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    updateGeometry();
}

double LEDWidget::diameter() const
{
    return m_pixX * m_diameterMM;
}

void LEDWidget::
setDiameterMM(double diameter)
{
    m_diameterMM = diameter;

    m_pixX = round(double(height())/heightMM());
    m_pixY = round(double(width())/widthMM());

    m_diamXInPixels = m_diameterMM*m_pixX;
    m_diamYInPixels = m_diameterMM*m_pixY;

    m_center = QPoint(m_diamXInPixels/2.0, m_diamYInPixels/2.0);
    m_radius = m_diamXInPixels/2.0;

    updateGeometry();
    update();
}


QColor LEDWidget::
color() const
{
    return m_color;
}

void LEDWidget::
setColor(const QColor& color)
{
    m_color = color;
    update();
}

Qt::Alignment LEDWidget::
alignment() const
{
    return m_alignment;
}

void LEDWidget::
setAlignment(Qt::Alignment alignment)
{
    if ( m_alignment == alignment )
        return;

    m_alignment = alignment;
    updateGeometry();

    update();
}

void LEDWidget::
setFlashRate(int rate)
{
    m_flashRate = rate;

    update();
}

void LEDWidget::
setFlashing(bool flashing)
{
    m_flashing = flashing;

    update();
}

void LEDWidget::
startFlashing()
{
    setFlashing(true);
}

void LEDWidget::
stopFlashing()
{
    setFlashing(false);
}

void LEDWidget::setMargin(int margin)
{
    if ( margin == m_margin )
        return;

    m_margin = margin;
    update();
}

bool LEDWidget::
state() const
{
    return m_state;
}

bool LEDWidget::
isFlashing() const
{
    return m_flashing;
}

int LEDWidget::
flashRate() const
{
    return m_flashRate;
}

int LEDWidget::margin() const
{
    return m_margin;
}

void LEDWidget::
setState(bool state)
{
    if ( state == m_state )
        return;

    m_state = state;

    update();
}

void LEDWidget::
toggleState()
{
    m_state = !m_state;

    update();
}

QSize LEDWidget::sizeHint() const
{
    return QSize(m_diamXInPixels+2, m_diamYInPixels+2);
}

QSize LEDWidget::minimumSizeHint() const
{
    return QSize(m_diamXInPixels+2, m_diamYInPixels+2);
}

int LEDWidget::heightForWidth(int width) const
{
    Q_UNUSED(width)

    return m_diamYInPixels+2;
}

void LEDWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);

    //QRectF rect = contentsRect();
    QRectF rect = event->rect();
    //rect.adjust(m_margin, m_margin, m_margin, m_margin);
    QPointF center = rect.center();
    double width = rect.width()-1;
    double height = rect.height()-1;

    double x=1.0, y=1.0;

    if ( m_alignment & Qt::AlignLeft )
        x = 1.0;
    else if ( m_alignment & Qt::AlignRight )
        x = width-m_diamXInPixels+1;
    else if ( m_alignment & Qt::AlignHCenter )
        x = (width-m_diamXInPixels)/2+1;
    else if ( m_alignment & Qt::AlignCenter )
        x = (width-m_diamXInPixels)/2+1;
    else if ( m_alignment & Qt::AlignJustify )
        x = 1.0;

    if ( m_alignment & Qt::AlignTop )
        y = 1.0;
    else if ( m_alignment & Qt::AlignBottom )
        y = height-m_diamYInPixels+1;
    else if ( m_alignment & Qt::AlignVCenter )
        y = (height-m_diamYInPixels)/2+1;
    else if ( m_alignment & Qt::AlignCenter )
        y = (height-m_diamYInPixels)/2+1;

    //qDebug() << "(x, y) = (" << x << ", " << y << ")";

    double radius = m_diamXInPixels; // /2+m_bevelSize;
    //
    // Draw bevel
    //
    //QRadialGradient bevelGradient(center, radius);
    QRadialGradient bevelGradient(QPointF(center.x()-x/2, center.y()-y/2), radius);
    bevelGradient.setColorAt(0.0, QColor("white"));
    bevelGradient.setColorAt(0.77, QColor("silver"));
    bevelGradient.setColorAt(1.0, QColor("white"));

    QRectF ellipseRect(x, y, m_diamXInPixels, m_diamYInPixels);

    QRadialGradient g(x+m_diamXInPixels/2, y+m_diamYInPixels/2, m_radius+1);

    g.setColorAt(0, Qt::white);
    if ( m_state )
    {
        QPen pen(m_color);
        //pen.setWidthF(0.0);
        pen.setCosmetic(true);
        g.setColorAt(1, m_color);
        p.setPen(pen);
        //p.setPen(m_color);
    }
    else
    {
        QPen pen("black");
        //pen.setWidthF(0.0);
        pen.setCosmetic(true);
        g.setColorAt(1, Qt::black);
        p.setPen(pen);
    }
    QBrush gradientBrush(g);

    //p.setPen(m_color);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(gradientBrush);

    p.drawEllipse(x, y, m_diamXInPixels, m_diamYInPixels);

    if ( m_flashRate > 0 && m_flashing )
        m_timer->start(m_flashRate);
    else
        m_timer->stop();
}

bool LEDWidget::hasHeightForWidth() const
{
    return true;
}
