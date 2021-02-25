#include "conseleappneder.h"
#include "iostream"

ConseleAppneder::ConseleAppneder(){}

void ConseleAppneder::write(QString str){
   std::cout<<str.toStdString()<<std::endl;
}
