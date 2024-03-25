#pragma once
#include "Bloc.h"
#include "LocatarRepo.h"
#include "validator.h"
#include <qwidget.h>
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qpainter.h>

class cosRDOnlyGUI : public QWidget, public Observer
{
private:

    Bloc& ctr;
    void update() override {
        repaint();
    }

public:

    cosRDOnlyGUI(Bloc& bloc) : ctr{  bloc }
    {
        ctr.addObserver(this);
    }

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };

        for (const auto a : ctr.getNotificari())
        {
            int x = rand() % (width() - 20);
            int y = rand() % (height() - 20);
            p.drawRect(x, y, 20, 20);
        }//drawEllipse pt cerc
        /*QPainter p{ this };

        int startx = 10;
        int spacing = 10;
        int y = height() / 2 - 10;
        int i = 0;
        for (const auto a : ctr.getNotificari())
        {
            int x = startx + (20 + spacing) * i;
            i++;
            p.drawRect(x, y, 20, 20);
        }*/
    }

    ~cosRDOnlyGUI()
    {
        ctr.removeObserver(this);
    }
};

class NotificariWindow : public QDialog, public Observer {
public:
    NotificariWindow(Bloc& bloc) : ctr(bloc) {
        ctr.addObserver(this);
        initGUI();
        loadData();
        
    }

    void update() override {
        loadData();
    }

private:
    Bloc& ctr;

    QListWidget* lstnot = new QListWidget;
    QPushButton* btnNot = new QPushButton{ "&Adauga Notificare" };
    QPushButton* btnGolNot = new QPushButton{ "&Golire Notificari" };
    QPushButton* btnGenNot = new QPushButton{ "&Generare Notificari" };

    QLineEdit* txtAp = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtPoz = new QLineEdit;

    void initGUI() {
        QVBoxLayout* layout = new QVBoxLayout;

        auto Notificari = new QFormLayout;
        Notificari->addWidget(lstnot);

        auto notificari = new QHBoxLayout;
        notificari->addWidget(btnNot);
        notificari->addWidget(btnGolNot);
        notificari->addWidget(btnGenNot);
        Notificari->addRow(notificari);

        Notificari->addRow("Apartament", txtAp);
        Notificari->addRow("Nume", txtNume);

        layout->addLayout(Notificari);

        setLayout(layout);
        setWindowTitle("Notificari");

        initConnect();
    }

    void loadData() {
        lstnot->clear();
        for (const auto& n : ctr.getNotificari()) {
            string c;
            c = std::to_string(n.getAp()) + " " + n.getNume() + " " + std::to_string(n.getSup()) + " " + n.getTip();
            lstnot->addItem(QString::fromStdString(c));
        }
        
    }

    void initConnect() {
        QObject::connect(btnNot, &QPushButton::clicked, [&]() {
            auto ap = txtAp->text();
            auto nume = txtNume->text();
            ctr.addNotificare(ap.toInt(), nume.toStdString());
            loadData();
            update();
            });

        QObject::connect(btnGolNot, &QPushButton::clicked, [&]() {
            ctr.golesteNotificari();
            loadData();
            update();
            });

        QObject::connect(btnGenNot, &QPushButton::clicked, [&]() {
            auto poz = txtPoz->text();
            ctr.randomNotificari(poz.toInt());
            loadData();
            update();
            });
    }
};



class GUI : public QWidget , public Observer {
public:
    GUI(Bloc& bloc) : ctr(bloc) {
        initGUI();
        initConnect();
        loadData();
    }

private:


    Bloc& ctr;

    QListWidget* lst = new QListWidget;
    QTableWidget* tabel = new QTableWidget;

    QListWidget* lstnot = new QListWidget;
    QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
    QPushButton* btnSterge = new QPushButton{ "&Sterge" };
    QPushButton* btnModifica = new QPushButton{ "&Modifica" };
    QPushButton* btnUndo = new QPushButton{ "&Undo" };

    QPushButton* btnSortNum = new QPushButton{ "&Sort Nume" };
    QPushButton* btnSortSup = new QPushButton{ "&Sort Sup" };
    QPushButton* btnSortSupTip = new QPushButton{ "&Sort Sup/Tip" };

    QPushButton* btnFiltSup= new QPushButton{ "&Filt Sup" };
    QPushButton* btnFiltTip = new QPushButton{ "&Filt Tip" };

    QPushButton* btnNrAp = new QPushButton{ "&Nr. Apartamente" };
    QPushButton* btnNrGa = new QPushButton{ "&Nr. Garsoniere" };

    QPushButton* btnNot = new QPushButton{ "&Adauga Notificare" };
    QPushButton* btnGolNot = new QPushButton{ "&Golire Notificari" };
    QPushButton* btnGenNot = new QPushButton{ "&Generare Notificari" };

    QPushButton* btnWindow = new QPushButton{ "&Notificari" };
    QPushButton* btnDesen = new QPushButton{ "&Desen" };

    QPushButton* btnAddNotMain = new QPushButton{ "&Adauga Notificare" };
    QPushButton* btnGolNotMain = new QPushButton{ "&Golire Notificari" };
    QPushButton* btnGenNotMain = new QPushButton{ "&Generare Notificari" };

    QLineEdit* txtAp = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtSup = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPoz = new QLineEdit;




    void initConnect() {

        QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
            auto ap = txtAp->text();
            auto nume = txtNume->text();
            auto sup = txtSup->text();
            auto tip = txtTip->text();
            try {
                ctr.addLocatar(ap.toInt(), nume.toStdString(), sup.toFloat(), tip.toStdString());
            }
            catch (const LocatarRepoException& ex) {
                cout << ex << '\n';
            }
            //QMessageBox::information(nullptr, "Adauga", "Locatar adaugat");
            loadData();
            });
        QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
            auto poz = txtPoz->text();
            int poz1 = poz.toInt();
            ctr.stergeLocatar(--poz1);
            loadData();
            });
        QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
            auto ap = txtAp->text();
            auto nume = txtNume->text();
            auto sup = txtSup->text();
            auto tip = txtTip->text();
            auto poz = txtPoz->text();
            int poz1 = poz.toInt();
            ctr.ModificaLocatar(ap.toInt(), nume.toStdString(), sup.toFloat(), tip.toStdString(), --poz1);
            loadData();
            });
        QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
            ctr.undo();
            loadData();
            });

        QObject::connect(btnNrAp, &QPushButton::clicked, [&]() {
            int nr=0;
            for (const auto& n : ctr.getAll()) {
                if (n.getTip() == "Apartament") {
                    nr++;
                }
            }
            QMessageBox::information(nullptr, "Nr. Ap", QString::number(nr));
            });
        QObject::connect(btnNrGa, &QPushButton::clicked, [&]() {
            int nr = 0;
            for (const auto& n : ctr.getAll()) {
                if (n.getTip() == "Garsoniera") {
                    nr++;
                }
            }
            QMessageBox::information(nullptr, "Nr. Ap", QString::number(nr));
            });

        QObject::connect(btnSortNum, &QPushButton::clicked, [&]() {
            loadDataSort(ctr.sortByNume());
            });
        QObject::connect(btnSortSup, &QPushButton::clicked, [&]() {
            loadDataSort(ctr.sortBySup());
            });
        QObject::connect(btnSortSupTip, &QPushButton::clicked, [&]() {
            loadDataSort(ctr.sortByTipSuprafata());
            });

        QObject::connect(btnFiltSup, &QPushButton::clicked, [&]() {
            auto sup = txtSup->text();
            float x = sup.toFloat();
            loadDataSort(ctr.filtrareSup(x));
            });
        QObject::connect(btnFiltTip, &QPushButton::clicked, [&]() {
            auto tip = txtTip->text();
            string x = tip.toStdString();
            loadDataSort(ctr.filtrareTip(x));
            });

        QObject::connect(btnNot, &QPushButton::clicked, [&]() {
            auto ap = txtAp->text();
            auto nume = txtNume->text();
            ctr.addNotificare(ap.toInt(), nume.toStdString());
            loadDataNot();
            });

        QObject::connect(btnGolNot, &QPushButton::clicked, [&]() {
            ctr.golesteNotificari();
            loadDataNot();
            });

        QObject::connect(btnGenNot, &QPushButton::clicked, [&]() {
            auto poz = txtPoz->text();
            ctr.randomNotificari(poz.toInt());
            loadDataNot();
            });
        QObject::connect(btnWindow, &QPushButton::clicked, [&]() {
            NotificariWindow* notificariWindow = new NotificariWindow(ctr);
            notificariWindow->show();
            ctr.addObserver(notificariWindow);
            update();
            });
        QObject::connect(btnDesen, &QPushButton::clicked, [&]() {
            cosRDOnlyGUI* wind = new cosRDOnlyGUI{ ctr };
            wind->show();
            });
        QObject::connect(btnAddNotMain, &QPushButton::clicked, [&]() {
            auto ap = txtAp->text();
            auto nume = txtNume->text();
            ctr.addNotificare(ap.toInt(), nume.toStdString());
            update();
            });
        QObject::connect(btnGolNotMain, &QPushButton::clicked, [&]() {
            ctr.golesteNotificari();
            update();
            });
        QObject::connect(btnGenNotMain, &QPushButton::clicked, [&]() {
            auto nr = txtPoz->text();
            ctr.randomNotificari(nr.toInt());
            update();
            });

    }
    void loadDataNot() {
        lstnot->clear();
        for (const auto& n : ctr.getNotificari()) {
            string c;
            c = std::to_string(n.getAp()) + " " + n.getNume() + " " + std::to_string(n.getSup()) + " " + n.getTip();
            lstnot->addItem(QString::fromStdString(c));
        }
    }
    void loadDataSort(vector<Locatar> p) {
        tabel->clear();
        int row = 0;
        tabel->setRowCount(0);
        for (const auto& n : p) {
            QTableWidgetItem* ap = new QTableWidgetItem(QString::number(n.getAp()));
            QTableWidgetItem* nume = new QTableWidgetItem(QString::fromStdString(n.getNume()));
            QTableWidgetItem* sup = new QTableWidgetItem(QString::number(n.getSup()));
            QTableWidgetItem* tip = new QTableWidgetItem(QString::fromStdString(n.getTip()));
            tabel->insertRow(row);
            tabel->setItem(row, 0, ap);
            tabel->setItem(row, 1, nume);
            tabel->setItem(row, 2, sup);
            tabel->setItem(row, 3, tip);
            row++;

        }
    }

    void update() override {
        loadDataNot();
    }
    void loadData() {
        tabel->clear();
        int row = 0;
        tabel->setRowCount(0);
        for (const auto& n : ctr.getAll()) {
            QTableWidgetItem* ap = new QTableWidgetItem(QString::number(n.getAp()));
            QTableWidgetItem* nume = new QTableWidgetItem(QString::fromStdString(n.getNume()));
            QTableWidgetItem* sup = new QTableWidgetItem(QString::number(n.getSup()));
            QTableWidgetItem* tip = new QTableWidgetItem(QString::fromStdString(n.getTip()));
            tabel->insertRow(row);
            tabel->setItem(row, 0, ap);
            tabel->setItem(row, 1, nume);
            tabel->setItem(row, 2, sup);
            tabel->setItem(row, 3, tip);
            row++;

        }
    }
    void initGUI() {

        QHBoxLayout* lyMain = new QHBoxLayout{};
        this->setLayout(lyMain);
 
        //setStyleSheet("background-color:lightblue");

        auto lyBtns = new QFormLayout;



        lyBtns->addRow("Apartament", txtAp);
        lyBtns->addRow("Nume", txtNume);
        lyBtns->addRow("Suprafata", txtSup);
        lyBtns->addRow("Tip", txtTip);
        lyBtns->addRow("Poz", txtPoz);
        lyMain->addLayout(lyBtns);

        auto repo = new QHBoxLayout;
        repo->addWidget(btnAdauga);
        repo->addWidget(btnSterge);
        repo->addWidget(btnModifica);
        repo->addWidget(btnUndo);

        lyBtns->addRow(repo);

        auto sort = new QHBoxLayout;
        sort->addWidget(btnSortNum);
        sort->addWidget(btnSortSup);
        sort->addWidget(btnSortSupTip);

        auto filt = new QHBoxLayout;
        filt->addWidget(btnFiltSup);
        filt->addWidget(btnFiltTip);

        tabel->setColumnCount(4);
        tabel->setSelectionMode(QAbstractItemView::SingleSelection);
        tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
        QStringList headers;
        headers << "Apartament" << "Nume" << "Suprafata" << "Tip";
        tabel->setHorizontalHeaderLabels(headers);

        lyMain->addWidget(tabel);
        lyBtns->addRow(sort);
        lyBtns->addRow(filt);

        auto mainNot = new QHBoxLayout;
        mainNot->addWidget(btnAddNotMain);
        mainNot->addWidget(btnGolNotMain);
        mainNot->addWidget(btnGenNotMain);

        lyBtns->addRow(mainNot);

        //auto Notificari = new QFormLayout;

        //Notificari->addWidget(lstnot);

        //auto notificari = new QHBoxLayout;
        //notificari->addWidget(btnNot);
        //notificari->addWidget(btnGolNot);
        //notificari->addWidget(btnGenNot);
        //Notificari->addRow(notificari);

        //notificariWindow->setLayout(Notificari);

        auto cer = new QVBoxLayout;
        cer->addWidget(btnNrAp);
        cer->addWidget(btnNrGa);
        cer->addWidget(btnWindow);
        cer->addWidget(btnDesen);
        lyMain->addLayout(cer);
    }
};


