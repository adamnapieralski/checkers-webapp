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

		$scope.boardConfig = {
			draggable: true,	//myszka
			dropOffBoard: 'snapback'
		}
		$scope.board = Chessboard('board', $scope.boardConfig);

		$scope.printUserData = function(data) {
			srvInfo.getUserData(
				function(data) {
					document.getElementById('userNameView').textContent = data.data.user_name;
					document.getElementById('userColorView').textContent = data.data.user_color;
				}
			)
		}

		$scope.loadBoard = function(data) {
			srvInfo.getGameState (
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
				 }

             });


