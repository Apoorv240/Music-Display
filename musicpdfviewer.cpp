#include "musicpdfviewer.h"
#include <QFileDialog>
#include <QHBoxLayout>

MusicPdfViewer::MusicPdfViewer(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    //layout->setMargin(0);

    pdfView = new QPdfView(this);
    layout->addWidget(pdfView);

    this->document = new QPdfDocument();
    this->currentZoom = 1;
}

MusicPdfViewer::~MusicPdfViewer() {
    delete document;
    delete pdfView;
}


void MusicPdfViewer::openPath(QString filepath) {
    document->load(filepath);
    pdfView->setDocument(document);
    pdfView->setPageMode(QPdfView::PageMode::MultiPage);
}

void MusicPdfViewer::open() {
    openPath(QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("PDF Files (*.pdf)")));
}

void MusicPdfViewer::close() {
    document->close();
    emit closed();
}

//void MusicPdfViewer::closed() {}

void MusicPdfViewer::zoomTo(double zoom) {
    currentZoom = zoom;
    pdfView->setZoomFactor(zoom);
}

void MusicPdfViewer::incrementZoom() {
    zoomTo(currentZoom + 0.15);
}

void MusicPdfViewer::decrementZoom() {
    zoomTo(currentZoom - 0.15);
}

void MusicPdfViewer::resetZoom() {
    zoomTo(1);
}
