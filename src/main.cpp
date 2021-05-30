#include "Scc.h"

int main(int argc,char* argv[]){
    Scc* scc_ = new Scc();
    scc_->GetOpt(argc,argv);
    scc_->Exec();
}