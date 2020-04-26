angular.module('Checkers', ['myAppControllers', 'myAppServices'] );

var myAppControllers = angular.module('myAppControllers', []);

myAppControllers.controller('codeController',
	['$scope', 'srvInfo',
		function ($scope, srvInfo) {

		$scope.viewTile = function(data) {
			this.printUserName();
			srvInfo.findTile(
				function(data) {
					// zwrocone z findTile z checkerspy/views.py
					$scope.pawn_tile = data.data;
					console.log(data);
				});
		};

		$scope.loadGame = function(data) {
			if (document.getElementById('userNameText').value == "") {
				document.getElementById('userNameText').placeholder = "Podaj nazwę gracza!";
				document.getElementById('userNameText').style.borderColor = 'red';
			}
			else {
				srvInfo.initializeGame(function(data) {});
				window.location = "/play";
			}
		};

		$scope.printUserName = function(data) {
			srvInfo.getUserName(
				function(data) {
					document.getElementById('userNameView').textContent = data.data.user_name;
					document.getElementById('userColorView').textContent = data.data.user_color;
				}
			)
		}
}]);
	

// communication with the server
angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {
                 this.findTile = function(callback) {
					 // wywoluje findTile z checkerspy/views.py
                     return $http.get('/ajax/checkerspy/findTile/?pawn_id='+document.getElementById('pawn_id').value).then(callback);
				 };
				 this.initializeGame = function(callback) {
					var colors = document.getElementsByName('userColors'); 
					var user_color = "";
					for(i = 0; i < colors.length; i++) { 
						if(colors[i].checked) 
							user_color = colors[i].value;
					} 
					return $http.get('/ajax/checkerspy/initialize/?user_name='
					+ document.getElementById('userNameText').value + '&user_color='
					+ user_color).then(callback); 
				 };
				 this.getUserName = function(callback) {
					return $http.get('/ajax/checkerspy/get_user_data/').then(callback); 
				 };

             });


