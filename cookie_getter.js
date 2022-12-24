function getCookie(name) {
  const value = `; ${document.cookie}`;
  const parts = value.split(`; ${name}=`);
  if (parts.length === 2) return parts.pop().split(';').shift()
  else return ""
}
function setget(){
  el = document.getElementsByClassName("inp")
  // el = document.getElementById("keyinpget")
  for (var i = 0; i < el.length; i++) {
    el[i].value = getCookie("get");
  }
}
window.onload = setget()
document.addEventListener("DOMContentLoaded", setget())