#include "Viewer.h"
#include "ui_Viewer.h"
#include <QWebFrame>

Viewer::Viewer(QWidget *parent) : QWidget(parent), ui(new Ui::Viewer)
{
    Q_INIT_RESOURCE(Viewer);
    ui->setupUi(this);

    // Add pointer to me
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("Viewer", this);

    // Test interaction
    connect(ui->doJavaScript, &QPushButton::released, [&]{
        ui->webView->page()->mainFrame()->evaluateJavaScript("g.setEdge(1,3); render(inner, g);");
    });

    // Logging:
    connect(this, SIGNAL(addLogItem(QString)), SLOT(insertLogItem(QString)));
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::insertLogItem(QString msg)
{
    ui->logWidget->insertItem(ui->logWidget->count(), msg);
}
