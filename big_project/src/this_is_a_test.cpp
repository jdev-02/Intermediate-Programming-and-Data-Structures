#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"

int main() {
    Stock_info s;

    Security jpm  = Security("JPM");   // JPMorgan Chase
    Security bac  = Security("BAC");   // Bank of America
    Security unh  = Security("UNH");   // UnitedHealth Group
    Security vz   = Security("VZ");    // Verizon
    Security ko   = Security("KO");    // Coca-Cola
    Security pep  = Security("PEP");   // PepsiCo
    Security mcd  = Security("MCD");   // McDonald's
    Security wmt  = Security("WMT");   // Walmart
    Security hd   = Security("HD");    // Home Depot
    Security pg   = Security("PG");    // Procter & Gamble
    Security dis  = Security("DIS");   // Walt Disney
    Security nke  = Security("NKE");   // Nike
    Security abbv = Security("ABBV");  // AbbVie

    // Print each security
    jpm.print();
    bac.print();
    unh.print();
    vz.print();
    ko.print();
    pep.print();
    mcd.print();
    wmt.print();
    hd.print();
    pg.print();
    dis.print();
    nke.print();
    abbv.print();


    // Print the cache at the end
    s.printCache();

    return 0;
}
