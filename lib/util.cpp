#include "util.h"
unique_ptr<ExecutionEngine> Util::getExecuteEngine(unique_ptr<Module> module) {
    string error;
    EngineBuilder enginerBuilder(move(module));
    enginerBuilder.setErrorStr(&error);
    enginerBuilder.setEngineKind(EngineKind::JIT);
    unique_ptr<ExecutionEngine> ee(enginerBuilder.create());
    if (nullptr == ee) {
        outs() << error << "\n";
        return nullptr;
    }
    return ee;
}

void Util::insertFunctionIntoModule(Function *function,
                                    unique_ptr<Module> module) {
    function->removeFromParent();
    module->getFunctionList().push_front(function);
}

void Util::initTarget() {
    InitializeNativeTarget();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
}

void Util::linkFunctionLibs(string IRName) {
    outs() << "linking source file and libs file……\n    ";
    string command =
        "llvm-link " + IRName + " ../resources/functionLibs.ll -o " + IRName;
    system(command.c_str());
    outs() << "……linking is over\n\n";
}