"""version interface module. Return database version, database connecting strings and application build version"""

import checkers
    
def findTile(params):
    pawn_id = str(params['pawn_id'])
    # input_key = str(params['input_key'])
    """the calculation from C++ library"""

    return {
        "val" : checkers.findTile(pawn_id)
    }