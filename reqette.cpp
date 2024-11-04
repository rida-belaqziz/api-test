#include <QCoreApplication>
#include <QHttpServer>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonArray>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QJsonDocument>



//__________________________________________
//Requete 0



QJsonObject getVilles()
{

    QJsonArray tab;

    QSqlDatabase db = QSqlDatabase::database("REP");
    QSqlQuery query("SELECT * from Villes" , db);

    while (query.next())
    {
        //int nbCols = query.record().count();
        QJsonObject o;


        o["id"] = query.value(0).toInt();
        o["nomAbrige"] = query.value(2).toString();
        o["nomVille"] = query.value(1).toString();



        tab.append(o);
    }
    //QJsonDocument d(o);






    return QJsonObject{
        {
            "Villes", tab
        }
};
}




/*QJsonObject getVilles()
{
    return QJsonObject{
        {
            {"id", "1"},
            {"nomAbrige", "PAR"},
            {"nomVille", "Paris"}
        }
   };
}*/



//__________________________________________
//Requete 1

QJsonObject getVols()
{

    QJsonArray tab;

    QSqlDatabase db = QSqlDatabase::database("REP");
    //QSqlQuery query("SELECT * from Vols" , db);
    QSqlQuery query("SELECT * from vols_disponibles" , db);

    while (query.next())
    {
        //int nbCols = query.record().count();
        QJsonObject o;
        //for(int i = 1; i<nbCols;i++){

            o["Arrivee"] = query.value(3).toString();
            o["Depart"] = query.value(2).toString();
            o["Nom"] = query.value(1).toString();
            o["dateArrive"] = query.value(4).toString();
            o["dateDepart"] = query.value(5).toString();
            o["heureArrive"] = query.value(7).toString();
            o["heureDepart"] = query.value(6).toString();


        //}

        tab.append(o);
    }
    //QJsonDocument d(o);






    return QJsonObject{
        {
            "Vols", tab
        }
};
}

//__________________________________________
//Requete 2
QJsonObject getListeSiege(qint32 idVol)
{

    QJsonArray tab0;
    QJsonArray tab1;
    QJsonArray tab2;

    QSqlDatabase db = QSqlDatabase::database("REP");


    QSqlQuery query("SELECT * FROM liste_seige " , db);






    while (query.next())
    {
      if (idVol == query.value(0).toInt() ){
        QJsonObject o;

        o["Nom"] = query.value(10).toString();
        o["nbColonne"] = query.value(12).toInt();
        o["nbLigne"] = query.value(11).toInt();


        tab0.append(o);


        QJsonObject o1;

        o1["Arrivee"] = query.value(14).toString();
        o1["Depart"] = query.value(13).toString();
        o1["Nom"] = query.value(10).toString();
        o1["dateArrive"] = query.value(6).toString();
        o1["dateDepart"] = query.value(7).toString();
        o1["heureArrive"] = query.value(8).toString();
        o1["heureDepart"] = query.value(9).toString();

        tab1.append(o1);



        QJsonObject o2;
        o2["Nom"] = query.value(4).toString();
        o2["Prenom"] = query.value(5).toString();
        o2["UUID"] = query.value(2).toString();
        o2["idSiege"] = query.value(1).toString();
        tab2.append(o2);
        }
    }


    return QJsonObject{
        {
            "Avion", tab0
        },
        {
            "Liste", tab2
        },
        {
            "Vols", tab1
        }
};
}


//__________________________________________
//Requete 3
QJsonObject getPassager(qint32 id)
{

    QJsonArray tab;

    QSqlDatabase db = QSqlDatabase::database("REP");
    QSqlQuery query("SELECT * from Passasers" , db);
    qint32 i=0;
    while (query.next())
    {
        //int nbCols = query.record().count();
        QJsonObject o;
        if (id == query.value(0).toInt() ){

        o["id"] = query.value(0).toInt();
        o["Nom"] = query.value(1).toString();
        o["Prenom"] = query.value(2).toString();
        o["Email"] = query.value(4).toString();
        o["Telephone"] = query.value(3).toString();



        tab.append(o);}
        else i++;
    }







    return QJsonObject{
        {
            "data", tab
        }
};
}




//__________________________________________
//Requete 4
/*void addPassager(QString nom, QString prenom, QString telephone, QString email)
{


    QSqlDatabase db = QSqlDatabase::database("REP");
    //QSqlQuery query("SELECT * from Passasers" , db);
    QSqlQuery query;
    query.prepare("insert into Passasers values(?, ?, ?, ?)");
    query.addBindValue(nom);
    query.addBindValue(prenom);
    query.addBindValue(telephone);
    query.addBindValue(email);
    query.exec();


}*/



//__________________________________________
//Requete 4
void addPassager(QJsonObject o)
{


    QSqlDatabase db = QSqlDatabase::database("REP");
    //QSqlQuery query("SELECT * from Passasers" , db);
    QSqlQuery query;
    query.prepare("insert into Passasers values(?, ?, ?, ?)");
    query.addBindValue(o["Nom"].toString());
    query.addBindValue(o["Prenom"].toString());
    query.addBindValue(o["Telephone"].toString());
    query.addBindValue(o["Email"].toString());
    query.exec();


}




//__________________________________________
//Requete 4-1
void updatePassager(QJsonObject o)  //void updatePassager(qint32 id, QString val)
{


    QSqlDatabase db = QSqlDatabase::database("REP");
    QSqlQuery query0("SELECT * from Passasers" , db);
    QSqlQuery query;
    int i=0;
    while (query0.next())
    {
        //int nbCols = query.record().count();
        //QJsonObject o;
        if (o["id"].toInt() == query0.value(0).toInt() ){

            //query.prepare("UPDATE Passasers SET Numero='+33586958604'");
            query.prepare("UPDATE Passasers SET Numero= ? ");
            query.addBindValue(o["Numero"].toString());
            query.exec();}
        else i++;
    }



}



//__________________________________________
//Requete 5
void addReservation(QJsonObject o) //void addReservation(qint32 idPassager, QString idSiege, qint32 idVol, qint32 numBillet)
{




    QSqlDatabase db = QSqlDatabase::database("REP");
    //QSqlQuery query("SELECT * from Passasers" , db);
    QSqlQuery query;
    query.prepare("insert into Reservation values(?, ?, ?, ?, ?)");
    query.addBindValue(o["idPassager"].toInt());
    query.addBindValue(o["idVol"].toInt());
    query.addBindValue(o["idSiege"].toInt());
    query.addBindValue(o["numBillet"].toInt());
    query.addBindValue(o["UUID"].toString());
    query.exec();


}


//__________________________________________
//Requete 6
QJsonObject getReservation(QString UUID)
{

    QJsonArray tab0;
    QJsonArray tab1;
    QJsonArray tab2;

    QSqlDatabase db = QSqlDatabase::database("REP");


    QSqlQuery query("SELECT * FROM liste_seige " , db);


    query.first();



    qint32 i=0;
    while (query.next())
    {
      if (UUID == query.value(2).toString() ){

        QJsonObject o;
        o["idSiege"] = query.value(1).toString();
        o["idVol"] = query.value(0).toInt();
        o["numBillet"] = query.value(2).toInt();



        tab0.append(o);


        QJsonObject o1;

        o1["Arrivee"] = query.value(14).toString();
        o1["Depart"] = query.value(13).toString();
        o1["Nom"] = query.value(10).toString();
        o1["dateArrive"] = query.value(6).toString();
        o1["dateDepart"] = query.value(7).toString();
        o1["heureArrive"] = query.value(8).toString();
        o1["heureDepart"] = query.value(9).toString();
        o1["UUID"] = query.value(2).toString();

        tab1.append(o1);



        QJsonObject o2;
        o2["Nom"] = query.value(4).toString();
        o2["Prenom"] = query.value(5).toString();


        tab2.append(o2);}

        else i++;
    }


    return QJsonObject{
        {
            "Vols", tab1
        },
        {
            "Passager", tab2
        },
        {
            "Liste", tab0
        }
};
}



//__________________________________________
//Requete 7


void updateReservation(QJsonObject o) //void updateReservation(QString Nom, QString Prenom,QString col, QString modif)
{

    QSqlDatabase db = QSqlDatabase::database("REP");
    QSqlQuery query0("SELECT * from udReservation" , db);
    QSqlQuery query;
    qint32 i=0;
    while (query0.next())
    {
        //int nbCols = query.record().count();
        //QJsonObject o;
        if (o["Nom"].toString() == query0.value(7).toString() && o["Prenom"].toString() == query0.value(8).toString()){


            if (o["UUID"].toString() != query0.value(5).toString()){
            query.prepare("UPDATE udReservation SET UUID= ? ");
            query.addBindValue(o["UUID"].toString());
            query.exec();}

            if (o["idVol"].toInt() != query0.value(2).toInt()){
            query.prepare("UPDATE udReservation SET idVol= ? ");
            query.addBindValue(o["idVol"].toInt());
            query.exec();}

            if (o["idSiege"].toString() == query0.value(3).toString()){
            query.prepare("UPDATE udReservation SET idSiege= ? ");
            query.addBindValue(o["idSiege"].toString());
            query.exec();}

            if (o["numBillet"].toInt() == query0.value(4).toInt()){
            query.prepare("UPDATE udReservation SET numBillet= ? ");
            query.addBindValue(o["numBillet"].toString());
            query.exec();}


            }
        else i++;
    }



}




//__________________________________________
//Requete 8
void DeleteReservation( QString UUID)
{



    QSqlDatabase db = QSqlDatabase::database("REP");

    QSqlQuery query;

    query.prepare("DELETE FROM Reservation WHERE UUID = ? ");
    query.addBindValue(UUID);
    query.exec();




}











//*************************************************************
//               MAIN
//*************************************************************

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



//*************************************************************

    //Affichage (Vérification)
    //qDebug() <<  getVilles();
    //qDebug() <<  getListeSiege();
    //qDebug() << getPassager(2);


    QHttpServer server;

    QString sFile = "/Users/ridabelaqziz/Desktop/Ausy/Formation/Projet SOUTENANCE/Ma Partie/passagers1.db";

    if (QFile::exists(sFile))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","REP");
        db.setDatabaseName(sFile);

    }

//*************************************************************
    //Requete 0
    server.route("/Villes", [] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return getVilles();
        }


    });


//*************************************************************
    //Requete 1
    server.route("/Vols", [] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return getVols();
        }


    });

//*************************************************************

     //Requete 2
    server.route("/ListeSiege", [] (qint32 id ,const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return getListeSiege(id);
        }


    });


//*************************************************************


    //Requete 3
   server.route("/Passager", [] (qint32 id, const QHttpServerRequest &request) {
       if (request.method() == QHttpServerRequest::Method::GET)
       {
           return getPassager(id);
       }

   });


//*************************************************************


   //Requete 4
  server.route("/Passager", [] (QJsonObject rootObj, const QHttpServerRequest &request) {
      if (request.method() == QHttpServerRequest::Method::POST)
      {
          QJsonDocument d = QJsonDocument::fromJson(request.body());
          rootObj = d.object();
          addPassager(rootObj);
      }


  });



//*************************************************************

  //Requete 4-1
 server.route("/Passager", [] (QJsonObject rootObj, const QHttpServerRequest &request) {
     if (request.method() == QHttpServerRequest::Method::PUT)
     {
         QJsonDocument d = QJsonDocument::fromJson(request.body());
         rootObj = d.object();
         updatePassager(rootObj);
     }


 });



//*************************************************************

 //Requete 5
 server.route("/Reservation", [] (QJsonObject rootObj, const QHttpServerRequest &request) {
    if (request.method() == QHttpServerRequest::Method::POST)
    {
        QJsonDocument d = QJsonDocument::fromJson(request.body());
        rootObj = d.object();
        addReservation(rootObj);
    }


});


//*************************************************************
 //Requete 6
 server.route("/Reservation", [] (QString UUID ,const QHttpServerRequest &request) {
    if (request.method() == QHttpServerRequest::Method::GET)
    {
        return getReservation(UUID);
    }


});



//*************************************************************

 //Requete 7
 server.route("/Reservation", [] (QJsonObject rootObj, const QHttpServerRequest &request) {
    if (request.method() == QHttpServerRequest::Method::PUT)
    {
        QJsonDocument d = QJsonDocument::fromJson(request.body());
        rootObj = d.object();
        updateReservation(rootObj);
    }


});


//*************************************************************


 //Requete 8
 server.route("/Delete", [] (QString UUID, const QHttpServerRequest &request) {
    if (request.method() == QHttpServerRequest::Method::GET)
    {
        return DeleteReservation(UUID);
    }

});


//*************************************************************



    server.listen(QHostAddress::Any,8585);

    return a.exec();
}