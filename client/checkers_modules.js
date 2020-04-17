angular.module('Checkers', ['myAppControllers', 'myAppServices'] );

var myAppControllers = angular.module('myAppControllers', []);

myAppControllers.controller('codeController',
	['$scope', 'srvInfo',
		function ($scope, srvInfo) {

		$scope.viewTile = function(data) {
			srvInfo.findTile(
				function(data) {
					// zwrocone z findTile z checkerspy/views.py
					$scope.pawn_tile = data;
				});
		};

		$scope.loadGame = function(data) {
			if (document.getElementById('userNameText').value == "") {
				document.getElementById('userNameText').placeholder = "Podaj nazwę gracza!";
				document.getElementById('userNameText').style.borderColor = 'red';
			}
			else {
				window.location = "/play";
			}
		};
}]);
	

// communication with the server
angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {
                 this.findTile = function(callback) {
					 // wywoluje findTile z checkerspy/views.py
                     return $http.get('/ajax/checkerspy/findTile/?pawn_id='+document.getElementById('pawn_id').value).success(callback);
                 };
             });


