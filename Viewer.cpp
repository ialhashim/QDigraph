#include "Viewer.h"
#include "ui_Viewer.h"

Viewer::Viewer(QWidget *parent) : QWidget(parent), ui(new Ui::Viewer)
{
    Q_INIT_RESOURCE(Viewer);
    ui->setupUi(this);

    wv = new QWebView();
    ui->mainlayout->addWidget(wv);

    wv->load(QUrl("qrc:/Viewer.html"));

	// Logging:
	connect(this, SIGNAL(addLogItem(QString)), SLOT(insertLogItem(QString)));

    // Add pointer to me
    wv->page()->mainFrame()->addToJavaScriptWindowObject("Viewer", this);

	// Demo:
	connect(ui->testGraph, SIGNAL(clicked()), SLOT(doTestGraph()));
}

void Viewer::doTestGraph()
{
    // Add sample nodes
    addNode("TOP,type-TOP");
    addNode("S,type-S");
    addNode("NP,type-NP");
    addNode("DT,type-DT");
    addNode("This,type-TK");
    addNode("VP,type-VP");
    addNode("VBZ,type-VBZ");
    addNode("is,type-TK");
    addNode("NP,type-NP");
    addNode("DT,type-DT");
    addNode("an,type-TK");
    addNode("NN,type-NN");
    addNode("example,type-TK");
    addNode(".,type-.");
    addNode("sentence,type-TK");

    // Add sample edges
    addEdge("3,4");
    addEdge("2,3");
    addEdge("1,2");
    addEdge("6,7");
    addEdge("5,6");
    addEdge("9,10");
    addEdge("8,9");
    addEdge("11,12");
    addEdge("8,11");
    addEdge("5,8");
    addEdge("1,5");
    addEdge("13,14");
    addEdge("1,13");
    addEdge("0,1");

    // Test interaction with javascript
    connect(ui->doJavaScript, &QPushButton::released, [&]{
        wv->page()->mainFrame()->evaluateJavaScript("g.setEdge(1,3);");
		updateGraph();
    });

    updateGraph();
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::insertLogItem(QString msg)
{
    ui->logWidget->insertItem(ui->logWidget->count(), msg);
}

int Viewer::addNode(QString node_info)
{
    QStringList params = node_info.split(",");
    if(params.size() < 2) params << "";

	auto cmd = QString("addNodeToGraph(g, '%1', '%2')").arg(params[0]).arg(params[1]);
    return wv->page()->mainFrame()->evaluateJavaScript(cmd).toInt();
}

void Viewer::addEdge(QString edge_info)
{
    QStringList params = edge_info.split(",");
    if(params.size() < 2) return;

    addEdge(params[0].toInt(), params[1].toInt());
}

void Viewer::addEdge(int nid1, int nid2)
{
    auto cmd = QString("addEdgeToGraph(g, %1, %2)").arg(nid1).arg(nid2);
    wv->page()->mainFrame()->evaluateJavaScript(cmd);
}

void Viewer::addCSS(QString style_code)
{
	auto cmd = QString("$('<style type=\"text/css\"> %1 </style>').appendTo('head')").arg(style_code);
    wv->page()->mainFrame()->evaluateJavaScript(cmd);
}

void Viewer::updateGraph()
{
    wv->page()->mainFrame()->evaluateJavaScript("render(inner, g);");
    wv->page()->mainFrame()->evaluateJavaScript("postProcessGraph(g);");
}
