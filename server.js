var http = require('http');
var https = require('https');
var crypto = require('crypto');

// Event Hubs parameters
var namespace = 'labsambient-ns';
var hubname ='labsambient';
var devicename = 'ardiuno';

// Shared access key (from Event Hub configuration)
var my_key_name = 'SendPolicy';
var my_key = 'xbnzyB/ZMmDrduNsa5BN2SPDFyvKyz9Uw5gvhfcF94M=';

// Full Event Hub publisher URI
var my_uri = 'https://' + namespace + '.servicebus.windows.net' + '/' + hubname + '/publishers/' + devicename + '/messages';

function create_sas_token(uri, key_name, key)
{
    // Token expires in 24 hours
    var expiry = Math.floor(new Date().getTime()/1000+3600*24);

    var string_to_sign = encodeURIComponent(uri) + '\n' + expiry;
    var hmac = crypto.createHmac('sha256', key);
    hmac.update(string_to_sign);
    var signature = hmac.digest('base64');
    var token = 'SharedAccessSignature sr=' + encodeURIComponent(uri) + '&sig=' + encodeURIComponent(signature) + '&se=' + expiry + '&skn=' + key_name;

    return token;
}

//var my_sas = create_sas_token(my_uri, my_key_name, my_key)

function send_payload(payload)
{
  var options = {
    hostname: namespace + '.servicebus.windows.net',
    port: 443,
    path: '/' + hubname + '/publishers/' + devicename + '/messages',
    method: 'POST',
    headers: {
      'Authorization': my_sas,
      'Content-Length': payload.length,
      'Content-Type': 'application/atom+xml;type=entry;charset=utf-8'
    }
  };
  
  var req = https.request(options, function(res) {
    console.log("statusCode: ", res.statusCode);
    console.log("headers: ", res.headers);
  
    res.on('data', function(d) {
      process.stdout.write(d);
    });
  });
  
  req.on('error', function(e) {
    console.error(e);
  });
  
  req.write(payload);
  req.end();
}

var server = http.createServer(function(request, response) {
  var body = '';
  request.on('data', function(data) {
    body += data;
  });
  request.on('end', function() {
    send_payload(body);
    response.statusCode = 200;
    response.end();
  });
});

server.listen(process.env.PORT);
