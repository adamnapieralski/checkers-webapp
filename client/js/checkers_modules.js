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
			isInMultipleMove : false,
			uAP : 12,
			cAP : 12,
			uAK : 0,
			cAK : 0,
		 	isFinished : false,
			score : $scope.scoreStates[0],
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
			$scope.gameData.isFinished = data.data.isEnd;
			$scope.gameData.score = $scope.scoreStates[data.data.score];

			$scope.boardConfig.position = $scope.gameData.fen;
			$scope.board = Chessboard('board', $scope.boardConfig);
			// console.log("user turn");
			// console.log($scope.gameData.isUserTurn)
			// console.log($scope.gameData.isFinished)
			// console.log($scope.gameData.score)

			$scope.checkIfFinished();
		};

		angular.element(function() {
			$scope.boardConfig.draggable = true;
			$scope.gameData.isFinished = false;
			$scope.turnOwnerName = "gracza";
			// $scope.ifEnd = false; //moze apply?
			$scope.loadBoard();
			// $scope.printUserData();
			if (!$scope.isUserTurn) {
				// $scope.turn = 'komputera';
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
			// $scope.turn = 'gracza';

			move = { 'source' : source, 'destination' : target }

			srvInfo.processUserMove(move,
				function(data) {
					$scope.updateGameData(data);
					// console.log($scope.gameData.fen)
					// $scope.currentFEN = data.data.fen;
					// $scope.isUserTurn = data.data.isUserTurn
					// $scope.isInMultipleMove = data.data.isInMultipleMove
					// $scope.boardConfig.position = $scope.currentFEN;
					// $scope.board = Chessboard('board', $scope.boardConfig);
					// $scope.uAP = data.data.uAP;
					// $scope.cAP = data.data.cAP;
					// $scope.uAK = data.data.uAK;
					// $scope.cAK = data.data.cAK;
					// $scope.ifEnd = data.data.isEnd;
				}
			)
			$scope.$digest();
			if (!$scope.isInMultipleMove) {
				$scope.turn = 'komputera';
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

		// $scope.printUserData = function() {
		// 	console.log("Printing user data");
		// 	srvInfo.getUserData(
		// 		function(data) {
		// 			$scope.userName = data.data.user_name;
		// 			$scope.userColor = data.data.user_color;
		// 			document.getElementById('userNameView').textContent = data.data.user_name;
		// 			document.getElementById('userColorView').textContent = data.data.user_color;
		// 			$scope.compColorView = data.data.comp_name;
		// 		}
		// 	)
		// }

		$scope.loadBoard = function() {
			$scope.gameData.isFinished = false;
			srvInfo.getGameState (
				function(data) {
					$scope.updateGameData(data);
					// $scope.gameData.fen = data.data.fen;
					// $scope.gameData.isUserTurn = data.data.isUserTurn;
					// $scope.gameData.isInMultipleMove = data.data.isInMultipleMove;
					// $scope.gameData.uAP = data.data.uAP;
					// $scope.gameData.cAP = data.data.cAP;
					// $scope.gameData.uAK = data.data.uAK;
					// $scope.gameData.cAK = data.data.cAK;
					// $scope.isFinished = data.data.isEnd;


					// $scope.boardConfig.position = $scope.currentFEN;
					// $scope.board = Chessboard('board', $scope.boardConfig);



					// $scope.currentFEN = data.data.fen;
					// $scope.isUserTurn = data.data.isUserTurn
					// $scope.isInMultipleMove = data.data.isInMultipleMove
					// $scope.boardConfig.position = $scope.currentFEN;
					// $scope.board = Chessboard('board', $scope.boardConfig);
					// $scope.uAP = data.data.uAP;
					// $scope.cAP = data.data.cAP;
					// $scope.uAK = data.data.uAK;
					// $scope.cAK = data.data.cAK;
					// $scope.ifEnd = data.data.isEnd;

					/*$scope.$apply(function(){
						$scope.ifEnd = data.data.isEnd;
					});*/
				}
			)
			// if($scope.isUserTurn){
			// 	$scope.turn = 'gracza';
			// }
			// else{
			// 	$scope.turn = 'komputera';
			// }
		}

		$scope.makeComputerMove = function() {
			// if($scope.isUserTurn){
			// 	$scope.turn = 'gracza';
			// }
			// else{
			// 	$scope.turn = 'komputera';
			// }
			srvInfo.makeComputerMove(
				function(data) {
					$scope.updateGameData(data);
					// $scope.currentFEN = data.data.fen;
					// $scope.boardConfig.position = $scope.currentFEN;
					// $scope.board = Chessboard('board', $scope.boardConfig);
					// $scope.uAP = data.data.uAP;
					// $scope.cAP = data.data.cAP;
					// $scope.uAK = data.data.uAK;
					// $scope.cAK = data.data.cAK;
					// $scope.ifEnd = data.data.isEnd;

				}
			)
			$scope.$digest();
			// $scope.turn = 'gracza';
			// $scope.$digest();
		}

		$scope.checkIfFinished = function() {
			if ($scope.gameData.isFinished && $scope.gameData.score != "IN_PROGRESS") {
				$scope.gameData.isFinished = false;
				$scope.boardConfig.draggable = false;
				$scope.board = Chessboard('board', $scope.boardConfig);
				let confirmText = "";
				let isConfirmed = false;
				switch ($scope.gameData.score) {
				case "USER_WON":
					confirmText = "Wygrana! Gratulacje!"
					break;
				case "USER_LOST":
					confirmText = "Przegrana. Następnym razem pójdzie lepiej!"
					break;
				case "DRAW":
					confirmText = "Remis! To była zacięta gra!"
					break;
				}
				confirmText += "\nCzy chcesz zagrać ponownie?"
				if (confirm(confirmText)) {
					window.location = "/entry";
				}
			}
		}

		// $scope.$watch('$scope.gameData.isFinished', function(newVal,oldVal) {
			
		// 	$scope.boardConfig.draggable = !newVal;
		// 	if (newVal) {
		// 		let confirmText = "";
		// 		let isConfirmed = false;
		// 		switch ($scope.gameData.score) {
		// 		case "USER_WON":
		// 			confirmText = "Wygrana! Gratulacje!"
		// 			break;
		// 		case "USER_LOST":
		// 			confirmText = "Przegrana. Następnym razem pójdzie lepiej!"
		// 			break;
		// 		case "DRAW":
		// 			confirmText = "Remis! To była zacięta gra!"
		// 			break;
		// 		}
		// 		confirmText += "\nCzy chcesz zagrać ponownie?"
		// 		if (confirm(confirmText)) {
		// 			window.location = "/entry";
		// 		}
		// 	}
		// });

		// $scope.$watch('$scope.gameData.isUserTurn', function(newVal, oldVal) {
		// 	if (newVal) {
		// 		$scope.turnOwnerName = "gracza";
		// 	}
		// 	else {
		// 		$scope.turnOwnerName = "komputera";
		// 	}
		// });

		// $scope.$watch('$scope.gameData.isUserWhite', function(newVal, oldVal) {
		// 	if (newVal) {
		// 		$scope.gameData.userColorString = "biały";
		// 		$scope.gameData.compColorString = "czarny";
		// 	}
		// 	else {
		// 		$scope.gameData.colorString = "czarny";
		// 		$scope.gameData.compColorString = "biały";
		// 	}
		// });
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
				 this.getUserData = function(callback) {
					return $http.get('/ajax/checkerspy/get_user_data/').then(callback); 
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


