"""version interface module. Return database version, database connecting strings and application build version"""

from checkerspy import checkers

game = checkers.Checkers.getInstance()
    
def findTile(params):
    pawn_id = str(params['pawn_id'])
    # input_key = str(params['input_key'])
    """the calculation from C++ library"""
    return {
        # "val" : checkers.findTile(pawn_id)
        'val' : game.findTile(pawn_id)
    }

def initialize(params):
    user_name = str(params['user_name'])
    user_color = True
    if (params['user_color'] == 'black'):
        user_color = False
    game.initialize(user_name, user_color)

def get_user_data(params):
    color = ""
    if game.getIsUserWhite() == True:
        color = "white"
    else:
        color = "black"

    return {
        'user_name': game.getUserName(),
        'user_color': color
    }