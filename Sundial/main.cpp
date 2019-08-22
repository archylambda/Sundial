#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

//void main_test2(){
//    Interface* interface = new Interface();

//    Location loc{36,36,50,36};

//    interface->timeAnalysis(loc, 3);

//    delete interface;
//}

//void main_test(){
//    Interface* interface = new Interface();

//    Date data(22,12,2019);
//    Location loc{0,0,0,0};

//    interface->oneDayAnalysis(data, loc);

//    delete interface;
//}
//void ArmaTest(){
//    vec X(17);
//    X(0) = 1; X(1) = 2; X(2) = 3;
//    X(3)=5;
//    double res = norm(X);
//    cout << res << endl;
//}

//int main()
//{

//    try{
//        main_test();
//        cout << "well done" << endl;
//    } catch (exception& e) {
//        cout << "Exception got: " << e.what() << endl;
//    }
//    return 0;
//}
