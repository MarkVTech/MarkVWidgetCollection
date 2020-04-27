#include <QtMath>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>
#include <QBrush>
#include <QRadialGradient>
#include <QVariantAnimation>
#include <QDebug>

#include "NeedleGauge.h"

NeedleGauge::NeedleGauge(QWidget *parent) :
    QWidget(parent),
    mDialAnimation(new QVariantAnimation(this))
{
    setDiameterMM(mDiameterMM);
    //calculateFontSize();
    mMajorTickLength = mDiamXInPixels*(mMajorTickLengthAsPercent/100.0);
    mMinorTickLength = mDiamXInPixels*(mMinorTickLengthAsPercent/100.0);

    connect(mDialAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(handleDialAnimationValueChanged(QVariant)));

    mFont = font();
    update();
}

double NeedleGauge::value() const
{
    return mValue;
}

double NeedleGauge::diameterMM() const
{
    return mDiameterMM;
}

QColor NeedleGauge::faceColor() const
{
    return mFaceColor;
}

int NeedleGauge::marginSizeAsPercent() const
{
    return mMarginSizeAsPercent;
}

QColor NeedleGauge::needleColor() const
{
    return mNeedleColor;
}

QFont NeedleGauge::font() const
{
    return mFont;
}

QColor NeedleGauge::fontColor() const
{
    return mFontColor;
}

double NeedleGauge::minValue() const
{
    return mMinValue;
}

double NeedleGauge::maxValue() const
{
    return mMaxValue;
}

int NeedleGauge::majorTickInterval() const
{
    return mMajorTickInterval;
}

int NeedleGauge::numberOfTicks() const
{
    return mNumberOfTicks;
}

int NeedleGauge::majorTickLengthAsPercent() const
{
    return mMajorTickLengthAsPercent;
}

int NeedleGauge::minorTickLengthAsPercent() const
{
    return mMinorTickLengthAsPercent;
}

QColor NeedleGauge::tickColor() const
{
    return mTickColor;
}


void NeedleGauge::
setDiameterMM(double diameter)
{
    mDiameterMM = diameter;

    mPixX = round(double(height())/heightMM());
    mPixY = round(double(width())/widthMM());


    mDiamXInPixels = mDiameterMM*mPixX;
    mDiamYInPixels = mDiameterMM*mPixY;

    mCenter = QPoint(mDiamXInPixels/2.0, mDiamYInPixels/2.0);
    mRadius = mDiamXInPixels/2.0;

    //calculateFontSize();

    updateGeometry();
    update();
}

void NeedleGauge::setFaceColor(const QColor &color)
{
    mFaceColor = color;

    update();
}

void NeedleGauge::setMarginSizeAsPercent(int percent)
{
    if ( percent < 0.0 || percent > 10.0 )
        return;

    mMarginSizeAsPercent = percent;

    //calculateFontSize();

    update();
}

void NeedleGauge::setNeedleColor(const QColor &color)
{
    if ( mNeedleColor == color )
        return;

    mNeedleColor = color;

    update();
}

void NeedleGauge::setFont(const QFont &font)
{
    if ( mFont == font )
        return;

    mFont = font;

    update();
}

void NeedleGauge::setFontColor(const QColor &color)
{
    if ( mFontColor == color )
        return;

    mFontColor = color;

    update();
}

void NeedleGauge::setMinValue(double value)
{
    mMinValue = value;

    update();
}

void NeedleGauge::setMaxValue(double value)
{
    mMaxValue = value;

    update();
}

void NeedleGauge::setMajorTickInterval(int interval)
{
    mMajorTickInterval = interval;

    update();
}

void NeedleGauge::setNumberOfTicks(int nTicks)
{
    mNumberOfTicks = nTicks;

    update();
}

void NeedleGauge::setMajorTickLengthAsPercent(int percent)
{
    if ( percent < 1 || percent > 10 )
        return;

    mMajorTickLengthAsPercent = percent;
    mMajorTickLength = mDiamXInPixels*(mMajorTickLengthAsPercent/100.0);

    update();
}

void NeedleGauge::setMinorTickLengthAsPercent(int percent)
{
    if ( percent < 1 || percent > 10 )
        return;

    mMinorTickLengthAsPercent = percent;
    mMinorTickLength = mDiamXInPixels*(mMinorTickLengthAsPercent/100.0);

    update();
}

void NeedleGauge::setTickColor(const QColor &color)
{
    if ( mTickColor == color )
        return;

    mTickColor = color;

    update();
}

QSize NeedleGauge::sizeHint() const
{
    return QSize(mDiamXInPixels, mDiamYInPixels);
}

QSize NeedleGauge::minimumSizeHint() const
{
    return QSize(mDiamXInPixels, mDiamYInPixels);
}

int NeedleGauge::heightForWidth(int w) const
{
    return w;
}

bool NeedleGauge::hasHeightForWidth() const
{
    return true;
}

void NeedleGauge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //calculateFontSize();

    mDegreesPerTick = (mEndAngle-mStartAngle)/mNumberOfTicks;
    mRatio = (mEndAngle-mStartAngle)/(mMaxValue-mMinValue);
    mAmountPerTick = (mMaxValue-mMinValue)/mNumberOfTicks;

    QPainter p;

    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //
    // Draw bevel
    //
    QRadialGradient bevelGradient(mCenter, mDiamXInPixels);
    bevelGradient.setColorAt(0.0, mFaceColor);
    bevelGradient.setColorAt(0.97, QColor("silver"));
    bevelGradient.setColorAt(1.0, QColor(mFaceColor));

    p.setPen(Qt::NoPen);
    p.setBrush(bevelGradient);
    p.drawEllipse(QRectF(0, 0, mDiamXInPixels, mDiamYInPixels));

    QPen pen(Qt::NoPen);
    p.setPen(pen);
    double marginFactor = mMarginSizeAsPercent/100.0;
    QRectF ellipseRect(mDiamXInPixels*marginFactor,
                       mDiamYInPixels*marginFactor,
                       mDiamXInPixels-mDiamXInPixels*marginFactor*2.0,
                       mDiamYInPixels-mDiamYInPixels*marginFactor*2.0);
    p.drawEllipse(ellipseRect);

    drawTicks(&p, mTickColor);
    drawAllNumbers(&p);
    drawNeedle(&p, mNeedleColor, mNeedleAngle);

    p.end();
}

void NeedleGauge::setValue(double value)
{
    if ( qFuzzyCompare(mValue, value) )
        return;

    if ( value > mMaxValue )
        value = mMaxValue;

    if ( value < mMinValue )
        value = mMinValue;

    if ( mDialAnimation->state() == QAbstractAnimation::Stopped )
    {
        //
        // Setup needle animation.
        //
        double newAngle = mRatio*(value-mMinValue)-45;
        mDialAnimation->setStartValue(mNeedleAngle);
        mDialAnimation->setEndValue(newAngle);
        mDialAnimation->setDuration(mTotalAnimationTime);

        mDialAnimation->start();

        mValue = value;
    }
}

void NeedleGauge::drawNeedle(QPainter *painter, const QColor& color, double degrees)
{
    double marginFactor = mMarginSizeAsPercent/100.0;
    double marginDistance = mDiamXInPixels*marginFactor;

    double needleWidthFactor = 0.025;
    double needleLengthFactor = 0.1;

    double needleSmallTriangleFactor = 0.058;

    double nwidth = needleWidthFactor*mRadius*2;
    double nlength = needleLengthFactor*mRadius*2;

    QPolygonF smallTriangle;
    smallTriangle << QPointF(mCenter.x()+nlength, mCenter.y()-nwidth) <<
                     QPointF(mCenter.x()+needleSmallTriangleFactor*mRadius*2, mCenter.y()) <<
                     QPointF(mCenter.x()+nlength, mCenter.y()+nwidth);       // lower point

    QPolygonF topTriangle;
    topTriangle << QPointF(mCenter.x()+nlength, mCenter.y()-nwidth) <<
                   QPointF(marginDistance+mMajorTickLength, mRadius) <<
                   QPointF(mCenter.x()+needleSmallTriangleFactor*mRadius*2, mCenter.y());

    QPolygonF bottomTriangle;
    bottomTriangle <<  QPointF(mCenter.x()+nlength, mCenter.y()+nwidth) <<
                   QPointF(marginDistance+mMajorTickLength, mRadius) <<
                   QPointF(mCenter.x()+needleSmallTriangleFactor*mRadius*2, mCenter.y());

    painter->save();

    painter->translate(mCenter);
    painter->rotate(degrees);
    painter->translate(-mCenter);

    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(color);
    painter->setPen(color.darker());
    painter->drawPolygon(smallTriangle);

    QPen pen;
    pen.setCosmetic(true);

    pen.setColor(color.darker());
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPolygon(topTriangle);

    pen.setColor(color.lighter());
    painter->setBrush(color.darker());
    painter->drawPolygon(bottomTriangle);

    painter->restore();
}

void NeedleGauge::drawTicks(QPainter *painter, const QColor& color)
{
    QPen tickPen(color);
    double angle = mStartAngle;

    painter->save();

    for ( int i=0; i<mNumberOfTicks+1; ++i )
    {
        painter->save(); // to prevent buildup of float inaccuracy in rotations.
        painter->translate(mCenter);
        painter->rotate(angle + (i*mDegreesPerTick));
        painter->translate(-mCenter);

        double tickLength;

        if ( i%mMajorTickInterval )
        {
            tickLength = mMinorTickLength;
            tickPen.setWidth(1);
        }
        else
        {
            tickLength = mMajorTickLength;
            tickPen.setWidth(4);
        }
        tickPen.setCapStyle(Qt::FlatCap);

        double radiusX = mDiamXInPixels/2.0;
        double radiusY = mDiamYInPixels/2.0;

        //QLineF tickLine(QPointF(10,radiusX), QPointF(10+tickLength, radiusY));
        QLineF tickLine(QPointF((mMarginSizeAsPercent/100)*mDiamXInPixels, radiusX),
                        QPointF((mMarginSizeAsPercent/100)*mDiamYInPixels+tickLength, radiusY));
        painter->setPen(tickPen);
        painter->drawLine(tickLine);

        painter->restore();
    }

    painter->restore();
}

void NeedleGauge::drawNumber(QPainter *painter, double number, double degrees)
{
    painter->save();

    double radians = qDegreesToRadians(degrees);

    QString ns = QString("%1").arg(number);

    //QFont font = painter->font();
    QFont font = mFont;
    //font.setPixelSize(mFontSize);
    painter->setFont(font);

    QFontMetrics fmetrics(font);
    QSize labelSize = fmetrics.size(Qt::TextSingleLine, ns);

    double fontPosFactor = 0.08;  // small adjustment to position

    double marginFactor = mMarginSizeAsPercent/100.0;
    double bevelDistanceX = mDiamXInPixels*marginFactor;
    double bevelDistanceY = mDiamYInPixels*marginFactor;

    double x = mCenter.x() + (mRadius-bevelDistanceX-mMajorTickLength-fontPosFactor*mRadius*2.0)*qCos(radians);
    double y = mCenter.y() + (mRadius-bevelDistanceY-mMajorTickLength-fontPosFactor*mRadius*2.0)*qSin(radians);

    painter->setPen(mFontColor);

    QRectF r(x, y, labelSize.width(), labelSize.height());
    r.moveCenter(QPointF(x, y));
    painter->drawText(r, Qt::AlignRight|Qt::AlignVCenter, ns);

    painter->restore();
}

void NeedleGauge::drawAllNumbers(QPainter *painter)
{
    double degrees = mStartAngle-180;
    double number = mMinValue;
    double arc = mEndAngle - mStartAngle;
    int additional = (qFuzzyCompare(arc, 360))?0:1;

    for ( int i=0; i<(mNumberOfTicks/mMajorTickInterval)+additional; ++i )
    {
        drawNumber(painter, number, degrees);

        degrees += (mMajorTickInterval*mDegreesPerTick);
        number += std::round(mAmountPerTick*mMajorTickInterval);
    }
}

void NeedleGauge::calculateFontSize()
{
    mFontSize = 1;

    QFont font = this->font();

    double FontWidthFactor = 0.147;
    double FontHeightFactor = 0.08;

    double width = FontWidthFactor*mRadius*2;
    double height = FontHeightFactor*mRadius*2;

    QRectF cRect(0, 0, width, height);

    while (true)
    {
        QFont f(font);
        f.setPixelSize(mFontSize);
        //QRectF r = QFontMetrics(f).boundingRect("9000");
        QRectF r = QFontMetrics(f).boundingRect("90");
        if ( r.width() < cRect.width() && r.height() < cRect.height() )
            mFontSize++;
        else {
            break;
        }
    }
}

void NeedleGauge::handleDialAnimationValueChanged(const QVariant& newValue)
{
    mNeedleAngle = newValue.toDouble();

    update();
}
