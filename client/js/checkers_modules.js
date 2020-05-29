angular.module('Checkers', ['myAppControllers', 'myAppServices'] );

var myAppControllers = angular.module('myAppControllers', []);

myAppControllers.controller('entryController',
	['$scope', 'srvInfo',
		function($scope, srvInfo) {
			$scope.loadGame = function(data) {
				if (document.getElementById('userNameText').value == "") {
					document.getElementById('userNameText').placeholder = "Podaj nazwę gracza!";
					document.getElementById('userNameText').style.borderColor = 'red';
				}
				else {
					userData = {
						"name" : document.getElementById('userNameText').value,
						"isWhite" : !document.getElementById('userColorSwitch').checked,
					}
					srvInfo.initializeGame(userData);
					window.location = "/play";
				}
			};
}]);

myAppControllers.controller('gameController',
	['$scope', 'srvInfo', '$timeout', '$window',
		function ($scope, srvInfo, $timeout, $window) {
		
		$scope.scoreStates = ["IN_PROGRESS", "USER_WON", "USER_LOST", "DRAW"];
		$scope.gameData = {
			userName : "name",
			isUserWhite : true,
			userColorString : "biały",
			compColorString : "czarny",
			fen : "",
			isUserTurn : true,
			turnOwnerName: "gracza",
			isInMultipleMove : false,
			uAP : 12,
			cAP : 12,
			uAK : 0,
			cAK : 0,
		 	isEnded : false,
			score : $scope.scoreStates[0],
			endText : "",
		};

		$scope.updateGameData = function(data) {
			$scope.gameData.userName = data.data.userName;
			$scope.gameData.isUserWhite = data.data.isUserWhite;
			$scope.gameData.fen = data.data.fen;
			$scope.gameData.isUserTurn = data.data.isUserTurn;
			$scope.gameData.isInMultipleMove = data.data.isInMultipleMove;
			$scope.gameData.uAP = data.data.uAP;
			$scope.gameData.cAP = data.data.cAP;
			$scope.gameData.uAK = data.data.uAK;
			$scope.gameData.cAK = data.data.cAK;
			$scope.gameData.isEnded = data.data.isEnd;
			$scope.gameData.score = $scope.scoreStates[data.data.score];

			$scope.boardConfig.position = $scope.gameData.fen;
			$scope.board = Chessboard('board', $scope.boardConfig);

			$scope.checkIfFinished();
			if ($scope.gameData.isUserTurn) {
				$scope.gameData.turnOwnerName = "gracza";
			}
			else {
				$scope.gameData.turnOwnerName = "komputera";
			}
			console.log($scope.gameData.isEnded);
		};

		angular.element(function() {
			$scope.boardConfig.draggable = true;
			$scope.gameData.isEnded = false;
			$scope.turnOwnerName = "gracza";
			$scope.loadBoard();
			if (!$scope.isUserTurn) {
				$scope.turnOwnerName = "komputera";
				$timeout(function() {
					$scope.makeComputerMove();
				}, 1200)
			}
		});

		$scope.reloadPage = function() {
			let isWhite = true;
			if ($scope.userColor == "black") isWhite = false;
			let userData = {
				"name" : $scope.userName,
				"isWhite" : isWhite,
			}
			srvInfo.initializeGame(userData);
			$window.location.reload();
		};
		
		$scope.onPieceDrop = function(source, target) {
			move = { 'source' : source, 'destination' : target }

			srvInfo.processUserMove(move,
				function(data) {
					$scope.updateGameData(data);
				}
			)
			$scope.$digest();
			if (!$scope.isInMultipleMove) {
				$timeout(function() {
					$scope.makeComputerMove();
				}, 1200)
			}
		}

		$scope.boardConfig = {
			draggable: true,
			dropOffBoard: 'snapback',
			onDrop: $scope.onPieceDrop,
		};

		$scope.board = Chessboard('board', $scope.boardConfig);

		$scope.loadBoard = function() {
			srvInfo.getGameState (
				function(data) {
					$scope.updateGameData(data);
				}
			)
		}

		$scope.makeComputerMove = function() {
			srvInfo.makeComputerMove(
				function(data) {
					$scope.updateGameData(data);
				}
			)
			$scope.$digest();
		}

		$scope.checkIfFinished = function() {
			if ($scope.gameData.isEnded && $scope.gameData.score != "IN_PROGRESS") {
				// $scope.gameData.isEnded = false;
				$scope.boardConfig.draggable = false;
				$scope.board = Chessboard('board', $scope.boardConfig);
				let confirmText = "";
				let isConfirmed = false;
				switch ($scope.gameData.score) {
				case "USER_WON":
					$scope.gameData.endText = "Wygrana! Gratulacje!"
					break;
				case "USER_LOST":
					$scope.gameData.endText = "Przegrana. Następnym razem pójdzie lepiej!"
					break;
				case "DRAW":
					$scope.gameData.endText = "Remis! To była zacięta gra!"
					break;
				}
			}
		}

		$scope.playAgain = function() {
			window.location = "/entry";
		}
}]);
	

// communication with the server
angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {

				 this.initializeGame = function(data) {
					return $http.get('/ajax/checkerspy/initialize/?user_name='
					+ data.name + '&is_user_white='
					+ data.isWhite); 
				 };
				 this.getGameState = function(callback) {
					return $http.get('/ajax/checkerspy/get_game_state/').then(callback); 
				 };
				 this.processUserMove = function(data, callback) {
					return $http.get('/ajax/checkerspy/process_user_move/?source='
					+ data.source + '&destination=' + data.destination).then(callback); 
				 };
				 this.makeComputerMove = function(callback) {
					return $http.get('/ajax/checkerspy/make_computer_move/').then(callback); 
				 };

             });


