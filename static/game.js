var started = false;
var start = new Date().getTime();
if(started == true){
var now = new Date().getTime();
var t = now-start;
var minutes=Math.floor((t%(1000 * 60 * 60)) / (1000 * 60 ));
var seconds=Math.floor((t%(1000 * 60 )) / 1000 );
console.log(minutes*60+seconds)
}
$("timer").innerHTML = minutes+"m "+seconds+"s ";
$(document).keypress(function() {
  if (!started) {
    started = true;
    console.log("Started")
    var start = new Date().getTime();
  }
});