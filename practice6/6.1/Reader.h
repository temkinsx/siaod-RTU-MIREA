#ifndef READER_H
#define READER_H
#include <string>
using namespace std;


class Reader {
    int ticketNumber;
    string fio;
    string address;

public:
    Reader();

    Reader(int ticket, string &f, string &a);

    int getTicketNumber() const;

    void setTicketNumber(int ticketNumber);

    string getFio();

    void setFio(string fio);

    string getAddress();

    void setAdress(string adress);
};


#endif //READER_H
