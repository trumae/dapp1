var eos;

var config = {
	keyProvider: ["5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3",
	              "5KEFmzRkaWXZh2XF3SkPenzsGMrfdJvDGapmjBbKwZrGfU2ZWxa"],
	httpEndpoint: 'http://192.168.0.111:8888',
	expireInSeconds: 60,
	broadcast: true,
	debug: false,
};

function hashloginpass(login, pass) {
    var saltpass = "salt@!#@@";
    //checksum256 ret;

    ss = login + "_" + pass + saltpass;

    var hash = sha256.create();
    hash.update(ss);

    return hash.hex();
}

/* function to index generate */
var prime___ = 9999999999299;
function cppjsindex(s) {
    var r = 1;
    for (var i=0; i < s.length; i++) {
	r *= s.charCodeAt(i);
	r ++;
	r = r % prime___;
    }
    return r;
}

var {api, ecc, json, Fcbuffer, format} = Eos.modules
var login = "";
var password = "";

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

function onLogin() {
    var user = $("#login").val();
    var p1 = $("#password").val();

    eos.getTableRows({
	    "json": true,
	    "scope": "game1",
	    "code": "game1",
	    "table": "player",
	    "table_key": "id",
	    "lower_bound" : cppjsindex(user), "limit" : 1,
    }).then(result => {	
	h = result.rows[0].passhash;
	hlocal = hashloginpass(user, p1);
	if (h == hlocal) {
	    gotoForm("homeForm");
	} else {
	    M.toast({html: 'Login/password fail!'});
	    $("#password").val("");
	}
    }).catch(function(exception) {
	if(exception) {
	    alert(exception);
	}
    });
}

function onRegister() {
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

    try {
	format.encodeName(user);
    } catch (exc) {
	M.toast({html: 'Name should be less than 13 characters and only contains the following symbol .12345abcdefghijklmnopqrstuvwxyz'});
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

