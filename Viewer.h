#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QWebFrame>
#include <QWebView>

namespace Ui {
class Viewer;
}

class Viewer : public QWidget
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    Ui::Viewer *ui;
    QWebView * wv;

public slots:
    void insertLogItem(QString msg);

    int addNode(QString node_info);
    void addEdge(QString edge_info);
    void addEdge(int nid1, int nid2);

	void updateGraph();
	void addCSS(QString style_code);

    void doTestGraph();

signals:
    void addLogItem(QString msg);
};

#endif // VIEWER_H
