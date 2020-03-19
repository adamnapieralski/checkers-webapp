angular.module('Checkers', ['myAppControllers', 'myAppServices'] );

angular.module('myAppControllers', [])
	.controller('codeController',
				['$scope',
				 'srvInfo',
				 function ($scope, srvInfo) {
					$scope.viewTile = function(data) {
						srvInfo.findTile(
							function(data) {
								$scope.pawn_tile = data;
							});
					};
				 }]);

// communication with the server
angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {
                 this.findTile = function(callback) {
                     return $http.get('/ajax/checkerspy/findTile/?pawn_id='+document.getElementById('pawn_id').value).success(callback);
                 };
             });


