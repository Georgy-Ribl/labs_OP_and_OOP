#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <vector>

class ChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* parent = nullptr);
    void setData(const std::vector<int>& years,
                 const std::vector<double>& values,
                 double mn, double mx, double md);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    std::vector<int>    m_years;
    std::vector<double> m_values;
    double m_min, m_max, m_med;
};

#endif // CHARTWIDGET_H
