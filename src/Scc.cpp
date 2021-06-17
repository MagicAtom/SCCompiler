#include "Scc.h"
#include <unistd.h>

void Scc::GetOpt(int argc,char** argv) {
    int opt;
    while((opt=getopt(argc,argv,"i:a:r:o:p"))!=-1){
        switch(opt){
            case 'a' : astFile_ = optarg; break; // AST tree
            case 'i' : inputFile_ = optarg; break; //
            case 'r' : irFile_ = optarg; break;
            case 'o' : objFile_ = optarg; break;
            case 'p' : std::cerr<<"[DEFAULT PROCESS START]"<<std::endl;break; // default process
            default:
                break;
        }
    }
    return;
}

void Scc::Exec(){
    scanner_ = new Scanner(inputFile_);
    parser_ = new Parser(scanner_->GetTS());
    parser_->Parse();
    // only objfile is supported now
    gen_ = new Generator(parser_->GetASTRoot());
    gen_->GenObjCode(objFile_);
    LOG_INFO("[PROCESS END]");
    return;
}