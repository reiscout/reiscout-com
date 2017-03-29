function SendSMS() {
  var xhttp;
document.getElementById("txtResponse").innerHTML = "";
var str=document.getElementById("phone").value;
if(str.match(/^[(]{0,1}[0-9]{3}[)]{0,1}[-\s\.]{0,1}[0-9]{3}[-\s\.]{0,1}[0-9]{4}$/)){
   
var apptype=document.getElementById("apptype").value;
/*  if (str.length != 10) { 
    document.getElementById("txtResponse").innerHTML = "Please enter a valid number";
    return false;
  }
*/

  xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      document.getElementById("txtResponse").innerHTML = xhttp.responseText;
    }
  };
  xhttp.open("GET", "/sites/all/libraries/twilio-php-master/send_sms.php?phone="+str+"&apptype="+apptype, true);
  xhttp.send();   
  return true;

}
else {
 document.getElementById("txtResponse").innerHTML = "Please enter a valid number";
return false;
}
}
