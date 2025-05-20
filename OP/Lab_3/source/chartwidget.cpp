#include "chartwidget.h"
#include <QPainter>
#include <QFont>

ChartWidget::ChartWidget(QWidget* parent)
    : QWidget(parent), m_min(0), m_max(0), m_med(0) {}

void ChartWidget::setData(const std::vector<int>& years,
                          const std::vector<double>& values,
                          double mn, double mx, double md) {
    m_years = years;
    m_values = values;
    m_min = mn; m_max = mx; m_med = md;
    update();
}

void ChartWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QRectF r = contentsRect();
    p.drawLine(r.bottomLeft(), r.bottomRight());
    p.drawLine(r.bottomLeft(), r.topLeft());
    p.setFont(QFont("Arial",8));
    p.drawText(r.bottomRight()+QPointF(-30,-5), "Year");
    p.drawText(r.topLeft()+QPointF(5,15), "Value");
    if (m_years.empty())
        return;
    double x0=r.left(), x1=r.right(), y0=r.bottom(), y1=r.top();
    int n=m_years.size();
    int ymin=m_years.front(), ymax=m_years.back();

    auto mapX= [&](int yr){ return x0 + double(yr-ymin)/(ymax-ymin)*(x1-x0); };
    auto mapY= [&](double v){ return y0 - (v-m_min)/(m_max-m_min)*(y0-y1); };

    for(int i=1; i<n; ++i)
        p.drawLine(QPointF(mapX(m_years[i-1]),mapY(m_values[i-1])),
                   QPointF(mapX(m_years[i]),  mapY(m_values[i])));
    p.setBrush(Qt::red);
    p.drawEllipse(QPointF(mapX(m_years.front()), mapY(m_min)),4,4);
    p.drawEllipse(QPointF(mapX(m_years.back()),  mapY(m_max)),4,4);
    int mid = n/2;
    p.drawEllipse(QPointF(mapX(m_years[mid]),   mapY(m_med)),4,4);
    p.setFont(QFont("Arial",7));
    p.drawText(mapX(m_years.front()), mapY(m_min)-5, "Min");
    p.drawText(mapX(m_years.back()),  mapY(m_max)-5, "Max");
    p.drawText(mapX(m_years[mid]),    mapY(m_med)-5, "Med");
}
