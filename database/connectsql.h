#ifndef CONNECTSQL_H
#define CONNECTSQL_H


class ConnectSQL
{
public:
    ConnectSQL();
    bool connectMYSQL();
    bool connectSQLite();
    void closeConnection();

};

#endif // CONNECTSQL_H
