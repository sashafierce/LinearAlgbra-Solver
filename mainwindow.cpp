#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_solveButton_clicked()
{
    QVector< QVector<double> > matrixA;
    int n = 0;
    int f = 1;
    int k = 0;
    int r = 0;
    foreach (QString row, ui->aMatrix->toPlainText().split("\n")) {
        QVector<double> col;

        k = 0 ;
        foreach (QString val , row.split(" ")) {

            bool check = false;
            double colValue = val.toDouble(&check);
            //qDebug() << "val = " << val <<" check = "<< check ;

            if(check){
                col.push_back(colValue) ;
                 k++ ;
            }
            else if(val != " " && val != "" ) {
                f = 0;
               // qDebug() << "check false ";
                break ;
            }
        }

        if(n == 0 )
            n = k;
        else if( n != k && k != 0) {            // checking no. of col elements
            f = 0 ;
            qDebug() << "n!=k "<<k;

            break ;
        }
        if(!col.isEmpty()) {
            matrixA.push_back(col) ;
            r++;
         }
        if(f == 0) {
            break;
        }

    }
    if(r != n )
        f = 0;
    if(f == 1) {
        int b = 0;

        QVector<double> vectorB;
        foreach (QString val, ui->bVector->toPlainText().split("\n")) {
            bool check = false;

            double colValue = val.toDouble(&check);
           // qDebug() << "val = " << val <<" check = "<< check ;
            if(check){
                vectorB.push_back(colValue );
                b++;
             }
            else if(val != ""){

                f = 0;
                break;
            }

        }
       // qDebug() << "b = " <<b ;
        if(n != b ) {
            f = 0;
        }
        if(f == 1) {

            QVector< QVector< double > > l(n+1) , u(n+1);
            for(int k = 1; k <= n ; k++) {
                 u[k].resize(n+1);
                 l[k].resize(1+n);
             }
            double sum = 0.0 ;
            for(int k = 1; k <=n ; k++)
            {

                    u[k][k] = 1 ;
                    for(int i = k ; i <= n ; i++)
                    {
                        sum =  0.0 ;
                        for(int p = 1 ; p <= k - 1 ; p++)
                            sum += l[i][p] * u[p][k] ;
                        l[i][k] = matrixA[i-1][k-1] - sum ;
                    }

                    for(int j = k + 1 ; j <= n ; j++)
                    {
                        sum = 0;
                        for(int p = 1 ; p <= k - 1 ; p++)
                            sum += l[k][p] * u[p][j] ;
                        u[k][j] = (matrixA[k-1][j-1] - sum) / l[k][k] ;
                    }
              }

            QVector< double > z(n+1) , x(n+1);

               for(int i = 1 ; i <= n ; i++)
               {                                        //forward subtitution method
                   sum = 0.0;
                   for(int p = 1 ; p < i ; p++)
                        sum += l[i][p] * z[p];
                   z[i] = (vectorB[i-1]-sum) / l[i][i];
               }

               for(int i=n;i>0;i--)
               {
                   sum=0.0;
                   for(int p = n ; p > i ; p--)
                       sum += u[i][p] * x[p];
                   x[i] = (z[i] - sum) / u[i][i];
                  // if(x[i] == ceil(x[i]))
               }

              qDebug() << "Set of solution";
               for(int i=1;i<=n;i++) {

                   qDebug() << x[i];
//                   if(x[i] == INFINITY || x[i] == NAN ) {
//                       ui->xResult->setText("A is not invertible matrix.");
//                       f = 0 ;
//                        break;
//                   }

                }
               if(f == 1) {

                   QString str;
                   for (int i = 1; i < x.size(); ++i)
                   {
                       str += QString::number(x[i]);
                       str += "\n";
                   }
                   ui->errorText->setText("Solution Found.");
                   ui->xResult->setText(str);

               }

        }
        else {

            QString str;
            str += "Invalid B vector.\nEnter an Nx1 vector and follow input format properly.\n";
            ui->errorText->setText(str);
            ui->xResult->setText("");

        }

     }
    else {
        // ui->errorText->setTextColor(red);
          QString str;
          str += "Invalid A matrix.\nEnter a square matrix and follow input format properly.\n";
          ui->errorText->setText(str);
          ui->xResult->setText("");


    }
}
