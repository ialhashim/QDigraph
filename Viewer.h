#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

namespace Ui {
class Viewer;
}

class Viewer : public QWidget
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

private:
    Ui::Viewer *ui;

public slots:
    void insertLogItem(QString msg);

    void addNode(QString node_info);
    void addEdge(QString edge_info);
	void updateGraph();
	void addCSS(QString style_code);

    void doTestGraph();

signals:
    void addLogItem(QString msg);
};

#endif // VIEWER_H
