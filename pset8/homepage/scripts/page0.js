var x = Math.floor(Math.random() * 8);
var y = Math.floor(Math.random() * 8);
var ansver = (x + y).toString(2).padStart(4,0)
var x = x.toString(2).padStart(4,0);
var y = y.toString(10);
var res = Math.floor(Math.random() * 16).toString(2).padStart(4,0)
document.getElementById("X").innerHTML = x;
document.getElementById("Y").innerHTML = y;

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
      for (var i = 0; i < lamps.length; i++)
      {
        res += lamps[i].value;
      }
      if (res == ansver)
      {
        document.getElementById("answer").innerHTML = "Well done"; 
        document.getElementById("next").innerHTML = "Next";
      }
      else
      {
        document.getElementById("answer").innerHTML = "I don't think so";
      }
  })
});
