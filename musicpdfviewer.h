#ifndef MUSICPDFVIEWER_H
#define MUSICPDFVIEWER_H

#include <QPdfView>
#include <QPdfDocument>

class MusicPdfViewer : public QWidget
{
    Q_OBJECT
public:
    MusicPdfViewer(QWidget *parent = nullptr);
    ~MusicPdfViewer();
public slots:
    void openPath(QString filepath);
    void open();
    void close();

    void incrementZoom();
    void decrementZoom();
    void zoomTo(double zoom);
    void resetZoom();

signals:
    void closed();

private:
    QPdfDocument *document;
    QPdfView *pdfView;
    double currentZoom;
};

#endif // MUSICPDFVIEWER_H
