#pragma once

#include <QWidget>

class LEDWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double diameterMM READ diameterMM WRITE setDiameterMM) // mm
    Q_PROPERTY(double diameter READ diameter) // pixels
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool state READ state WRITE setState)
    Q_PROPERTY(bool flashing READ isFlashing WRITE setFlashing)
    Q_PROPERTY(int flashRate READ flashRate WRITE setFlashRate)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(unsigned int id READ id)
    Q_PROPERTY(Qt::Edge labelEdge READ labelEdge WRITE setLabelEdge)
    //Q_PROPERTY(Qt::Orientation labelOrientation READ labelOrientation WRITE setLabelOrientation)
    Q_PROPERTY(int margin READ margin WRITE setMargin)

public:
    LEDWidget(QWidget *parent = 0);

    double diameter() const;

    double diameterMM() const
    {
        return m_diameterMM;
    }

    void setDiameterMM(double diameterMM);

    QColor color() const;
    void setColor(const QColor& color);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    bool state() const;

    bool isFlashing() const;

    int flashRate() const;

    QString name() const
    {
        return m_name;
    }

    QString label() const
    {
        return m_label;
    }

    QFont textFont() const
    {
        return m_textFont;
    }

    unsigned int id() const
    {
        return m_id;
    }

    Qt::Edge labelEdge() const
    {
        return m_labelEdge;
    }

    Qt::Orientation labelOrientation() const
    {
        return m_labelOrientation;
    }

    int margin() const;

public slots:
    void setState(bool state);
    void toggleState();
    void setFlashing(bool flashing);
    void setFlashRate(int rate);
    void startFlashing();
    void stopFlashing();
    void setName(QString name)
    {
        m_name = name;
    }

    void setTextFont(QFont textFont)
    {
        m_textFont = textFont;

        update();
    }

    void setLabelEdge(Qt::Edge labelEdge)
    {
        m_labelEdge = labelEdge;

        update();
    }

    void setLabelOrientation(Qt::Orientation orientation)
    {
        if (m_labelOrientation == orientation)
            return;

        m_labelOrientation = orientation;

        update();
    }

    void setMargin(int margin);

    // QWidget interface
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int width) const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_color = QColor("red");
    Qt::Alignment m_alignment = Qt::AlignHCenter|Qt::AlignVCenter;
    bool m_initialState = true;
    bool m_state = true;
    int m_flashRate = 200;
    bool m_flashing = false;
    int m_margin=9;

    //
    // Pixels per mm for x and y...
    //
    double m_pixX = 0.0;
    double m_pixY = 0.0;

    //
    // Scaled values for x and y diameter.
    //
    double m_diamXInPixels = 0.0;
    double m_diamYInPixels = 0.0;

    QRadialGradient gradient_;
    QTimer* m_timer = nullptr;
    double m_diameterMM = 5;
    QString m_name = "LED";
    QString m_label = "LED 0";
    QFont m_textFont = font();
    unsigned int m_id = 0;
    Qt::Edge m_labelEdge = Qt::LeftEdge;
    Qt::Orientation m_labelOrientation = Qt::Horizontal;
    QSize m_fontSize = QSize(0,0);

    QPointF m_center = QPointF(0,0);
    double m_radius = 0;

    // QWidget interface
public:
    bool hasHeightForWidth() const override;
};

