#ifndef RGBHISTOGRAMMODEL_H
#define RGBHISTOGRAMMODEL_H

#include <QAbstractListModel>
#include "rgbhistogram.h"

class RgbHistogramModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(RgbHistogram *histogram READ histogram WRITE setHistogram NOTIFY histogramChanged)

public:
    enum HistogramRoles {
         BinNumberRole = Qt::UserRole + 1,
         RedCountRole,
         GreenCountRole,
         BlueCountRole
     };

    RgbHistogramModel(QObject *parent = 0): QAbstractListModel(parent), m_histogram(0) { }

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[BinNumberRole] = "binNumber";
        roles[RedCountRole] = "redCount";
        roles[GreenCountRole] = "greenCount";
        roles[BlueCountRole] = "blueCount";
        return roles;
    }

    int rowCount(const QModelIndex &) const { return m_histogram->binCount(); }

    QVariant data(const QModelIndex &index, int role) const {
        if (!m_histogram)
            return QVariant(0);
        int bin = index.row();
        switch(role) {
        case BinNumberRole:
            return bin;
        case RedCountRole:
            return m_histogram->redCount(bin);
        case GreenCountRole:
            return m_histogram->greenCount(bin);
        case BlueCountRole:
            return m_histogram->blueCount(bin);
        }
        return 0;
    }

    RgbHistogram *histogram() const { return m_histogram; }

public slots:
    void histogramUpdated() {
        beginResetModel();
        endResetModel();

        emit dataChanged(index(0,0), index(m_histogram->binCount() -1, 0));
    }

    void setHistogram(RgbHistogram *histogram)
    {
        if (m_histogram != histogram) {
            m_histogram = histogram;
            connect(m_histogram, SIGNAL(histogramUpdated()), this, SLOT(histogramUpdated()));
            histogramUpdated();
            emit histogramChanged(histogram);
        }
    }

signals:
    void histogramChanged(RgbHistogram *histogram);

private:
    RgbHistogram *m_histogram;
};

#endif // RGBHISTOGRAMMODEL_H
