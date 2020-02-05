#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QWebEngineView;
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);

    void viewSource();

    void highlightAllLinks();
    void removeGifImages();

private:
    QString jQuery;
    QWebEngineView *view;
    QLineEdit *locationEdit;
    int progress;
};
