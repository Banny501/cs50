var res = Math.floor(Math.random() * 16).toString(2).padStart(4,0)
var ansver = "0100";
let lamps = [];
for (var i = 0; i < res.length; i++)
{
  lamps[i] = new Lamp(res.charAt(i), i);
}
document.addEventListener('DOMContentLoaded',function() {
  let lamp = document.querySelectorAll('.lamp');
  for (let i = 0; i < lamp.length; i++) {
      lamp[i].addEventListener('click', function() {
      lamps[i].invert(i);
    })
  }
  let check = document.querySelector('.butt');
  check.addEventListener('click',function() {
      res = "";
    for (var i = 0; i < lamps.length; i++) {
      res += lamps[i].value;
    }
    if (res == ansver) {
      document.getElementById("answer").innerHTML = "You are wonderful!";
    }
    else {
      document.getElementById("answer").innerHTML = "I don't think so";
    }
  })
});
