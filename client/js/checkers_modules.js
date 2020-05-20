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
					srvInfo.initializeGame($scope.isUserWhite);
					window.location = "/play";
				}
			};
}]);

myAppControllers.controller('gameController',
	['$scope', 'srvInfo',
		function ($scope, srvInfo) {

		angular.element(function() {
			$scope.loadBoard();
			$scope.printUserData();
		});
		
		$scope.onPieceDrop = function(source, target) {
			console.log('Source: ' + source)
			console.log('Target: ' + target)
			move = { 'source' : source, 'destination' : target }
			srvInfo.processUserMove(move,
				function(data) {
					$scope.currentFEN = data.data.fen;
					console.log($scope.currentFEN)
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
				}
			)
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
					document.getElementById('userNameView').textContent = data.data.user_name;
					document.getElementById('userColorView').textContent = data.data.user_color;
					console.log("got user data");
					console.log(data.data.user_name);
				}
			)
		}

		$scope.loadBoard = function() {
			srvInfo.getGameState (
				function(data) {
					$scope.currentFEN = data.data.fen;
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
				}
			)
		}

		$scope.makeComputerMove = function() {
			srvInfo.makeComputerMove(
				function(data) {
					$scope.currentFEN = data.data.fen;
					$scope.boardConfig.position = $scope.currentFEN;
					$scope.board = Chessboard('board', $scope.boardConfig);
				}
			)
		}
}]);
	

// communication with the server
angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {

				 this.initializeGame = function(data) {
					return $http.get('/ajax/checkerspy/initialize/?user_name='
					+ document.getElementById('userNameText').value + '&is_user_white='
					+ !document.getElementById('userColorSwitch').checked); 
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
				 }
				 this.makeComputerMove = function(callback) {
					return $http.get('/ajax/checkerspy/make_computer_move/').then(callback); 
				 }

             });


