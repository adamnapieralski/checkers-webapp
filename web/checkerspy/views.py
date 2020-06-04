"""version interface module. Return database version, database connecting strings and application build version"""

from checkerspy import checkers

game = checkers.Checkers.getInstance()

def initialize(params):
    user_name = str(params['user_name'])
    is_user_white = True
    if (params['is_user_white'] == 'false'):
        is_user_white = False
    game.initialize(user_name, is_user_white)

def get_game_state(params):
    game_state = game.getGameState()
    return make_game_state_obj(game_state)

def process_user_move(params):
    game_state = game.processUserMove(params['source'], params['destination'])
    return make_game_state_obj(game_state)

def make_computer_move(params):
    game_state = game.makeComputerMove()
    return make_game_state_obj(game_state)

def make_game_state_obj(game_state):
    return {
        'userName' : game_state.userName,
        'isUserWhite' : game_state.isUserWhite,
        'fen': game_state.boardFEN,
        'isUserTurn' : game_state.isUserTurn,
        'isInMultipleMove' : game_state.isInMultipleMove,
        'uAP' : game_state.uAP, 
	    'cAP' : game_state.cAP, 
	    'uAK' : game_state.uAK,
	    'cAK' : game_state.cAK,
	    'isEnd' : game_state.hasGameEnded,
        'score' : game_state.score,
    }
