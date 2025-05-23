#include "chartwidget.h"
#include <QPainter>
#include <QPen>
#include <QFontMetrics>
#include <QPainterPath>
#include <algorithm>
#include <cmath>

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget(parent)
{
}

void ChartWidget::setData(const std::vector<int>* years,
                          const std::vector<double>* values,
                          double minValue,
                          double maxValue,
                          double medianValue)
{
    m_years = years;
    m_values = values;
    m_minValue = minValue;
    m_maxValue = maxValue;
    m_medianValue = medianValue;
    update();
}

void ChartWidget::paintEvent(QPaintEvent*)
{
    if (!m_years || !m_values || m_years->empty() || m_values->empty()) {
        return;
    }

    if (m_years->size() != m_values->size()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = palette().color(QPalette::Window);
    painter.fillRect(rect(), bgColor);

    int w = width();
    int h = height();

    const int marginLeft = 60;
    const int marginBottom = 50;
    const int marginTop = 20;
    const int marginRight = 20;

    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(marginLeft, marginTop, marginLeft, h - marginBottom); // ось Y
    painter.drawLine(marginLeft, h - marginBottom, w - marginRight, h - marginBottom); // ось X

    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);
    QFontMetrics fm(font);

    int stepsY = 5;
    for (int i = 0; i <= stepsY; ++i) {
        double val = m_minValue + (m_maxValue - m_minValue) * i / stepsY;
        int y = h - marginBottom - (h - marginTop - marginBottom) * i / stepsY;
        QString text = QString::number(val, 'f', 2);
        painter.drawText(marginLeft - fm.horizontalAdvance(text) - 10, y + fm.height() / 2 - 3, text);
        painter.drawLine(marginLeft - 4, y, marginLeft, y);
    }

    int n = (int)m_years->size();
    if (n < 2) {
        painter.drawText(marginLeft + 10, marginTop + 20, "Недостаточно данных");
        return;
    }

    double stepX = (double)(w - marginLeft - marginRight) / (n - 1);

    int maxLabels = 10;
    int labelStep = n / maxLabels;
    if (labelStep == 0) labelStep = 1;

    for (int i = 0; i < n; i += labelStep) {
        int x = marginLeft + static_cast<int>(stepX * i);
        QString yearText = QString::number(m_years->at(i));
        painter.drawText(x - fm.horizontalAdvance(yearText) / 2, h - marginBottom + fm.height() + 10, yearText);
        painter.drawLine(x, h - marginBottom, x, h - marginBottom + 4);
    }

    auto valueToY = [&](double val) {
        return h - marginBottom - (val - m_minValue) / (m_maxValue - m_minValue) * (h - marginTop - marginBottom);
    };

    std::vector<double> smoothValues(n);
    int windowSize = 5;
    for (int i = 0; i < n; ++i) {
        int count = 0;
        double sum = 0;
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; ++j) {
            if (j >= 0 && j < n) {
                sum += m_values->at(j);
                count++;
            }
        }
        smoothValues[i] = sum / count;
    }

    painter.setPen(QPen(Qt::white, 3));
    QPainterPath path;
    path.moveTo(marginLeft, valueToY(smoothValues[0]));
    for (int i = 1; i < n; ++i) {
        double ctrlX = (marginLeft + stepX * (i - 1) + marginLeft + stepX * i) / 2;
        path.quadTo(ctrlX, valueToY(smoothValues[i - 1]), marginLeft + stepX * i, valueToY(smoothValues[i]));
    }
    painter.drawPath(path);

    painter.setPen(QPen(Qt::red));
    painter.setBrush(Qt::red);
    int medianIndex = 0;
    double minDist = 1e9;
    for (int i = 0; i < n; ++i) {
        double diff = std::abs(m_values->at(i) - m_medianValue);
        if (diff < minDist) {
            minDist = diff;
            medianIndex = i;
        }
    }
    int medianX = marginLeft + static_cast<int>(stepX * medianIndex);
    int medianY = valueToY(m_values->at(medianIndex));
    painter.drawEllipse(QPoint(medianX, medianY), 5, 5);
    painter.drawText(medianX + 5, medianY - 5, "Med");

    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
    int yMin = valueToY(m_minValue);
    int yMax = valueToY(m_maxValue);
    int yMed = valueToY(m_medianValue);
    painter.drawLine(marginLeft, yMin, w - marginRight, yMin);
    painter.drawLine(marginLeft, yMax, w - marginRight, yMax);
    painter.drawLine(marginLeft, yMed, w - marginRight, yMed);

    painter.setPen(Qt::white);
    painter.drawText(w - marginRight - 50, yMin - 5, "Min");
    painter.drawText(w - marginRight - 50, yMax - 5, "Max");
    painter.drawText(w - marginRight - 50, yMed - 5, "Median");
}
