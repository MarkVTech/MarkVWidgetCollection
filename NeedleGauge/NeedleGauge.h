#pragma once

#include <QWidget>

class QVariantAnimation;

class NeedleGauge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(double diameterMM READ diameterMM WRITE setDiameterMM NOTIFY diameterMMChanged)
    Q_PROPERTY(QColor faceColor READ faceColor WRITE setFaceColor NOTIFY faceColorChanged)
    Q_PROPERTY(int marginSizeAsPercent READ marginSizeAsPercent WRITE setMarginSizeAsPercent)
    Q_PROPERTY(QColor needleColor READ needleColor WRITE setNeedleColor)
    Q_PROPERTY(QFont font READ font WRITE setFont)
    Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(int majorTickInterval READ majorTickInterval WRITE setMajorTickInterval)
    Q_PROPERTY(int numberOfTicks READ numberOfTicks WRITE setNumberOfTicks)
    Q_PROPERTY(int majorTickLengthAsPercent READ majorTickLengthAsPercent WRITE setMajorTickLengthAsPercent) // 1-100
    Q_PROPERTY(int minorTickLengthAsPercent READ minorTickLengthAsPercent WRITE setMinorTickLengthAsPercent) // 1-100
    Q_PROPERTY(QColor tickColor READ tickColor WRITE setTickColor)

public:
    NeedleGauge(QWidget *parent = 0);

    double value() const;

    double diameterMM() const;
    QColor faceColor() const;
    int marginSizeAsPercent() const;
    QColor needleColor() const;
    QFont font() const;
    QColor fontColor() const;

    double minValue() const;
    double maxValue() const;
    int majorTickInterval() const;
    int numberOfTicks() const;
    int majorTickLengthAsPercent() const;
    int minorTickLengthAsPercent() const;
    QColor tickColor() const;


public slots:
    void setValue(double value);
    void setDiameterMM(double diameter);
    void setFaceColor(const QColor& color);
    void setMarginSizeAsPercent(int percent);
    void setNeedleColor(const QColor& color);
    void setFont(const QFont& font);
    void setFontColor(const QColor& color);

    void setMinValue(double value);
    void setMaxValue(double value);
    void setMajorTickInterval(int interval);
    void setNumberOfTicks(int nTicks);
    void setMajorTickLengthAsPercent(int percent);
    void setMinorTickLengthAsPercent(int percent);
    void setTickColor(const QColor& color);

signals:
    void diameterMMChanged(double newDiameter);
    void faceColorChanged(const QColor& newColor);

private:
    double mValue = 0.0;
    double mDiameterMM = 100;
    QColor mFaceColor = QColor("green");
    double mMarginSizeAsPercent = 5.0;
    QColor mNeedleColor = QColor("lightgray");
    QFont mFont;
    QColor mTickColor = QColor("black");
    QColor mFontColor = QColor("black");

    double mMinorTickLength = 0;
    double mMajorTickLength = 0;
    double mDegreesPerTick;
    int mFontSize=1;
    int mUnitsLabelFontSize=1;
    QFont mUnitsLabelFont;
    double mRatio=0.0;
    int mMajorTickInterval=10;
    int mNumberOfTicks=100;
    int mMajorTickLengthAsPercent=10;
    int mMinorTickLengthAsPercent=8;
    double mAmountPerTick=100;
    double mStartAngle=-45;
    double mEndAngle=225;
    double mMinValue = 0;
    double mMaxValue = 9999;
    QString mLabel = " ";

    double mDiameterInPixels;
    double mRadius;

    int mTotalAnimationTime = 250;

    // QWidget interface
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int w) const override;
    bool hasHeightForWidth() const override;

    void calculateFontSize();
    void drawNeedle(QPainter *painter, const QColor &color, double degrees);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawTicks(QPainter* painter, const QColor& color);
    void drawNumber(QPainter* painter, double number, double degrees);
    void drawAllNumbers(QPainter* painter);

    // Pixels per mm for x and y...
    //
    double mPixX = 0.0;
    double mPixY = 0.0;

    //
    // Scaled values for x and y diameter.
    //
    double mDiamXInPixels = 0.0;
    double mDiamYInPixels = 0.0;

    QPointF mCenter = QPointF(0,0);

    QVariantAnimation* mDialAnimation=nullptr;
    double mNeedleAngle=-45;

private slots:
     void handleDialAnimationValueChanged(const QVariant& newValue);

};

