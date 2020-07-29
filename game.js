$(document).keypress(function() {
  if (!started) {
    started = true;
    var start = new Date().getTime();
    var now = new Date().getTime();
    var t = now-start;
    var minutes=Math.floor((t%(1000 * 60 * 60)) / (1000 * 60 ));
    var seconds=Math.floor((t%(1000 * 60 )) / 1000 );
    $("timer").innerHTML = minutes+"m "+seconds+"s ";
  }
});