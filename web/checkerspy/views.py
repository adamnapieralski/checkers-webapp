"""version interface module. Return database version, database connecting strings and application build version"""

from checkerspy import checkers

game = checkers.Checkers.getInstance()

# initialize_fen = "8/4P3/8/4p3/5P2/2k5/1P6/8"
# initialize_fen = "8/4P3/8/3p4/3k1P2/8/1P6/8"

def initialize(params):
    user_name = str(params['user_name'])
    is_user_white = True
    if (params['is_user_white'] == 'false'):
        is_user_white = False
    game.initialize(user_name, is_user_white)
    # game.fenInitialize(initialize_fen, user_name, is_user_white, True)

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

def get_game_state(params):
    game_state = game.getGameState()
    return {
        'fen': game_state.boardFEN,
        'isUserTurn' : game_state.isUserTurn,
        'isInMultipleMove' : game_state.isInMultipleMove,
    }

def process_user_move(params):
    game_state = game.processUserMove(params['source'], params['destination'])
    return {
        'fen': game_state.boardFEN,
        'isUserTurn' : game_state.isUserTurn,
        'isInMultipleMove' : game_state.isInMultipleMove,
    }

def make_computer_move(params):
    game_state = game.makeComputerMove()
    return {
        'fen' : game_state.boardFEN,
        'isUserTurn' : game_state.isUserTurn,
        'isInMultipleMove' : game_state.isInMultipleMove,
    }
