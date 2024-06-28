from src.semantic.type_finder_visitor import type_finder
from src.semantic.type_filler_visitor import type_filler
from src.semantic.var_finder_visitor import var_finder
from termcolor import colored

def semantic_check(ast,verbose=False):
    errors=[]
    warnings=[]
    type_collector = type_finder(errors)
    context,errors=type_collector.visit(ast)

    var_collector=var_finder(context,errors,warnings)
    scope=var_collector.visit(ast)
    if verbose:print(colored(scope,'yellow'))

    type_fill = type_filler(context, errors)
    context,errors=type_fill.visit(ast)


    if verbose:print(context)

    for warning in warnings:
        print(warning)
    if errors:
        for error in errors:
            print(error)
        return False
    
    if verbose:print("NO SEMANTIC ERRORS FOUND")
    return True

