// DNI 74011239E LLINARES MAURI, JUAN
#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <string>

using namespace std;

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE
};

class Util{
  public:
    static void error(Error e);
    static bool checkEmpty(string s);
    static void saveDate(string deadline,int &day,int &month,int &year);
    static int KMINMONTH();
    static int KMAXMONTH();
    static int KMAXFEB();
    static int KMAXDAY2();
    static int KMAXDAY();
    static int KMINYEAR();
    static int KMAXYEAR();
    static int KMAXNAME();
    static int KMAXDESC();
    static void E_PN();
    static void E_PD();
    static void E_LN();
    static void E_TN();
    static void E_D();
    static void E_DD();
    static void E_ET();
    static string N();
    static string D();
    static string TL();
    static string TD();
    static string MIN();
    static string HP();
    static string E_ID();
    static string E_FN();
    static string CONF();
    static string SAP();
};

#endif
