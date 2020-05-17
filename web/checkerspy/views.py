"""version interface module. Return database version, database connecting strings and application build version"""

from checkerspy import checkers

game = checkers.Checkers.getInstance()

def initialize(params):
    user_name = str(params['user_name'])
    is_user_white = True
    if (params['is_user_white'] == 'false'):
        is_user_white = False
    game.initialize(user_name, is_user_white)

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
        'fen': game_state.boardFEN
    }

def process_user_move(params):
    print(params['source'], params['destination'], type(params['source']))
    game_state = game.processUserMove(params['source'], params['destination'])
    return {
        'fen': game_state.boardFEN
    }

def make_computer_move(params):
    game_state = game.makeComputerMove()
    return {
        'fen' : game_state.boardFEN
    }
