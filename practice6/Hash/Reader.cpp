#include "Reader.h"

Reader::Reader(){}

Reader::Reader(int ticket, string &f, string &a) : ticketNumber(ticket), fio(f), address(a) {}

int Reader::getTicketNumber() const {
    return ticketNumber;
}

void Reader::setTicketNumber(int ticketNumber) {
    this->ticketNumber = ticketNumber;
}

string Reader::getFio() {
    return fio;
}

void Reader::setFio(string fio) {
    this->fio = fio;
}

string Reader::getAddress() {
    return address;
}

void Reader::setAdress(string address) {
    this->address = address;
}


