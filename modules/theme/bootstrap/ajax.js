
var http_request = false;
var callback = false;
var response; 

function makeRequest(url, formid, callme) {

  http_request = false;
  callback = callme;

  if (window.XMLHttpRequest) { // Mozilla, Safari,...
    http_request = new XMLHttpRequest();
    if (http_request.overrideMimeType) {
      http_request.overrideMimeType('text/xml');
    }
  } else if (window.ActiveXObject) { // IE
    try {
      http_request = new ActiveXObject("Msxml2.XMLHTTP");
    } catch (e) {
      try {
        http_request = new ActiveXObject("Microsoft.XMLHTTP");
      } catch (e) {}
    }
  }

  if (!http_request) {
    alert('Giving up :( Cannot create an XMLHTTP instance');
    return false;
  }

  var inputs;
  var posts = new Array();
  var post = '';
  var children = document.getElementById(formid).getElementsByTagName('input');
  for (var j = 0, child; child = children[j]; j++)
  {
    if (child.name && child.value)
    {
      if (child.name == 'target')
        posts.push('target=ajax');
      else
        posts.push(child.name+"="+encodeURI(child.value));
    }
  }

  http_request.onreadystatechange = alertContents;
  http_request.open("POST", url, true);
  http_request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  http_request.send(posts.join('&'));
}

function alertContents() {

  if (http_request.readyState == 4) {
    if (http_request.status == 200) {
      response = http_request.responseXML;
      setTimeout(callback,0);
    } else {
      alert('There was a problem with the request.');
    }
  }

}

function renameDone()
{
    document.getElementById('renameform').getElementsByTagName('input');
    var newtitle = document.getElementById('formtitle').value;
    document.getElementById('title').innerHTML=newtitle;
    document.getElementById('rename').style.display='none';
    document.getElementById('receipt').style.visibility='visible';
    document.getElementById('receipt').innerHTML='<form action="'+cameralifebaseurl+'/undo_controller.php" method="post"><input id="receiptid" type="hidden" name="id" value="'+response.firstChild.firstChild.textContent+'" /><input type="hidden" name="action" value="undo" /><input type="hidden" name="target" value="'+window.location+'" />The description has been updated. <button type="submit">Undo</button></form>';
    
}
