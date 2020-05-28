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

		angular.element(function() {
			$scope.ifEnd = false; //moze apply?
			$scope.loadBoard();
			$scope.printUserData();
			if (!$scope.isUserTurn) {
				$scope.turn = 'komputera';
				console.log($scope.turn);
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
		}
		
		$scope.onPieceDrop = function(source, target) {
			$scope.turn = 'gracza';
			console.log($scope.turn)

			console.log('Source: ' + source)
			console.log('Target: ' + target)
			move = { 'source' : source, 'destination' : target }

			srvInfo.processUserMove(move,
				function(data) {
					$scope.currentFEN = data.data.fen;
					$scope.isUserTurn = data.data.isUserTurn
					$scope.isInMultipleMove = data.data.isInMultipleMove
					console.log($scope.currentFEN)
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
					$scope.uAP = data.data.uAP;
					$scope.cAP = data.data.cAP;
					$scope.uAK = data.data.uAK;
					$scope.cAK = data.data.cAK;
					$scope.ifEnd = data.data.isEnd;
				}
			)
			console.log($scope.uAP);
			console.log($scope.cAP);
			console.log($scope.uAK);
			console.log($scope.cAK);
			console.log($scope.ifEnd);

			if (!$scope.isInMultipleMove) {
				$scope.turn = 'komputera';
				console.log($scope.turn);
				$timeout(function() {
					$scope.makeComputerMove();
				}, 1200)
			}
		}

		$scope.boardConfig = {
			draggable: true,	//myszka
			dropOffBoard: 'snapback',
			onDrop: $scope.onPieceDrop
		}

		$scope.board = Chessboard('board', $scope.boardConfig);

		$scope.printUserData = function() {
			console.log("Printing user data");
			srvInfo.getUserData(
				function(data) {
					$scope.userName = data.data.user_name;
					$scope.userColor = data.data.user_color;
					document.getElementById('userNameView').textContent = data.data.user_name;
					document.getElementById('userColorView').textContent = data.data.user_color;
					$scope.compColorView = data.data.comp_name;
					console.log("got user data");
					console.log(data.data.user_name);
				}
			)
		}

		$scope.loadBoard = function() {
			srvInfo.getGameState (
				function(data) {
					$scope.currentFEN = data.data.fen;
					$scope.isUserTurn = data.data.isUserTurn
					$scope.isInMultipleMove = data.data.isInMultipleMove
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
					$scope.uAP = data.data.uAP;
					$scope.cAP = data.data.cAP;
					$scope.uAK = data.data.uAK;
					$scope.cAK = data.data.cAK;
					$scope.ifEnd = data.data.isEnd;
					/*$scope.$apply(function(){
						$scope.ifEnd = data.data.isEnd;
					});*/
				}
			)
			console.log($scope.uAP);
			console.log($scope.cAP);
			console.log($scope.uAK);
			console.log($scope.cAK);
			console.log($scope.ifEnd);
			if($scope.isUserTurn){
				$scope.turn = 'gracza';
			}
			else{
				$scope.turn = 'komputera';
			}
		}

		$scope.makeComputerMove = function() {
			if($scope.isUserTurn){
				$scope.turn = 'gracza';
			}
			else{
				$scope.turn = 'komputera';
			}
			srvInfo.makeComputerMove(
				function(data) {
					$scope.currentFEN = data.data.fen;
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
					$scope.uAP = data.data.uAP;
					$scope.cAP = data.data.cAP;
					$scope.uAK = data.data.uAK;
					$scope.cAK = data.data.cAK;
					$scope.ifEnd = data.data.isEnd;

				}
			)
			console.log($scope.uAP);
			console.log($scope.cAP);
			console.log($scope.uAK);
			console.log($scope.cAK);
			console.log($scope.ifEnd);
			$scope.turn = 'gracza';
			console.log($scope.turn)
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


