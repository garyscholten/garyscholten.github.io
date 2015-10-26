#ifndef RGBHISTOGRAM_H
#define RGBHISTOGRAM_H

#include <QObject>
#include <QUrl>
#include <QVector>

class RgbHistogram : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(int binCount READ binCount WRITE setBinCount NOTIFY binCountChanged)
    Q_PROPERTY(int maxValue READ maxValue NOTIFY maxValueChanged)

public:
    explicit RgbHistogram(QObject *parent = 0);

    Q_INVOKABLE int redCount(int bin) const;
    Q_INVOKABLE int greenCount(int bin) const;
    Q_INVOKABLE int blueCount(int bin) const;
    Q_INVOKABLE void compute();

    int binCount() const { return m_binCount; }
    QUrl imageSource() const { return m_imageSource; }
    int maxValue() const { return m_maxValue; }

signals:
    void histogramUpdated();

    void binCountChanged(int binCount);

    void imageSourceChanged(QUrl imageSource);

    void maxValueChanged(int maxValue);

public slots:
void setBinCount(int binCount)
{
    if (m_binCount != binCount) {
        m_binCount = binCount;
        m_bins.resize(m_binCount);
        m_bins.fill(RgbHistogram::RgbBin());
        emit binCountChanged(binCount);
    }
}
void setImageSource(QUrl imageSource)
{
    if (m_imageSource == imageSource)
        return;
    m_imageSource = imageSource;
    emit imageSourceChanged(imageSource);
}

private:
    inline int binForValue(int v) { return v * m_binCount / 256; }

    struct RgbBin {
        int red;
        int green;
        int blue;
    };

    QUrl m_imageSource;
    int m_binCount;
    QVector<RgbBin> m_bins;
    int m_maxValue;
};

#endif // RGBHISTOGRAM_H
