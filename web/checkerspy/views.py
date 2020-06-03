"""version interface module. Return database version, database connecting strings and application build version"""

from checkerspy import checkers

game = checkers.Checkers.getInstance()

# initialize_fen = "8/4P3/8/4p3/5P2/2k5/1P6/8"
# initialize_fen = "8/4P3/8/3p4/3k1P2/8/1P6/8"
# initialize_fen = "1p5p/p7/3p1p2/8/3p4/4P3/8/2P1P1P1"
# initialize_fen = "8/8/5p2/2p5/1P1P1P2/8/8/8" # wygrana
# initialize_fen = "8/4k3/8/8/8/8/1K6/8" # remis
initialize_fen = "8/8/3P4/4p3/8/8/8/8"

def initialize(params):
    user_name = str(params['user_name'])
    is_user_white = True
    if (params['is_user_white'] == 'false'):
        is_user_white = False
    # game.initialize(user_name, is_user_white)
    game.fenInitialize(initialize_fen, user_name, is_user_white, True)

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
