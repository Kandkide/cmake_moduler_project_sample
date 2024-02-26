#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // ボタンを作成
    QPushButton button("クリックしてください", nullptr);

    // ボタンがクリックされたときの処理を設定
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        // メッセージボックスを表示
        QMessageBox::information(nullptr, "メッセージ", "ボタンがクリックされました！");
    });

    // ウィンドウを表示
    button.show();

    // アプリケーションを実行
    return app.exec();
}
