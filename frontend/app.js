var eos;

var config = {
	keyProvider: "5KEFmzRkaWXZh2XF3SkPenzsGMrfdJvDGapmjBbKwZrGfU2ZWxa", 
	httpEndpoint: 'http://192.168.0.111:8888',
	expireInSeconds: 60,
	broadcast: true,
	debug: false,
};


$( document ).ready(function() {
	M.AutoInit();

	eos = Eos.Localnet(config);  
});

function addPlayer(ulogin, password) {
	eos.contract('game1').then(contract => 
			contract.newplayer({login: ulogin, pass: password},
				{authorization: "game1"})).catch(function(exception) {
											     if(exception) {
												     alert(exception);
											     }
										     })
}


function getPlayers() {
	eos.getTableRows({
		"json": true,
		"scope": "game1",
		"code": "game1",
		"table": "player",
		"limit": 500
	}).then(result => {
		console.log(result);
	}).catch(function(exception) {
		if(exception) {
			alert(exception);
		}
	});
}

function gotoForm(frm) {
	$(".appform").hide();
	$("#"+frm).show();
}

function login() {
	gotoForm("homeForm");
}

function register() {
	$("input").val("");
	gotoForm("registerForm");
}

function onRegisterOk() {
   var user = $("#rlogin").val();
   var p1 = $("#rpassword").val();
   var p2 = $("#rpassword2").val();

   if (p1 != p2) {
	   M.toast({html: 'Passwords not equals!'});
	   return;
   }


   eos.contract('game1')
	   .then(contract => 
			   contract.newplayer({login: user, pass: p1},
				   {authorization: "game1"})).then(result => { 
										     gotoForm("loginForm");
									     })
   .catch(function(exception) {
	   if(exception) {
		   alert(exception);
	   }
   })
}

function onRegisterCancel() {
	gotoForm("loginForm");
}
