#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <vector>

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void setData(const std::vector<int>* years,
                 const std::vector<double>* values,
                 double minValue,
                 double maxValue,
                 double medianValue);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const std::vector<int>* m_years = nullptr;
    const std::vector<double>* m_values = nullptr;

    double m_minValue = 0.0;
    double m_maxValue = 0.0;
    double m_medianValue = 0.0;
};

#endif // CHARTWIDGET_H
