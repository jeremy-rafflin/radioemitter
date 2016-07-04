module.exports = function(params){   
	var identifiant = parseInt(params.deviceType.identifier) + parseInt(params.state.value);

	var delai = 200; // delais in millisecond between two signals
	var nbrs_signals = 4; // we send 4 signal
	// radio is not secure transmision, we send the signals many time
	for (var i = 0; i <= nbrs_signals; i++) {
		setTimeout(function(){ 
			gladys.modules.serial.sendCode('{"fonction_name":"SendRadioCode","code":"' + identifiant + '"}%');
		}, i * delai);
	}
	
	return true;
};