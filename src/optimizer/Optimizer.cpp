#include "Optimizer.h"

#include "llvm/Passes/PassBuilder.h"

#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Scalar/Reassociate.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
#include "llvm/Transforms/Utils/Mem2Reg.h"

#include "loguru.hpp"
//BEST RESOURE IS the llvm-project/llvm/lib/Passes/PassBuilderPipelines.cpp

//  Minimal optimization pass using LLVM pass managers
void Optimizer::optimize(llvm::Module *theModule) {
  LOG_S(1) << "Optimizing program " << theModule->getName().str();

  // New pass builder
  llvm::PassBuilder passBuilder;

  // Setting-up Analysis Managers for different granularities of optimizations
  llvm::FunctionAnalysisManager functionAnalysisManager;    // most people add some function analyses
  llvm::ModuleAnalysisManager moduleAnalysisManager;        // if brave, some people add this
  llvm::LoopAnalysisManager loopAnalysisManager;            // definitely have some of these            
  llvm::CGSCCAnalysisManager cgsccAnalysisManager;

  // Registering the analysis managers with the pass builder
  passBuilder.registerModuleAnalyses(moduleAnalysisManager);
  passBuilder.registerCGSCCAnalyses(cgsccAnalysisManager);
  passBuilder.registerFunctionAnalyses(functionAnalysisManager);
  passBuilder.registerLoopAnalyses(loopAnalysisManager);

  // Cross Register Proxies so that analysis results can be reused as needed.
  passBuilder.crossRegisterProxies(loopAnalysisManager, functionAnalysisManager,
                                   cgsccAnalysisManager, moduleAnalysisManager);

  // Initiating Function and Module level PassManagers
  llvm::ModulePassManager modulePassManager;
  llvm::FunctionPassManager functionPassManager;
  // figure out how to add things to each pass manager, can also have function pass managers
  // overall, keep this boilerplate code
  // i think wed need to add a loop manager
  // he added a loop manager and a loop manager w ssa
  // use time as a metric
  // ablation study, only need to do one at a time, no need to test combinations.

  // Adding passes to the pipeline

  // Loop invariant code modtion pass for ssa loop manager
  // loop deletion pass

  // Constructs SSA and is a pre-requisite for many other passes
  functionPassManager.addPass(llvm::PromotePass());  // determines if you need memory for this thing or not, ie alloca into a register
  // this one is needed, others wont work without this one

  // Instruction combine pass scans for a variety of patterns and replaces bitcodes matched with improvements.
  functionPassManager.addPass(llvm::InstCombinePass());
  // a lot of things in this one, 25k lines

  // Reassociate expressions.
  functionPassManager.addPass(llvm::ReassociatePass());
  //takes exprs and puts them in pesudocanonical form. ie add op register comes first number second, either or works

  // Eliminate Common SubExpressions using the Global Value Numbering (GVN) algorithm.
  functionPassManager.addPass(llvm::GVNPass());
  //whether an expression has been computed multiple times

  // Simplify the control flow graph (deleting unreachable blocks, etc).
  functionPassManager.addPass(llvm::SimplifyCFGPass());
  //ie if in a conditional statement, you might determine the condition is always true, so simplify this, so off branhces gone.
  // Passing the function pass manager to the modulePassManager using a function
  // adaptor, then passing theModule to the ModulePassManager along with
  // ModuleAnalysisManager.
  modulePassManager.addPass(
      createModuleToFunctionPassAdaptor(std::move(functionPassManager)));
  modulePassManager.run(*theModule, moduleAnalysisManager);

  // module pass optim module inliner pass
}
