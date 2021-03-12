

    var x = Math.floor(Math.random() * 128);
    var y = Math.floor(Math.random() * 128);
    var ansver = (x + y).toString(2).padStart(8,0)
    var x = x.toString(2).padStart(8,0);
    var y = y.toString(10);
    var res = Math.floor(Math.random() * 256).toString(2).padStart(8,0)
    document.getElementById("X").innerHTML = x;
    document.getElementById("Y").innerHTML = y;

    document.getElementById("deb").innerHTML = ansver; //DEBUG

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
              document.getElementById("deb").innerHTML = 'good'; //DEBUG
            }
            else {
              document.getElementById("deb").innerHTML = 'bad'; //DEBUG
            }
          })
      });
